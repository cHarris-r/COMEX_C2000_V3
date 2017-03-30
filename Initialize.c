/*
 * Initialize.c
 *
 *  Created on: Mar 19, 2017
 *      Author: Christopher Harris
 */


#include "COMEX_Proj.h"




/*
** f_Initialize();
** This handles most of the gross common
**  Initializations */
void f_Initialize( void )
{
   /* Initialize System Control:
   ** PLL, WatchDog, enable Peripheral Clocks */
   InitSysCtrl();

   /* Initialize GPIO */
   InitGpio();


   /* Initialize the pins for the SCI-A port.
   ** GPIO_SetupPinMux() - Sets the GPxMUX1/2 and GPyMUX1/2 register bits
   ** GPIO_SetupPinOptions() - Sets the direction and configuration of the GPIOS */
   GPIO_SetupPinMux(18, GPIO_MUX_CPU1, 2); // set to mux 2
   GPIO_SetupPinOptions(18, GPIO_INPUT, GPIO_PUSHPULL);
   GPIO_SetupPinMux(19, GPIO_MUX_CPU1, 2); // set to mux 2
   GPIO_SetupPinOptions(19, GPIO_OUTPUT, GPIO_ASYNC);

   /* Clear all __interrupts and initialize PIE vector table:
   ** Disable CPU __interrupts */
   DINT;

   /* Initialize PIE control registers to their default state.
   ** The default state is all PIE __interrupts disabled and flags are cleared */
   InitPieCtrl();

   /* Disable CPU __interrupts and clear all CPU __interrupt flags: */
   IER = 0x0000;
   IFR = 0x0000;

   /* Initialize the PIE vector table with pointers to the shell Interrupt
   ** Service Routines (ISR).
   ** This will populate the entire table, even if the __interrupt is not used */
   InitPieVectTable();

} /* End f_Initialize */


/*
** f_sci_init
** Test 1,SCIA  DLB, 8-bit word, baud rate 0x000F,
**   default, 1 STOP bit, no parity */
void f_sci_init()
{
    // Note: Clocks were turned on to the SCIA peripheral in the InitSysCtrl() function
    ScibRegs.SCICCR.all  = 0x0007;  // 1 stop bit,  No loopback, No parity, 8 char bits, async mode, idle-line protocol
    ScibRegs.SCICTL1.all = 0x0003;  // enable TX, RX, internal SCICLK, Disable RX ERR, SLEEP, TXWAKE

    ScibRegs.SCICTL2.all = 0x0003;       // Disable txrdy and rxrdy interupt
    ScibRegs.SCICTL2.bit.TXINTENA = 1;   // redundant of above
    ScibRegs.SCICTL2.bit.RXBKINTENA = 1; // redundant of above

    // SCIA at 9600 baud
    // BAUD = clk / (( BRR+1)*8)
    // @LSPCLK = 50 MHz (200 MHz SYSCLK) HBAUD = 0x02 and LBAUD = 0x8B.
    // @LSPCLK = 30 MHz (120 MHz SYSCLK) HBAUD = 0x01 and LBAUD = 0x86.

    //ScibRegs.SCILBAUD.all = 0x0000; // 115200
    //ScibRegs.SCILBAUD.all = 0x0036;

    //ScibRegs.SCIHBAUD.all = 0x0002; //9600
    //ScibRegs.SCILBAUD.all = 0x008B;

    ScibRegs.SCIHBAUD.all = 0x0001; //9600 - 25 MHz
    ScibRegs.SCILBAUD.all = 0x0044;

    /* We set the baud rate low for auto-baud detection */
    //ScibRegs.SCIHBAUD.all = 0x0000; //for Auto baud
    //ScibRegs.SCILBAUD.all = 0x0002;

    ScibRegs.SCICTL1.all  = 0x0023;  // Relinquish SCI from SW Reset
} /* End of f_sci_init */



