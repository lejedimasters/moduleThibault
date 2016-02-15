/*
 *  Théo Folin
 *  2016
 * 	lsm_driver.h
 *
 * A REFAIRE
 *
 *
 * */


#ifndef LSM9_DRIVER_H
#define LSM9_DRIVER_H

#include "lsm9_spi.h"
#include "error.h"

ERROR_status lsm9_driver_init();
ERROR_status lsm9_driver_get_data();

ERROR_status lsm9_driver_get_accelerometry();
ERROR_status lsm9_driver_get_gyroscope();
ERROR_status lsm9_driver_get_magnotemeter();

ERROR_status lsm9_driver_write_register(uint8_t reg, uint8_t value);
ERROR_status lsm9_driver_read_register(uint8_t reg, uint8_t value);
ERROR_status lsm9_driver_write_registers(uint8_t reg, uint8_t *value, uint8_t size);
ERROR_status lsm9_driver_read_registers(uint8_t reg, uint8_t *value, uint8_t size);
typedef struct
{
	int16_t X;
	int16_t Y;
	int16_t Z;
}acc_data_typedef;

typedef struct
{
	int16_t X;
	int16_t Y;
	int16_t Z;
}gyr_data_typedef;

typedef struct
{
	int16_t X;
	int16_t Y;
	int16_t Z;
}mag_data_typedef;

typedef struct
{
	acc_data_typedef	accelerometry;
	gyr_data_typedef	gyroscope;
	mag_data_typedef	magnotemeter;
	//ERROR_status			error;
}lsm9_data_typedef;





/* */
#define REG_WHOAMI_ADDR		(0x0F)	/** Who am i address register */
#define REG_CNTRL0_ADDR		(0x1F)	/** CNTRL0 address register */
#define REG_CNTRL1_ADDR		(0x20)	/** CNTRL1 address register */
#define REG_CNTRL2_ADDR		(0x21)	/** CNTRL2 address register */
#define REG_CNTRL3_ADDR		(0x22)	/** CNTRL3 address register */
#define REG_CNTRL4_ADDR		(0x23)	/** CNTRL4 address register */
#define REG_CNTRL5_ADDR		(0x24)	/** CNTRL5 address register */
#define REG_CNTRL6_ADDR		(0x25)	/** CNTRL6 address register */
#define REG_CNTRL7_ADDR		(0x26)	/** CNTRL7 address register */


#define SPI_READ	0x80
#define SPI_WRITE	0x00

#define NO_INC		0b00000000
#define INC			0b01000000

#endif
