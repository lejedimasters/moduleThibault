/**
 * \file      sd_driver_cc2541.c
 ----------------------------------
 * \author    Romain AUBER
 * \copyright 2011 BodyCap S.A.S.
 * \version   1.0
 * \date      2015
 * \brief     SD driver
 *
 * \details  driver to write and read data on the SD card
 *
 */
 
#ifndef SD_DRIVER_CC2541_H
#define SD_DRIVER_CC2541_H

/***********************************************************************************
* INCLUDES
*/
#include "diskio.h"
#include "pff.h"
#include "pffconf.h"
#include "integer.h"

extern unsigned char CardType;

//data_token for data packet
static const unsigned char data_token1 = 0xFE;      //data_token fot cmd17/18/24
static const unsigned char data_token2 = 0xFC;      //data_token fot cmd25
/**
 * \fn      void sd_driver_cc2541_init( void )
 * \brief   Initialisation of the SD card
 * \return  1 : init sucess , 0: init fail
 */
extern unsigned char sd_driver_cc2541_init( void );

/**
 * \fn      void sd_driver_cc2541_send_cmd( unsigned char command, unsigned long argument )
 * \brief   send a command to SD card
 * \param   command : command to send
 * \param   argument : argument of the command
 */
extern void sd_driver_cc2541_send_cmd( unsigned char command, unsigned long argument );
	
/**
 * \fn      void sd_driver_cc2541_send_acmd( unsigned char command, uint32_t argument )
 * \brief   send a command to SD card
 * \param   command : command to send
 * \param   argument : argument of the command
 */
extern void sd_driver_cc2541_send_acmd( unsigned char command, unsigned long argument );

/**
 * \fn      sd_driver_cc2541_makeCRC(unsigned char *address, unsigned char length) 
 * \brief   calcul the CRC7 
 * \param   length : number of byte needed to calcul CRC7
 * \param   address : adddress od data with the CRC7 is calculed
 * \return  the CRC7 checksum
 */
unsigned char sd_driver_cc2541_makeCRC7(unsigned char *address, unsigned char length);

/**
 * \fn      sd_driver_cc2541_makeCRC16(unsigned char *address, unsigned char length) 
 * \brief   calcul the CRC16 
 * \param   length : number of byte needed to calcul CRC16
 * \param   address : adddress od data with the CRC16 is calculed
 * \return  the CRC16 checksum
 */
extern unsigned short sd_driver_cc2541_makeCRC16(unsigned char *address, unsigned short length);

/**
 * \fn      sd_driver_cc2541_write1byte() 
 * \brief   write one byte on SD card
 * \param   the first address on the sd card where we begin write data   
 * \param   number of byte of the data (max : 256 bytes)
 * \param   data to send 
 * \return  
 */
extern void sd_driver_cc2541_write(unsigned long data_address , unsigned short length , unsigned char *data);

/**
 * \fn      sd_driver_cc2541_send_data_packet() 
 * \brief   write one byte on SD card
 * \param   the first address on the sd card where we begin write data   
 * \param   number of byte of the data (max : 512 bytes)
 * \param   data to send 
 */
extern void sd_driver_cc2541_send_data_packet(unsigned long data_token , unsigned short length , const unsigned char *data);

/**
 * \fn      sd_driver_cc2541_read_data_packet() 
 * \brief   write one byte on SD card
 * \param   number of byte of the data (max : 512 bytes)
 * \param   data to send 
 */
extern void sd_driver_cc2541_read_data_packet( unsigned char *data);

/**
 * \fn      uint8 sd_driver_cc2541_read_R1( void )
 * \brief   read the R1 responce of SD card
 *
 * +-------------------------------------------------+
 * | 0 | arg | addr | seq | crc | cmd | erase | idle |
 * +-------------------------------------------------+
 * \return  return the R1 responce
 */
extern unsigned char sd_driver_cc2541_read_R1( void );
     

/**
 * \fn      uint8 sd_driver_cc2541_read_R7_or_R3( void )
 * \brief   read the R7 or R3 responce of SD card
 *
 ********************R3 response***************************
 * R1 / R7 Byte1 [39:32]
 * +-------------------------------------------------+
 * | 0 | arg | addr | seq | crc | cmd | erase | idle |
 * +-------------------------------------------------+
 * R7 Byte2 [31:24]
 * +-------------------------------------------------------+
 * |  31  |  30  |  29  |  28  |  27  |  26  |  25  |  24  |
 * |-------------------------------------------------------|
 * |  7   |  6   |  5   |  4   |  3   |  2   |  1   |  0   |
 * |-------------------------------------------------------|
 * |       CMD version         |      reserved             |
 * +-------------------------------------------------------+
 * R7 Byte3 [23:16] (reserved)
 * R7 Byte4 [15:8]
 * +-------------------------------------------------------+
 * |  15  |  14  |  13  |  12  |  11  |  10  |  9   |  8   |
 * |-------------------------------------------------------|
 * |  7   |  6   |  5   |  4   |  3   |  2   |  1   |  0   |
 * |-------------------------------------------------------|
 * |       reserved            |      voltage accepted     |
 * +-------------------------------------------------------+
 * R7 Byte5 [7:0] check pattern (do not care)
 *
 ********************R7 response***************************
 * R1 / R3 Byte1
 * +-------------------------------------------------+
 * | 0 | arg | addr | seq | crc | cmd | erase | idle |
 * +-------------------------------------------------+
 * R3 Byte2,3,4,5 [31:0]
 * +------------------------------------------------------------------------+
 * |                    CRC 
 * +------------------------------------------------------------------------+
 * \param   pointer to return the response R7 or R3
 * \return  return the R1 responce
 */
extern unsigned char sd_driver_cc2541_read_R7_or_R3( unsigned char *responseR7 );


#endif