/*
** f_fifo_init
** Initialize the SCI FIFO */
void f_fifo_init()
{
    ScibRegs.SCIFFTX.all = 0xE043; // resume transmit/recieve, fifo enhancements enabled, re-enable transmit fifo, clear TXFFINT
    //ScibRegs.SCIFFTX.all = 0xE040; // resume transmit/recieve, fifo enhancements enabled, re-enable transmit fifo, clear TXFFINT
    ScibRegs.SCIFFRX.all = 0x2044; // re-enable fifo revieve, set interupt lvl (4), set rx interupt at gteq to interupt lvl
    ScibRegs.SCIFFRX.bit.RXFFINTCLR = 1; // clear interupt
    ScibRegs.SCIFFTX.bit.TXFFINTCLR = 1; // clear interupt

    /* Auto-baud register will be set in f_Handshake */
    //ScibRegs.SCIFFCT.all = 0x0;    // clear fifo control registers (flags), disable auto-baud alignment, set fifo transfer delay to 3 baud cycles
    //ScibRegs.SCIFFCT.all = 0x6003;   // clear ABD flag, enable auto baud, set fifo delat to 3 baud cycles
    //ScibRegs.SCIFFCT.all = 0x6000;   // clear ABD flag, enable auto baud, no fifo delay
    ScibRegs.SCIFFCT.all = 0x4000;   // clear ABD flag, disable auto baud, no fifo delay
} /* End of f_fifo_init */


