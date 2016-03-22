/*-----------------------------------------------------------------------*/
/* Low level disk I/O module skeleton for FatFs     (C)ChaN, 2014        */
/*-----------------------------------------------------------------------*/
/* If a working storage control module is available, it should be        */
/* attached to the FatFs via a glue function rather than modifying it.   */
/* This is an example of glue functions to attach various exsisting      */
/* storage control modules to the FatFs module with a defined API.       */
/*-----------------------------------------------------------------------*/

#include "diskio.h"		/* FatFs lower layer API */


/* Definitions of physical drive number for each drive */
#define ATA		0	/* Example: Map ATA harddisk to physical drive 0 */
#define MMC		1	/* Example: Map MMC/SD card to physical drive 1 */
#define USB		2	/* Example: Map USB MSD to physical drive 2 */


/*-----------------------------------------------------------------------*/
/* Get Drive Status                                                      */
/*-----------------------------------------------------------------------*/

DSTATUS disk_status (
	BYTE pdrv		/* Physical drive nmuber to identify the drive */
)
{
	/*
	if (SD_Detect() != SD_PRESENT) {
		return STA_NOINIT;
	}

	if (!TM_FATFS_SDIO_WriteEnabled()) {
		TM_FATFS_SD_SDIO_Stat |= STA_PROTECT;
	} else {
		TM_FATFS_SD_SDIO_Stat &= ~STA_PROTECT;
	}

	return TM_FATFS_SD_SDIO_Stat;
	*/
	return RES_OK;
}



/*-----------------------------------------------------------------------*/
/* Inidialize a Drive                                                    */
/*-----------------------------------------------------------------------*/

DSTATUS disk_initialize (
	BYTE pdrv				/* Physical drive nmuber to identify the drive */
)
{
	uint8_t responseR1, i = 0;
    uint8_t responseR7_or_R3[4], CardType;
    CardType = 0;
	//sd_spi_deinit();
	sd_spi_init_low_speed();

	//Check disk initialized
	//Wait 1ms to be sure the card is correctly supply
	WAIT_N_MS(500);
    //dummy clock : to send at least dummy 74 clock cycles before sending any commands
    dummyclock();

    sd_spi_send_cmd(0, 0x00000000);
    // check R1 responce
    responseR1 = sd_spi_read_R1();

    if(responseR1 != 1){
         return RES_ERROR;
    }
    //send CMD8
    sd_spi_send_cmd(8, 0x000001AA);

    //check the version of the sd card
    responseR1 = sd_spi_read_R7_or_R3(responseR7_or_R3);
        if(responseR1 == 1){
            CardType = 2;
            if ( responseR7_or_R3[2] != 0x01 || responseR7_or_R3[3] != 0xAA ) {
                return RES_ERROR;
            }
        }
        else{
            CardType = 1;
        }

    responseR1 = 1;
    i = 0;
    while( responseR1 != 0 ){

        //send ACMD41
        sd_spi_send_acmd(41, 0x40000000);

        //check R1 responce
         responseR1 = sd_spi_read_R1();

         i++;

         if(i == 100){
             return RES_ERROR;
         }
    }

    if( CardType == 2)
    {
        //send CMD58
        sd_spi_send_cmd(58, 0x00000000);

        //check CCS bit in OCR
         responseR1 = sd_spi_read_R7_or_R3(responseR7_or_R3);

         if((responseR7_or_R3[3] & 0xC0) != 0)
             return RES_ERROR;
    }


    //send CMD16
    sd_spi_send_cmd(16, 0x00000200);

    // the Sd card is initialized

    // no crc
    sd_spi_send_cmd(59, 0x00000200);

    // change the speed of SPI
    sd_spi_init_high_speed();

    return RES_OK;
}



/*-----------------------------------------------------------------------*/
/* Read Sector(s)                                                        */
/*-----------------------------------------------------------------------*/

