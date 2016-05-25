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



/* MACRO ULTRA APPROXIMATIVE  !!!!*/
#define DELAY_1MS() 	{uint32_t i;						\
						for(i = 0 ; i < (500000/350) ; i++ ){};	\
	}

/* MACRO ULTRA APPROXIMATIVE  !!!!*/
#define DELAY_N_MS(n)	{uint32_t i;						\
						for(i = 0 ; i < n ; i++ ){DELAY_1MS()};	\
	}

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

	uint8_t val[5]={0,0,0,0,0};
	static cpt = 0;


	lsm9_spi_init(1);
	cpt++;
	if( cpt > 8){
		cpt = 0;
	}


	DELAY_N_MS(500);

/*
	      // Initialisation accéléromètre/magnétomètre
	      lsm9_driver_write_register(REG_CNTRL0_ADDR, 0b10000000, lsm9_sensor_typedef_XM); // Reset
	      lsm9_driver_write_register(REG_CNTRL1_ADDR, LSM9DS0_ACC_ODR100|ENABLE_ALL_AXES, lsm9_sensor_typedef_XM);
	      lsm9_driver_write_register(REG_CNTRL2_ADDR, 0b00100000 , lsm9_sensor_typedef_XM); // ±16 g
	      lsm9_driver_write_register(REG_CNTRL5_ADDR, 0b01100000|TEMP_ON|LSM9DS0_MAG_ODR100, lsm9_sensor_typedef_XM);//  high resoluation
	      lsm9_driver_write_register(REG_CNTRL6_ADDR, 0b01100000, lsm9_sensor_typedef_XM); // ± 12 gauss
	      lsm9_driver_write_register(REG_CNTRL7_ADDR, 0b00000000, lsm9_sensor_typedef_XM); //Continuous-conversion mode

	      // Initialisation gyroscope
	      lsm9_driver_write_register(CTRL_REG5, 0x80, lsm9_sensor_typedef_G);				 // Reset
	      lsm9_driver_write_register(CTRL_REG1, ODR190|BW11|PM_NORMAL|ENABLE_ALL_AXES, lsm9_sensor_typedef_G);
	      lsm9_driver_write_register(CTRL_REG4, 0b00000000,lsm9_sensor_typedef_G); // 250 dps
*/


	lsm9_driver_read_register(0x0F,val,lsm9_sensor_typedef_G);

	if( (val[0] != 0xFF) && (val[0] != 0x00)){
		DELAY_N_MS(1);
	}

