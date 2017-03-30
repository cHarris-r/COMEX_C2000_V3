//###########################################################################
//
//###########################################################################



/***************************************************************************
*************************** Includes ***************************************
****************************************************************************/

#include "COMEX_Proj.h"


/***************************************************************************
*************************** Globals ****************************************
****************************************************************************/





/***************************************************************************
*************************** Function Prototypes ****************************
****************************************************************************/
int f_TestPacket( void );

/***************************************************************************
*************************** Main Start *************************************
****************************************************************************/

void main( void )
{
   int ErrorCount = 0;

   f_Initialize();

   f_fifo_init();  // Initialize the SCI FIFO
   f_sci_init();   // Initialize SCI

   /* Handshake w/ IMU to sync baud rate */
   //g_IMU_state.BaudLock=false;
   //f_Handshake();

   ErrorCount = f_TestPacket();
}





/***************************************************************************
*************************** Functions **************************************
****************************************************************************/

int f_TestPacket( void )
{
    Uint16 LoopCount;
    Uint16 ErrorCount;
    unsigned char myChecksum;



    RESPONSE_TYPE Response;
    DATA_TYPE Data;

    //uint16_t SendChar = 0xB1; /* Debug int */
    uint16_t SendChar = 0xB2; /* Debug float */
    //uint16_t SendChar = 0xA1; /* Request 3 x 16 bit floats */
    //uint16_t SendChar = 0xA2; /* Request 3 x 32 bit floats */

    /* User specific code: */
    LoopCount   = 0;
    ErrorCount  = 0;

    /* Test */
    while( LoopCount<1000 )
    {
        /* Send test init character */
        while (ScibRegs.SCICTL2.bit.TXEMPTY == 0) {}
        ScibRegs.SCITXBUF.all = SendChar;

        /* Get data packet */
        f_GetPacket( &Data, &Response );

        /* Calculate checksum of data */
        myChecksum = f_CheckSum( &Response.Buffer[0], Response.Buffer_nBytes );

        if( myChecksum != Response.CheckSum ) { ErrorCount++; }

        LoopCount++;
    }

    return( ErrorCount );
} /* End f_TestPacket */





