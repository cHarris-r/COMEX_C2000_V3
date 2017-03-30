/*
 * COMEX_Proj.h
 *
 *  Created on: Mar 19, 2017
 *      Author: Christopher Harris
 */

#ifndef COMEX_PROJ_H_
#define COMEX_PROJ_H_

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "F28x_Project.h"


#define TRUE  1
#define FALSE 0

/* n bytes in float */
#define SFLOAT 2


typedef struct
{
    uint16_t Packet_nBytes;     /* Length of entire packet, minus this variable, in bytes */
    uint16_t PacketType;        /* Type code of packet */
    uint16_t Buffer_nBytes;     /* Length of data buffer in bytes (0-50) */
    unsigned char  Buffer[50];  /* Data buffer */
    unsigned char  CheckSum;         /* CheckSum of data buffer only */
} RESPONSE_TYPE;

typedef struct
{
    bool BaudLock;
} IMU_STATE_TYPE;


typedef struct
{
  float Roll;
  float Pitch;
  float Yaw;

  uint16_t Test_uI16;
  int      Test_sI16;
  float    Test_F32;
} DATA_TYPE;


void f_Initialize( void );
void f_fifo_init(void);
void f_sci_init(void);
void f_Handshake(  IMU_STATE_TYPE g_IMU_state  );

void f_xmit_char( char xmitChar );
void f_rcv_char( char *InputBuffer );
void f_GetPacket( DATA_TYPE *Data, RESPONSE_TYPE *Response );
void f_UnpackFloat_s16( unsigned char *Packet, float *Output );
void f_UnpackFloat_u16( unsigned char *Packet, float *Output );
void f_UnpackFloat_s32( unsigned char *Packet, float *Output );
void f_UnpackInt_u16( unsigned char *Packet, unsigned int *Output );
void f_UnpackInt_s16( unsigned char *Packet, int *Output );
unsigned char f_CheckSum( unsigned char *p_Buffer, uint16_t nBytes );



#endif /* COMEX_PROJ_H_ */
