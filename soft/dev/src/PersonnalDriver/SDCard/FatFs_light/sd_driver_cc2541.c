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


/***********************************************************************************
* INCLUDES
*/

#include "sd_driver_cc2541.h"
#include "sd_spi.h"


unsigned char CardType;
uint8_t buffer[515];

/**
 * \fn      void sd_driver_cc2541_init( void )
 * \brief   Initialisation of the SD card
 * \return  1 : init sucess , 0: init fail
 */
unsigned char sd_driver_cc2541_init( void )
{
    uint8_t i;
    uint8_t responseR1 = 0;
    uint8_t responseR7_or_R3[4];
    
    CardType = 0;
    //initialization of spi
    sd_spi_init_low_speed();
    //spi_driver_cc2541_init();
    
    //Wait 1ms to be sure the card is correctly supply
    WAIT_N_MS(10);
    
    //dummy clock : to send at least dummy 74 clock cycles before sending any commands
    for (i = 0; i < 25; i++)
    {
    	/*
        // Write byte to USART0 buffer (transmit data).
        U1DBUF = 0xFF;
        // Check if byte is transmitted.
        while(!(U1CSR & U0CSR_TX_BYTE));
        // Clear transmit byte status.
        U1CSR &= ~U0CSR_TX_BYTE;
        */
    	sd_spi_transmit_receive(&responseR1,&responseR1,1);


    }
    
    //send CMD0
    sd_driver_cc2541_send_cmd(0, 0x00000000);
        
    // check R1 responce
    responseR1 = sd_driver_cc2541_read_R1();
    if(responseR1 != 1){
         return 0;
    }
     
    //send CMD8
    sd_driver_cc2541_send_cmd(8, 0x000001AA);
        
    //check the version of the sd card
    responseR1 = sd_driver_cc2541_read_R7_or_R3(responseR7_or_R3);
        if(responseR1 == 1){
            CardType = 2;
            if ( responseR7_or_R3[2] != 0x01 || responseR7_or_R3[3] != 0xAA ) {
                return 0;
            }
        } 
        else{
            CardType = 1;
        }
    
    responseR1 = 1;
    i = 0;
    while( responseR1 != 0 ){
    
        //send ACMD41
        sd_driver_cc2541_send_acmd(41, 0x40000000); 
    
        //check R1 responce
         responseR1 = sd_driver_cc2541_read_R1();
         
         i++;
             
         if(i == 100){
             return 0;
         }
    }   

    if( CardType == 2)
    {
        //send CMD58
        sd_driver_cc2541_send_cmd(58, 0x00000000);
        
        //check CCS bit in OCR
         responseR1 = sd_driver_cc2541_read_R7_or_R3(responseR7_or_R3);
         
         if((responseR7_or_R3[3] & 0xC0) != 0)
             return 0;
    }
    
    
    //send CMD16
    sd_driver_cc2541_send_cmd(16, 0x00000200);
    
    // the Sd card is initialized
    
    // no crc
    sd_driver_cc2541_send_cmd(59, 0x00000200);
    
    // change the speed of SPI at 2MHz
    sd_spi_init_high_speed();
    
    return 1;

}

/**
 * \fn      void sd_driver_cc2541_send_cmd( uint8_t command, uint32_t argument )
 * \brief   send a command to SD card
 * \param   command : command to send
 * \param   argument : argument of the command
 */
void sd_driver_cc2541_send_cmd( uint8_t command, uint32_t argument )
{
	uint8_t buffer_to_write[6];
	
	//calcul the command to write
	buffer_to_write[0] = 0x40 | command; 
	buffer_to_write[1] = (uint8_t)(argument >> 24);
	buffer_to_write[2] = (uint8_t)(argument >> 16);
	buffer_to_write[3] = (uint8_t)(argument >> 8);
	buffer_to_write[4] = (uint8_t)(argument);
	buffer_to_write[5] =  sd_driver_cc2541_makeCRC7(buffer_to_write , 5);  
	
	// write the commande on SPI
	//spi_driver_cc2541_write(6 , buffer_to_write);
	sd_spi_transmit_receive(buffer_to_write, buffer_to_write, 6);
}

/**
 * \fn      void sd_driver_cc2541_send_acmd( uint8_t command, uint32_t argument )
 * \brief   send a command to SD card; the command acmd is the same that cmd but we must send the command cmd55 before
 * \param   command : command to send
 * \param   argument : argument of the command
 */
void sd_driver_cc2541_send_acmd( uint8_t command, uint32_t argument )
{
    //send the command cmd 55 to indicate this is acmd
	sd_driver_cc2541_send_cmd( 55, 0x00000000 );
     
    sd_driver_cc2541_read_R1();
    
    // send the command
	sd_driver_cc2541_send_cmd( command, argument );	
}


/**
 * \fn      sd_driver_cc2541_makeCRC7(uint8_t *address, uint8_t length)
 * \brief   calcul the CRC7 
 * \param   length : number of byte needed to calcul CRC7
 * \param   address : adddress od data with the CRC7 is calculed
 * \return  the CRC7 checksum
 */
