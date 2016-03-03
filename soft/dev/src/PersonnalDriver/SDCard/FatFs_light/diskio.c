/*-----------------------------------------------------------------------*/
/* Low level disk I/O module skeleton for Petit FatFs (C)ChaN, 2014      */
/*-----------------------------------------------------------------------*/

#include "diskio.h"
#include "sd_driver_cc2541.h"
#include "sd_spi.h"


BYTE test[516];

/*-----------------------------------------------------------------------*/
/* Initialize Disk Drive                                                 */
/*-----------------------------------------------------------------------*/

DSTATUS disk_initialize (void)
{
    UINT res;
        res = 0;
        while(res == 0){
            res = sd_driver_cc2541_init();
        }
	return 0;
}



/*-----------------------------------------------------------------------*/
/* Read Partial Sector                                                   */
/*-----------------------------------------------------------------------*/

DRESULT disk_readp (
	BYTE* buff,		/* Pointer to the destination object */
	DWORD sector,	/* Sector number (LBA) */
	UINT offset,	/* Offset in the sector */
	UINT count		/* Byte count (bit15:destination) */
)
{   BYTE responseR1; 
	DRESULT res;
	BYTE buffer_to_read, buffer_to_write = 0x00;
    UINT i;

	res = RES_ERROR;
    i = 0;
    
    sector *= 512;
    
    do{
        sd_driver_cc2541_send_cmd( 17, sector );   
        responseR1 = sd_driver_cc2541_read_R1();
        i++;
    }while(responseR1 != 0 && i< 5);
    
    if(responseR1 ==0){
        i = 0;
        buffer_to_read = 0;
        
        do{
        	sd_spi_transmit_receive( &buffer_to_write, &buffer_to_read, 1);
            //spi_driver_cc2541_read( 1 , &buffer_to_read );
        }while(i++ < 127 && (buffer_to_read != 0xFE));
    
        test[0]=buffer_to_read;  
        for(i = 1; i<514;i++){
            //spi_driver_cc2541_read( 1 , &test[i] );
            sd_spi_transmit_receive( &buffer_to_write, &test[i], 1);
        }
        
        for(i = 0; i <count;i++){
      
            buff[i] = test[i+offset+1];  
      
        }
        res =  RES_OK;       
    }
    return res;
}



/*-----------------------------------------------------------------------*/
/* Write Partial Sector                                                  */
/*-----------------------------------------------------------------------*/

DRESULT disk_writep (
	const BYTE* buff,		/* Pointer to the data to be written, NULL:Initiate/Finalize write operation */
	DWORD sc		/* Sector number (LBA) or Number of bytes to send */
)
{
	DRESULT res;
	UINT bc;
	static WORD wc;
    BYTE tosend[2], buffer_to_write = 0x00;
    BYTE responseR1;
	res = RES_ERROR;
    UINT i;

	if (buff) {		/* Send data bytes */
        bc = (WORD)sc;
        while (bc && wc) {		/* Send data bytes to the card */
            tosend[0] = *buff++;
            //spi_driver_cc2541_write(1,tosend);
            sd_spi_transmit_receive( tosend, tosend, 1);

            wc--; bc--;   
        }
        res = RES_OK;
	} 
    else {
		if (sc) {	/* Initiate sector write transaction */
            do{
                sd_driver_cc2541_send_cmd( 24, sc );   
                responseR1 = sd_driver_cc2541_read_R1();
                i++;
            }while(responseR1 != 0 && i< 5);
            tosend[0] = 0xFF;
            tosend[1] = 0xFE;
            //spi_driver_cc2541_write(2,tosend);
            sd_spi_transmit_receive( tosend, tosend, 2);
            wc = 512;
            res = RES_OK;
		} 
        else {	/* Finalize sector write transaction */
            bc = wc + 2;
			while (bc--){
              tosend[0] = 0x00;
              //spi_driver_cc2541_write(1,tosend);
              sd_spi_transmit_receive( tosend, tosend, 1);
            } 	
			/* Receive data resp and wait for end of write process in timeout of 500ms */
            bc = 5000;
             do{ 
                responseR1 = sd_driver_cc2541_read_R1();
                bc--;
            }while(((responseR1 & 0x1F) == 0x05) & (bc != 0) );
            if(responseR1 == 0x05){
                res = RES_OK;
            }           
             do{ 
                 //spi_driver_cc2541_read( 1 , tosend );
                 sd_spi_transmit_receive( &buffer_to_write, tosend, 1);
                 WAIT_1MS();
            }while(tosend[0] != 0xFF);
		}
	}

	return res;
}

