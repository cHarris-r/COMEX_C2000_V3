/*
 * IO_Helpers.c
 *
 *  Created on: Mar 19, 2017
 *      Author: Christopher Harris
 */

#include "COMEX_Proj.h"




/*
** f_GetPacket
** This function reads the data packet response sent by
** the IMU. The protocol is custom and is not optimal by
** any means.
**
** There are several packet types
** The only difference between types is
** the data field arrangement
** Common packet fields:
**    u16 packet length
**    u16 packet type
**    u16 buffer length
**    u8  buffer
**    u8  checksum
** Data field (buffer)
**    case 1:
**      16 bit fixed point floats
**      Each element is shifted 7 bits
**      floats are signed
**    case 2:
**      16 bit debug character (0xB1)
**      Sent as a 16 bit integer
**
*/
void f_GetPacket( DATA_TYPE *Data, RESPONSE_TYPE *Response )
{
  int i;
  unsigned char Buffer[100];

  /* The first 2 bytes contain the length of the packet */
  while( (ScibRegs.SCIFFRX.bit.RXFFST == 0) ) {}
  Buffer[0] = ScibRegs.SCIRXBUF.bit.SAR;
  while( (ScibRegs.SCIFFRX.bit.RXFFST == 0) ) {}
  Buffer[1] = ScibRegs.SCIRXBUF.bit.SAR;
  Response->Packet_nBytes = (Buffer[0]<<8) | (Buffer[1]);

  /* Read the entire packet and store in a buffer */
  for( i=0; i<Response->Packet_nBytes; i++)
  {
      while( (ScibRegs.SCIFFRX.bit.RXFFST == 0) ) {}
      Buffer[i] = ScibRegs.SCIRXBUF.bit.SAR;
  }

  /* The first byte pair is the packet type */
  Response->PacketType = (Buffer[0]<<8) | (Buffer[1]);

  /* The second byte pair is the length of the data buffer */
  Response->Buffer_nBytes = (Buffer[2]<<8) | (Buffer[3]);

  /* Read the data buffer and copy to new array */
  for( i=0; i<Response->Buffer_nBytes; i++)
  {
    Response->Buffer[i] = Buffer[2*2 + i];
  }

  switch ( Response->PacketType )
  {
    /* Packet type 11
    ** Debug test byte
    ** Data buffer
    **   1 x 16 bit integer
    **   Ints are signed */
    case 11:
      f_UnpackInt_u16( &Response->Buffer[0], &Data->Test_uI16 );
      break;

    /* Packet type 12
    ** Debug test 32 bit float
    ** Data buffer
    **   1 x 32 bit float
    **   Float is sent bit for bit */
    case 12:
      f_UnpackFloat_s32( &Response->Buffer[0], &Data->Test_F32 );
      break;

    /* Packet type 1
    ** Roll pitch yaw data
    ** Data buffer:
    **    3 x 16 bit fixed point floats
    **    Each element is shifted 7 bits
    **    floats are signed */
    case 1:
      /* Unpack the data (assuming 2 byte float) into Data array */
      f_UnpackFloat_s16( &Response->Buffer[0], &Data->Roll );
      f_UnpackFloat_s16( &Response->Buffer[SFLOAT*1], &Data->Pitch );
      f_UnpackFloat_s16( &Response->Buffer[SFLOAT*2], &Data->Yaw );
      break;

    /* Packet type 2
    ** Roll pitch yaw data
    ** Data buffer:
    **    3 x 32 bit floats
    **    floats are sent bit for bit */
    case 2:
      /* Unpack the data (assuming 2 byte float) into Data array */
      f_UnpackFloat_s32( &Response->Buffer[0], &Data->Roll );
      f_UnpackFloat_s32( &Response->Buffer[SFLOAT*1], &Data->Pitch );
      f_UnpackFloat_s32( &Response->Buffer[SFLOAT*2], &Data->Yaw );
      break;


    /* Undetermined case */
    default:
      Data->Test_uI16 = 0xAA;
  }

  /* Read IMU calculated checksum */
  Response->CheckSum = Buffer[Response->Packet_nBytes-1];

} /* End f_GetPacket */




/*
** f_UnpackFloat_u16
** This code converts 2 x 8 bit characters (sent from IMU)
** into a 16 bit signed float
** Characters are sent from a 16 bit signed integer */
void f_UnpackFloat_s16( unsigned char *Packet, float *Output )
{
  int hpFloat = 0;
  int div     = 128; /* shift right 7 bits */

  hpFloat = (Packet[0] << 8) | (Packet[1]);
  *Output = (float)hpFloat;
  *Output /= div;

} /* End f_UnpackFloat_u16 */


/*
** f_UnpackFloat_u16
** This code converts the 2 x 8 bit characters (sent from IMU)
** into a 16 bit unsigned float
** Characters are sent from a 16 bit unsigned integer */
void f_UnpackFloat_u16( unsigned char *Packet, float *Output )
{
  int hpFloat = 0;
  int div     = 256; /* shift right 8 bits */

  hpFloat = (Packet[0] << 8) | (Packet[1]);
  *Output = (float)hpFloat;
  *Output /= div;
} /* End f_UnpackFloat_u16 */


/*
** f_UnpackFloat_s32
** This code converts 4 x 8 bit characters (sent from IMU)
** into a 32 bit signed float
** Characters are sent as float bit for bit */
void f_UnpackFloat_s32( unsigned char *Packet, float *Output )
{
  int i;
  unsigned char *p_byte = (unsigned char*) Output;

  /* Notes about this operation:
  ** The TI board is LE.
  ** Further, the TI board uses 16 bit bytes
  ** The data was sent BE in 8 bit characters */
  for( i=0; i<2; i++)
  {
    p_byte[i] = ( Packet[2-(i*2)] << 8 ) | ( Packet[3-(i*2)] );
  }
} /* End f_UnpackFloat_u16 */


/*
** f_UnpackInt_s16
** This code converts the 2 x 8 bit characters (sent from IMU)
** into a 16 bit unsigned integer
** Characters are sent from a 16 bit signed integer */
void f_UnpackInt_s16( unsigned char *Packet, int *Output )
{
  /* We simply mask two adjacent characters in the data buffer */
  *Output = (Packet[0] << 8) | (Packet[1]);
}

/*
** f_UnpackInt_u16
** This code converts the 2 x 8 bit characters (sent from IMU)
** into a 16 bit signed integer
** Characters are sent from a 16 bit signed integer */
void f_UnpackInt_u16( unsigned char *Packet, unsigned int *Output )
{
  /* We simply mask two adjacent characters in the data buffer */
  *Output = (Packet[0] << 8) | (Packet[1]);
}


/*
** f_CheckSum
** Calculate a simple checksum
** We simply sum the data in a buffer */
unsigned char f_CheckSum( unsigned char *p_Buffer, uint16_t nBytes )
{
  int i;
  unsigned char checksum = 0;

  /* Our check sum is a simmple summation */
  for( i=0; i<nBytes; i++) { checksum += p_Buffer[i]; }

  return( checksum & 0xFF );
} /* End f_CheckSum */



/*
** f_xmit_char
** Transmit a single character */
void f_xmit_char( char xmitChar )
{
    /* Transmit "xmitChar" */
    //while (ScibRegs.SCICTL2.bit.TXEMPTY == 0) {}
    ScibRegs.SCITXBUF.all = xmitChar;
} /* End f_xmit_char */



/*
** f_rcv_char
** Receive a single character */
void f_rcv_char( char *InputBuffer )
{
    InputBuffer[0] = ScibRegs.SCIRXBUF.bit.SAR;
} /* End f_xmit_char */

