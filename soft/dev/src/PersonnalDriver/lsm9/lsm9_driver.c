/*
 *  Théo Folin
 *  2016
 * 	lsm_driver.c
 *
 * A REFAIRE
 *
 *
 * */


#include "lsm9_driver.h"



/** \fn ERROR_status lsm9_driver_init(void)
 * \author T.Folin
 * \test
 * \brief	Initialisation of lsm9_driver :
 *             	Init spi
 *				Init register of lsm9
 * \deprecated
 *            SLD_
 */
ERROR_status lsm9_driver_init( void ){

	lsm9_spi_init();

	// Initialisation accéléromètre
	lsm9_driver_write_register(REG_CNTRL0_ADDR, 0b10000000, lsm9_sensor_typedef_XM);
	lsm9_driver_write_register(REG_CNTRL1_ADDR, 0b00011111, lsm9_sensor_typedef_XM);
	lsm9_driver_write_register(REG_CNTRL5_ADDR, 0b10011000, lsm9_sensor_typedef_XM);

	// Initialisation magnétomètre
	lsm9_driver_write_register(REG_GEN_MAG_ADDR, 0b10000000, lsm9_sensor_typedef_XM);
	lsm9_driver_write_register(REG_CNTRL1_ADDR, 0b00011111, lsm9_sensor_typedef_XM);
	lsm9_driver_write_register(REG_CNTRL5_ADDR, TEMP_ON|LSM9DS0_MAG_ODR100, lsm9_sensor_typedef_XM);//   0b11110100, lsm9_sensor_typedef_XM);
	lsm9_driver_write_register(REG_CNTRL7_ADDR, 0b00000000, lsm9_sensor_typedef_XM);

	return ERROR_status_NOERROR;
}
/** \fn ERROR_status lsm9_driver_get_data( lsm9_data_typedef *data)
 * \param[in] data, pointer on struct lsm9 data
 * \param[out] ERROR_status
 * \author T.Folin
 * \test
 * \brief		Get data of all sensor on lsm9
 * \deprecated
 *            SLD_
 */
ERROR_status lsm9_driver_get_data( lsm9_data_typedef *data){


	lsm9_driver_get_accelerometry(&data->accelerometry);
	lsm9_driver_get_gyroscope(&data->gyroscope);
	lsm9_driver_get_magnotemeter(&data->magnotemeter);

	return ERROR_status_NOERROR;
}
/** \fn ERROR_status lsm9_driver_get_accelerometry( acc_data_typedef *data )
 * \param[in] data, pointer on struct lsm9 accelerometry data
 * \param[out] ERROR_status
 * \author T.Folin
 * \test
 * \brief	Get accelerometry data on lsm9
 * \deprecated
 *            SLD_
 */
ERROR_status lsm9_driver_get_accelerometry( acc_data_typedef *data ){
	uint8_t readTab[8] ={0,0,0,0,0,0,0,0};

	lsm9_driver_read_registers(REG_ACC_DATA_ADDR,readTab,7,lsm9_sensor_typedef_XM);
	data->X = readTab[1]*256 + readTab[0];
	data->Y = readTab[3]*256 + readTab[2];
	data->Z = readTab[5]*256 + readTab[4];

	return ERROR_status_NOERROR;
}
/** \fn ERROR_status lsm9_driver_get_gyroscope( gyr_data_typedef *data)
 * \param[in] data, pointer on struct lsm9 gyroscope data
 * \param[out] ERROR_status
 * \author T.Folin
 * \test
 * \brief		Get gyroscope data on lsm9
 * \deprecated
 *            SLD_
 */
ERROR_status lsm9_driver_get_gyroscope( gyr_data_typedef *data){
	uint8_t readTab[8] ={0,0,0,0,0,0,0,0};

	lsm9_driver_read_registers(REG_GYR_DATA_ADDR,readTab,7,lsm9_sensor_typedef_G);
	data->X = readTab[1]*256 + readTab[0];
	data->Y = readTab[3]*256 + readTab[2];
	data->Z = readTab[5]*256 + readTab[4];

	return ERROR_status_NOERROR;
}
/** \fn ERROR_status lsm9_driver_get_magnotemeter( mag_data_typedef *data)
 * \param[in] data, pointer on struct lsm9 magnotemeter data
 * \param[out] ERROR_status
 * \author T.Folin
 * \test
 * \brief		Get magnotemeter data on lsm9
 * \deprecated
 *            SLD_
 */
ERROR_status lsm9_driver_get_magnotemeter( mag_data_typedef *data){
	uint8_t readTab[8] ={0,0,0,0,0,0,0,0};

	lsm9_driver_read_registers(REG_MAG_DATA_ADDR,readTab,7,lsm9_sensor_typedef_XM);
	data->X = readTab[1]*256 + readTab[0];
	data->Y = readTab[3]*256 + readTab[2];
	data->Z = readTab[5]*256 + readTab[4];
	return ERROR_status_NOERROR;
}
/** \fn ERROR_status lsm9_driver_write_register(uint8_t reg, uint8_t value, lsm9_sensor_typedef sensor)
 * \param[in] reg, adress of register to write
 * \param[in] value, value to write in register
 * \param[in] sensor, requested sensor
 * \param[out] ERROR_status
 * \author T.Folin
 * \test
 * \brief		Function for write a value in a lsm9 register
 * \deprecated
 *            SLD_
 */