/* f_Hnadshake
** This is not currently used!
** The Handshake code uses the auto-baud rate detection
** to communicate with the IMU. This is completed via the following:
**   1) Initiate the handshake with the IMU by sending an "Initiate"
**      character. This character will not be understood by the IMU
**      (since the baud rate has not been set) but that does not matter.
**      The IMU will initiate the handshake once any character is recieved.
**   2) The IMU will then send one of the boud-lock characters 'a' or 'A'
**      The C2000 will then (internally) detect the character and set the
**      baud rate automatically.
**   3) Once the baud rate is set successfully, we send a confirmation character
**      to the IMU. This character must match the confirmation character on the
**      IMU.
**   4) The IMU will echo the confirmation character.
**      If the IMU (or the C2000) did not complete the handshake correctly, the
**      reply from the IMU will not be the confirmation character. If this is
**      the case, we must retry the baud lock sequence (return to step 1)
**      If handshake complete successfully, we need to toggle several registers to
**      deactivate the auto-baud detection. */
void f_Handshake( IMU_STATE_TYPE g_IMU_state )
{
    int i;

    /* NOTE:
    **   ASCII 'A' :: DEC:65 HEX:0x41
    **   ASCII 'a' :: DEC:97 HEX:0x61 */
    const char BaudLockChar = 0x61;

    /* HEX: 0xB1 DEC: 177 BIN: 1011 0001 */
    const char InitHandshakeChar = 0xA1;

    /* HEX: 0xAA DEC: 170 BIN: 1010 1010 */
    const char ConfirmChar = 0xAA;

    /* HEX: 0xAB DEC: 171 BIN: 1010 1011 */
    const char FailChar = 0xAB;


    /* Rx/Tx variables */
    int     nBytesIn;

    char InputBuffer[50];
    memset( &InputBuffer, 0, sizeof(char)*50 );

    /* Prepare for Auto-Baud Detection */
    ScibRegs.SCIFFCT.bit.ABDCLR = 1; /* Clear ABD bit */
    ScibRegs.SCIFFCT.bit.CDC    = 1; /* Enable Auto-Baud detection */



    /* UART Hanshake
    ** We continue to attempt a handshake
    ** until there is a lock */
    while( g_IMU_state.BaudLock==FALSE )
    {
        /* Clear Rx Buffer (active low) */
        //ScibRegs.SCIFFRX.bit.RXFIFORESET = 0;
        //ScibRegs.SCIFFRX.bit.RXFIFORESET = 1;

        /* Clear Tx Buffer (active low) */
        //ScibRegs.SCIFFTX.bit.TXFIFORESET = 0;
        //ScibRegs.SCIFFTX.bit.TXFIFORESET = 1;

        /* 1) Initiate the handshake
        ** 2) Wait for IMU to respond with baud-lock char */
        while( ScibRegs.SCIFFCT.bit.ABD==0 )
        {
            f_xmit_char( InitHandshakeChar );
            if( ScibRegs.SCIFFTX.bit.TXFFST==16 )
            {
                /* Clear Tx Buffer (active low) */
                ScibRegs.SCIFFTX.bit.TXFIFORESET = 0;
                ScibRegs.SCIFFTX.bit.TXFIFORESET = 1;
            }

            if( (ScibRegs.SCIFFRX.bit.RXFFOVF==1) )
            {
                ScibRegs.SCIFFRX.bit.RXFIFORESET = 0;
                ScibRegs.SCIFFRX.bit.RXFIFORESET = 1;
            }
        }

        ScibRegs.SCIFFCT.bit.ABDCLR = 1; // Clear ABD bit
        ScibRegs.SCIFFCT.bit.CDC    = 0; // disable further Auto baud detection

        /* Clear Rx Buffer (active low) */
        //ScibRegs.SCIFFRX.bit.RXFIFORESET = 0;
        //ScibRegs.SCIFFRX.bit.RXFIFORESET = 1;

        /* Clear Tx Buffer (active low) */
        //ScibRegs.SCIFFTX.bit.TXFIFORESET = 0;
        //ScibRegs.SCIFFTX.bit.TXFIFORESET = 1;


        /* 3) Baud rate detected and set
        **    Send IMU Confirmation char */
        f_xmit_char( ConfirmChar );

        /* 4) Wait for IMU to reply
        **    If reply is confirmation char: Handshake successful
        **    Else: Handshake fail. Send FailChar to IMU and retry
        **    NOTE:  nBytesIn should be 1! */
        while( ScibRegs.SCIFFRX.bit.RXFFST == 0 ) {}
        nBytesIn = ScibRegs.SCIFFRX.bit.RXFFST;
        for( i=0; i<nBytesIn; i++ ) { f_rcv_char( &InputBuffer[i] ); }

        if( InputBuffer[0]==ConfirmChar )
        {
            /* Handshake successful
            ** Deactivate auto-baud regs
            ** Set state flags */
            g_IMU_state.BaudLock = TRUE;

            //ScibRegs.SCIFFCT.bit.ABDCLR = 1; // Clear ABD bit
            //ScibRegs.SCIFFCT.bit.CDC    = 0; // disable further Auto baud detection

            /* Clear/Reset FIFO RX buffer */
            ScibRegs.SCIFFRX.bit.RXFIFORESET = 0;
            ScibRegs.SCIFFRX.bit.RXFIFORESET = 1;
        }
        else
        {
            /* If we received the Failure character
            ** Then the baud was set correctly, but the IMU
            ** doesn't know it yet ... let's try to send the
            ** confirmation character a few times to let
            ** the IMU know the baud rate is locked on our end. */
            if( (InputBuffer[0]==FailChar) || (InputBuffer[0]==BaudLockChar) )
            {
                for(;;)
                {
                    /* Clear input buffer */
                    //ScibRegs.SCIFFRX.bit.RXFIFORESET = 0;
                    //ScibRegs.SCIFFRX.bit.RXFIFORESET = 1;

                    /* Send Confirmation Char */
                    f_xmit_char( ConfirmChar );

                    /* Read Reply */
                    while( ScibRegs.SCIFFRX.bit.RXFFST == 0 ) {}
                    nBytesIn = ScibRegs.SCIFFRX.bit.RXFFST;
                    for( i=0; i<nBytesIn; i++ ) { f_rcv_char( &InputBuffer[i] ); }

                    if( InputBuffer[0]==ConfirmChar )
                    {
                        g_IMU_state.BaudLock = TRUE;
                        break;
                    }
                    else
                        continue;
                }

                if( g_IMU_state.BaudLock == TRUE ){
                    /* Clear/Reset FIFO RX buffer */
                    ScibRegs.SCIFFRX.bit.RXFIFORESET = 0;
                    ScibRegs.SCIFFRX.bit.RXFIFORESET = 1;
                }
                else
                {
                    /* Handshake Failed
                    ** We will retry handshake */
                    g_IMU_state.BaudLock = FALSE; /* Redundancy for clairity */

                    /* Clear/Reset FIFO RX buffer */
                    ScibRegs.SCIFFRX.bit.RXFIFORESET = 0;
                    ScibRegs.SCIFFRX.bit.RXFIFORESET = 1;

                    /* Clear ABD bit */
                    ScibRegs.SCIFFCT.bit.ABDCLR = 1;

                    /* Ensure have the auto-baud bit set
                    ** This should be redundant */
                    ScibRegs.SCIFFCT.bit.CDC    = 1;
                }
            }
            else
            {
                /* Handshake Failed
                ** We will retry handshake */
                g_IMU_state.BaudLock = FALSE; /* Redundancy for clairity */

                /* Clear/Reset FIFO RX buffer */
                ScibRegs.SCIFFRX.bit.RXFIFORESET = 0;
                ScibRegs.SCIFFRX.bit.RXFIFORESET = 1;

                /* Clear ABD bit */
                ScibRegs.SCIFFCT.bit.ABDCLR = 1;

                /* Ensure have the auto-baud bit set */
                ScibRegs.SCIFFCT.bit.CDC    = 1;
            }
        }
    }
} /* End f_Handshake */