uint8_t sd_driver_cc2541_makeCRC7(uint8_t *address, uint8_t length)
{
    uint8_t crc = 0;
    uint8_t data;
    uint8_t packet[10];
    uint8_t i;
    uint8_t a;
  
    for(i = 0;i < length; i++)
    {
        packet[i] = address[i];
    }
  
    for (a=0;a<5;a++) //Loop through the packet array starting at packet[0]
    {
        data=packet[a];// Loop through the bits in the current array index starting at 0
	for (i=0;i<8;i++)
	{
		crc <<= 1;
		if ((((data & 0x80)^(crc & 0x80)) != 0))
		{
                  crc ^= 0x09;
		}
		data <<= 1;
	}   // End Inner for loop
  }// End outer for loop

  crc = (crc<<1) | 1;

return(crc);
  
}

/**
 * \fn      sd_driver_cc2541_makeCRC16(uint8_t *address, uint8_t length)
 * \brief   calcul the CRC16 
 * \param   length : number of byte needed to calcul CRC16
 * \param   address : adddress od data with the CRC16 is calculed
 * \return  the CRC16 checksum
 */
uint16_t sd_driver_cc2541_makeCRC16(uint8_t *address, uint16_t length)
{
    unsigned char x;
    unsigned short crc = 0xFFFF;

    while (length--){
        x = crc >> 8 ^ *address++;
        x ^= x>>4;
        crc = (crc << 8) ^ ((unsigned short)(x << 12)) ^ ((unsigned short)(x <<5)) ^ ((unsigned short)x);
    }
    return crc;
}

/**
 * \fn      sd_driver_cc2541_write() 
 * \brief   write one byte on SD card
 * \param   the first address on the sd card where we begin write data   
 * \param   number of byte of the data (max : 256 bytes)
 * \param   data to send 
 * \return  
 */
void sd_driver_cc2541_write(uint32_t data_address , uint16_t length , uint8_t *data)
{
  uint8_t i;
  uint8_t responseR1, dummy = 0x00;
  
  // send cmd24
  
  
  do{   
        sd_driver_cc2541_send_cmd(24, data_address);
        responseR1 = sd_driver_cc2541_read_R1();
        i++;
  }while(responseR1 != 0 && i< 128);
    
  //send data
  sd_driver_cc2541_send_data_packet(data_token1, length , data);
  
    i = 0;
    do{
      //spi_driver_cc2541_read( 1 , &responseR1 );
      sd_spi_transmit_receive( &dummy, &responseR1, 1);
      //timer_driver_cc2541_wait_1ms(1);
  }while(responseR1 != 0xFF);  
}
  
/**
 * \fn      sd_driver_cc2541_send_data_packet() 
 * \brief   write one byte on SD card
 * \param   the first address on the sd card where we begin write data   
 * \param   number of byte of the data (max : 512 bytes)
 * \param   data to send 
 */
void sd_driver_cc2541_send_data_packet(uint32_t data_token , uint16_t length , const uint8_t *data)
{
    	
	uint16_t i;
    //uint16_t crc;
    
	//data_token 
    //buffer[0] = 0xFF;
	buffer[0] = data_token;
    
    //send data
    for(i=0; i<length ; i++){
        buffer[i+1] = data[i];
    }
    
    //calcul sur crc16
    //crc = sd_driver_cc2541_makeCRC16(buffer , length + 2);       crc is not used here to gain time
    
    //add crc16
    buffer[length+1] = 0;//(uint8_t)(crc >> 8);
    buffer[length+2] = 0;//(uint8_t)(crc);
	
	// write the commande on SPI
	//spi_driver_cc2541_write(length+3,buffer);
	sd_spi_transmit_receive( buffer, buffer, length+3);
}


/**
 * \fn      sd_driver_cc2541_read_data_packet() 
 * \brief   write one byte on SD card
 * \param   number of byte of the data (max : 512 bytes)
 * \param   data to send 
 */
void sd_driver_cc2541_read_data_packet( uint8_t *data)
{
	uint8_t tab[512] = {0};
    //spi_driver_cc2541_read(512, data);
    sd_spi_transmit_receive(tab, data, 512);
}

/**
 * \fn      uint8_t sd_driver_cc2541_read_R1( void )
 * \brief   read the R1 responce of SD card
 *
 * +-------------------------------------------------+
 * | 0 | arg | addr | seq | crc | cmd | erase | idle |
 * +-------------------------------------------------+
 * \return  return the R1 responce
 */
uint8_t sd_driver_cc2541_read_R1( void )
{
    uint8_t buffer_to_read;
    uint8_t i;
    
    i = 0;
    do{
        
    // read the R response
    //spi_driver_cc2541_read( 1 , &buffer_to_read );
    sd_spi_transmit_receive(&buffer_to_read, &buffer_to_read, 1);
    }while(i++ < 127 && (buffer_to_read == 0xFF));
           
    // return the response
    return buffer_to_read;
    
}

/**
 * \fn      uint8_t sd_driver_cc2541_read_R7_or_R3( void )
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
 * |                    0CR 
 * +------------------------------------------------------------------------+
 * \param   pointer to return the response R7 or R3
 * \return  return the R1 responce
 */
uint8_t sd_driver_cc2541_read_R7_or_R3( uint8_t *responseR7 )
{
    uint8_t responseR1;
    
    responseR1 = sd_driver_cc2541_read_R1();
    
    // read the R7 response
    //spi_driver_cc2541_read( 4 , responseR7 );
    sd_spi_transmit_receive(responseR7, responseR7, 4);
    // return the R1 response
    return responseR1;
    
}