/*	if( (val[0] == 0x3D) && (val[0] == 0x68)){
		DELAY_N_MS(1);
	}

	lsm9_driver_read_register(0x0F,val,lsm9_sensor_typedef_X);

	if( (val[0] == 0x3D) && (val[0] == 0x68)){
		DELAY_N_MS(1);
	}


	lsm9_driver_read_register(0x0F,val,lsm9_sensor_typedef_M);

	if( (val[0] != 0xFF) && (val[0] != 0x00)){
		DELAY_N_MS(1);
	}
*/

			lsm9_driver_write_register(0x22, 0b10000000, lsm9_sensor_typedef_G); // Reset ACC/GYR
			lsm9_driver_write_register(0x21, 0b00001000, lsm9_sensor_typedef_M); // CTRL_REG2_M, reset MAG
		// Accéléro Gyroscope
			lsm9_driver_write_register(0x10, 0b01100000|0b00011000, lsm9_sensor_typedef_G); // CTRL_REG1_G, ODR 119Hz, 2000dps, defaut bandwitch
			lsm9_driver_write_register(0x1E, 0b00111000, lsm9_sensor_typedef_G); // CTRL_REG4, x,y,z Gyr enable
			lsm9_driver_write_register(0x1F, 0b00111000, lsm9_sensor_typedef_G); //CTRL_REG5_XL, x,y,z Acc enable
			lsm9_driver_write_register(0x20, 0b01100000|0b00011000, lsm9_sensor_typedef_G); // CTRL_REG6_XL, ODR 119 Hz
			lsm9_driver_read_register(0x20, val, lsm9_sensor_typedef_G);
			lsm9_driver_write_register(0x22, 0b01000100, lsm9_sensor_typedef_G); // continuous update, auto @ increment
			lsm9_driver_read_register(0x22, val, lsm9_sensor_typedef_G);
			lsm9_driver_write_register(0x22, 0b01000100, lsm9_sensor_typedef_G); // continuous update, auto @ increment
			lsm9_driver_read_register(0x22, val, lsm9_sensor_typedef_G);
			lsm9_driver_write_register(0x22, 0b01000100, lsm9_sensor_typedef_G); // continuous update, auto @ increment
			lsm9_driver_read_register(0x22, val, lsm9_sensor_typedef_G);
			lsm9_driver_write_register(0x2E, 0b11000000, lsm9_sensor_typedef_G); // fifo continuous mode, fifo threshold = 0

		// Magnétomètre
			lsm9_driver_write_register(0x20, 0b00011100|0b00000010, lsm9_sensor_typedef_M); // CTRL_REG1_M, ODR 80Hz, FAST ODR







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
	uint8_t readTab[7];

	lsm9_driver_read_registers(0x28,readTab,6,lsm9_sensor_typedef_G);
	lsm9_driver_read_register(0x18,readTab,lsm9_sensor_typedef_G);
	lsm9_driver_read_register(0x19,readTab,lsm9_sensor_typedef_G);
	lsm9_driver_read_register(0x1A,readTab,lsm9_sensor_typedef_G);

	lsm9_driver_get_accelerometry(&data->accelerometry);
	lsm9_driver_get_magnotemeter(&data->magnotemeter);
	lsm9_driver_get_gyroscope(&data->gyroscope);

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

	lsm9_driver_read_registers(0x28,readTab,7,lsm9_sensor_typedef_X);
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

	lsm9_driver_read_registers(0x18,readTab,7,lsm9_sensor_typedef_G);
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

	lsm9_driver_read_registers(0x28,readTab,7,lsm9_sensor_typedef_M);
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



	/* ERROR CHECK
	if( reg & (SPI_READ | NO_INC) ){
		return -1;
	}*/
	/* END OF ERROR CHECK*/



	if( sensor == lsm9_sensor_typedef_X ){
		lsm9_spi_transmit_receive_XG(readTab,readTab,2);
	}
	else if( sensor == lsm9_sensor_typedef_M ) {
		lsm9_spi_transmit_receive_M( readTab, readTab, 2);
	}
	else if( sensor == lsm9_sensor_typedef_G ) {
		lsm9_spi_transmit_receive_XG(readTab,readTab,2);
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



	/* ERROR CHECK
	if( reg & (SPI_WRITE | NO_INC) ){
		return -1;
	}*/
	/* END OF ERROR CHECK*/



	if( sensor == lsm9_sensor_typedef_X ){
		lsm9_spi_transmit_receive_XG(readTab,readTab,2);
	}
	else if( sensor == lsm9_sensor_typedef_M ) {
		lsm9_spi_transmit_receive_M( readTab, readTab, 2);
	}
	else if( sensor == lsm9_sensor_typedef_G ) {
		lsm9_spi_transmit_receive_XG(readTab,readTab,2);
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
	/*
	if( reg & (SPI_READ | NO_INC) ){
		return -1;
	}
*/
	if( size > NB_MAX_DATA ){
		return -1;
	}
	/* END OF ERROR CHECK*/

	/* condition lolilol pour le MAG et pas les autres....*/
	if( sensor == lsm9_sensor_typedef_M ){
		readTab[0] = SPI_WRITE | INC | reg;
	}
	else{
		readTab[0] = SPI_WRITE | reg;
	}
	for(i = 1 ; i < size ; i++ ){
		readTab[i] = value[i-1];
	}

	if( sensor == lsm9_sensor_typedef_X ){
		lsm9_spi_transmit_receive_XG( readTab, readTab, size);
	}
	else if( sensor == lsm9_sensor_typedef_M ) {
		lsm9_spi_transmit_receive_M( readTab, readTab, size);
	}
	else if( sensor == lsm9_sensor_typedef_G ) {
		lsm9_spi_transmit_receive_XG( readTab, readTab, size);
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
 * \deprecatedk
 *            SLD_
*/
ERROR_status lsm9_driver_read_registers(uint8_t reg, uint8_t *value, uint8_t size, lsm9_sensor_typedef sensor){
	uint8_t readTab[NB_MAX_DATA] ={0,0,0,0,0,0,0,0,0,0};
	uint8_t i;

	/* ERROR CHECK*/
	/*
	if( reg & (SPI_READ | NO_INC) ){
		return -1;
	}
*/
	if( size > NB_MAX_DATA ){
		return -1;
	}
	/* END OF ERROR CHECK*/


	/* condition lolilol pour le MAG et pas les autres....*/
	if( sensor == lsm9_sensor_typedef_M ){
		readTab[0] = SPI_READ | INC | reg;
	}
	else{
		readTab[0] = SPI_READ | reg;
	}
	//readTab[1] = value;

	if( sensor == lsm9_sensor_typedef_X ){
		lsm9_spi_transmit_receive_XG( readTab, readTab, size);
	}
	else if( sensor == lsm9_sensor_typedef_M ) {
		lsm9_spi_transmit_receive_M( readTab, readTab, size);
	}
	else if( sensor == lsm9_sensor_typedef_G ) {
		lsm9_spi_transmit_receive_XG( readTab, readTab, size);
	}
	else{
		return -1;
	}


	for( i = 1 ; i < size ; i++ ){
		value[i-1] = readTab[i];
	}

	return ERROR_status_NOERROR;
}