DRESULT disk_read (
	BYTE pdrv,		/* Physical drive nmuber to identify the drive */
	BYTE *buff,		/* Data buffer to store read data */
	DWORD sector,	/* Sector address in LBA */
	UINT count		/* Number of sectors to read */
)
{

	uint32_t address = 0;
	uint8_t responseR1, i = 0;

	address = sector*SECTOR_SIZE;

	do{
		sd_spi_send_cmd(17, address);
		responseR1 = sd_spi_read_R1();
		i++;
	}while(responseR1 != 0 && i< 128);
	//while (((tmp & 0x80) != 0) && i < SD_CMD_TIMEOUT);
	if( i > 128 ){

		return RES_ERROR;
	}
	/*
	responseR1 = sd_spi_read_R1();
	responseR1 = sd_spi_read_R1();
	responseR1 = sd_spi_read_R1();
	responseR1 = sd_spi_read_R1();
	responseR1 = sd_spi_read_R1();
*/
	for( i = 0 ; i < count ; i++ ){
		sd_spi_read_data_packet(DATA_TOKEN_CMD17, SECTOR_SIZE, (buff+i*SECTOR_SIZE) );
	}


	/*
	sd_spi_send_cmd(12, 0);

	// wait one byte
	sd_spi_read_R1();
	//command response
	responseR1 = sd_spi_read_R1();
*/

    return RES_OK;
}



/*-----------------------------------------------------------------------*/
/* Write Sector(s)                                                       */
/*-----------------------------------------------------------------------*/

#if _USE_WRITE
DRESULT disk_write (
	BYTE pdrv,			/* Physical drive nmuber to identify the drive */
	const BYTE *buff,	/* Data to be written */
	DWORD sector,		/* Sector address in LBA */
	UINT count			/* Number of sectors to write */
)
{

	uint32_t address = 0;
	uint8_t responseR1, i = 0;

	address = sector*SECTOR_SIZE;

	// send cmd25 and wait for cmd accepted
	do{
		sd_spi_send_cmd(25, address);
		responseR1 = sd_spi_read_R1();
		i++;
	}while(responseR1 != 0 && i< 128);

	if( i > 128 ){

		return RES_ERROR;
	}

	// wait one byte
	sd_spi_read_R1();

	for( i = 0 ; i < count ; i++ ){

		// Send cmd until no error / Risque de GROS blocage
		do{
			// Data packet
			sd_spi_send_data_packet(DATA_TOKEN_CMD18, SECTOR_SIZE, (buff+i*SECTOR_SIZE) );
			// Data resp
			responseR1 = sd_spi_read_R1();
		}while( (responseR1 & 0b00001110) != 0b00000100);

		//Busy test
	    do{
	    	responseR1 = sd_spi_read_R1();
	    }while(responseR1 != 0xFF);


	}

	// stop transaction
	sd_spi_send_stop();

	// Wait one byte
	sd_spi_read_R1();

	//Busy test
    do{
    	responseR1 = sd_spi_read_R1();
    }while(responseR1 != 0xFF);

    return RES_OK;
}
#endif


/*-----------------------------------------------------------------------*/
/* Miscellaneous Functions                                               */
/*-----------------------------------------------------------------------*/

#if _USE_IOCTL
DRESULT disk_ioctl (
	BYTE pdrv,		/* Physical drive nmuber (0..) */
	BYTE cmd,		/* Control code */
	void *buff		/* Buffer to send/receive control data */
)
{

	switch (cmd) {
		case GET_SECTOR_SIZE :     // Get R/W sector size (WORD)
			*(WORD *) buff = 512;
		break;
		case GET_BLOCK_SIZE :      // Get erase block size in unit of sector (DWORD)
			*(DWORD *) buff = 32;
		break;
		case CTRL_SYNC :
		//case CTRL_ERASE_SECTOR :
		break;
		default:
			return RES_ERROR;
		break;
	}
	return RES_OK;
}
#endif

DWORD get_fattime (void){

	return 0;
}