ERROR_status lsm9_driver_write_register(uint8_t reg, uint8_t value, lsm9_sensor_typedef sensor){
	uint8_t readTab[2] ={0,0};


	readTab[0] = SPI_WRITE | NO_INC | reg;
	readTab[1] = value;



	/* ERROR CHECK*/
	if( reg & (SPI_READ | NO_INC) ){
		return -1;
	}
	/* END OF ERROR CHECK*/



	if( sensor == lsm9_sensor_typedef_XM ){
		lsm9_spi_transmit_receive_XM(readTab,readTab,2);

	}
	else if( sensor == lsm9_sensor_typedef_G ) {
		lsm9_spi_transmit_receive_G( readTab, readTab, 2);
	}
	else{

		return -1;
	}
	return ERROR_status_NOERROR;
}
/** \fn ERROR_status lsm9_driver_read_register(uint8_t reg, uint8_t value, lsm9_sensor_typedef sensor)
 * \param[in] reg, address of register to read
 * \param[in] value,
 * \param[in] sensor, requested sensor
 * \param[out] ERROR_status
 * \author T.Folin
 * \test
 * \brief	Function for read a value in a lsm9 register
 * \deprecated
 *            SLD_
 */
ERROR_status lsm9_driver_read_register(uint8_t reg, uint8_t *value, lsm9_sensor_typedef sensor){
	uint8_t readTab[2] ={0,0};


	readTab[0] = SPI_READ | NO_INC | reg;



	/* ERROR CHECK*/
	if( reg & (SPI_READ | NO_INC) ){
		return -1;
	}
	/* END OF ERROR CHECK*/



	if( sensor == lsm9_sensor_typedef_XM ){
		lsm9_spi_transmit_receive_XM(readTab,readTab,2);

	}
	else if( sensor == lsm9_sensor_typedef_G ) {
		lsm9_spi_transmit_receive_G( readTab, readTab, 2);
	}
	else{

		return -1;
	}

	value[0] = readTab[1];

	return ERROR_status_NOERROR;
}
/** \fn ERROR_status lsm9_driver_write_registers(uint8_t reg, uint8_t *value, uint8_t size, lsm9_sensor_typedef sensor)
 * \param[in] reg, first address of register to write
 * \param[in] value, values to write in register
 * \param[in] size, number of register to read
 * \param[in] sensor, requested sensor
 * \param[out] ERROR_status
 * \author T.Folin
 * \test
 * \brief		Function for write values in some lsm9 register
 * \deprecated
 *            SLD_
 */
ERROR_status lsm9_driver_write_registers(uint8_t reg, uint8_t *value, uint8_t size, lsm9_sensor_typedef sensor){
	uint8_t readTab[NB_MAX_DATA] ={0,0,0,0,0,0,0,0,0,0};
	uint8_t i;

	/* ERROR CHECK*/
	if( reg & (SPI_READ | NO_INC) ){
		return -1;
	}

	if( size > NB_MAX_DATA ){
		return -1;
	}
	/* END OF ERROR CHECK*/

	readTab[0] = SPI_WRITE | INC | reg;
	for(i = 1 ; i < size ; i++ ){
		readTab[i] = value[i-1];
	}

	if( sensor == lsm9_sensor_typedef_XM ){
		lsm9_spi_transmit_receive_XM( readTab, readTab, size);
	}
	else if( sensor == lsm9_sensor_typedef_G ) {
		lsm9_spi_transmit_receive_G( readTab, readTab, size);
	}
	else{

		return -1;
	}
	return ERROR_status_NOERROR;
}
/** \fn ERROR_status lsm9_driver_read_registers(uint8_t reg, uint8_t *value, uint8_t size, lsm9_sensor_typedef sensor)
 * \param[in] reg, first address of register to read
 * \param[in] value, array for read value in register
 * \param[in] size, number of register to read
 * \param[in] sensor, requested sensor
 * \param[out] ERROR_status
 * \author T.Folin
 * \test
 * \brief	Function for read values in some lsm9 register
 * \deprecated
 *            SLD_
*/
ERROR_status lsm9_driver_read_registers(uint8_t reg, uint8_t *value, uint8_t size, lsm9_sensor_typedef sensor){
	uint8_t readTab[NB_MAX_DATA] ={0,0,0,0,0,0,0,0,0,0};
	uint8_t i;

	/* ERROR CHECK*/
	if( reg & (SPI_READ | NO_INC) ){
		return -1;
	}

	if( size > NB_MAX_DATA ){
		return -1;
	}
	/* END OF ERROR CHECK*/


	readTab[0] = SPI_READ | INC | reg;
	//readTab[1] = value;

	if( sensor == lsm9_sensor_typedef_XM ){
		lsm9_spi_transmit_receive_XM( readTab, readTab, size);
	}
	else if( sensor == lsm9_sensor_typedef_G ) {
		lsm9_spi_transmit_receive_G( readTab, readTab, size);
	}
	else{
		return -1;
	}


	for( i = 1 ; i < size ; i++ ){
		value[i-1] = readTab[i];
	}

	return ERROR_status_NOERROR;
}
