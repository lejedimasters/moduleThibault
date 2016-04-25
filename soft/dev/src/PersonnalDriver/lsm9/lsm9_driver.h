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
#include "lsm9_register_XM_def.h"
#include "lsm9_register_G_def.h"
#include "error.h"





#define SPI_READ	0x80
#define SPI_WRITE	0x00

#define NO_INC		0b00000000
#define INC			0b01000000

#define NB_MAX_DATA	10

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
	uint32_t			time_ms;
}lsm9_data_typedef;

typedef enum
{
	lsm9_sensor_typedef_X,
	lsm9_sensor_typedef_G,
	lsm9_sensor_typedef_M
}lsm9_sensor_typedef;


ERROR_status lsm9_driver_init();
ERROR_status lsm9_driver_get_data();

ERROR_status lsm9_driver_get_accelerometry();
ERROR_status lsm9_driver_get_gyroscope();
ERROR_status lsm9_driver_get_magnotemeter();

ERROR_status lsm9_driver_write_register(uint8_t reg, uint8_t value, lsm9_sensor_typedef sensor);
ERROR_status lsm9_driver_read_register(uint8_t reg, uint8_t *value, lsm9_sensor_typedef sensor);
ERROR_status lsm9_driver_write_registers(uint8_t reg, uint8_t *value, uint8_t size, lsm9_sensor_typedef sensor);
ERROR_status lsm9_driver_read_registers(uint8_t reg, uint8_t *value, uint8_t size, lsm9_sensor_typedef sensor);

#endif
