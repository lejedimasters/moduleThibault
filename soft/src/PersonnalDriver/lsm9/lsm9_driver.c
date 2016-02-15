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

ERROR_status lsm9_driver_init(){

	lsm9_spi_init();

	//lsm9_driver_write_register()

	return ERROR_status_NOERROR;
}


ERROR_status lsm9_driver_get_data( lsm9_data_typedef *data){


	return ERROR_status_NOERROR;
}

ERROR_status lsm9_driver_get_accelerometry( acc_data_typedef *data ){


	return ERROR_status_NOERROR;
}

ERROR_status lsm9_driver_get_gyroscope( gyr_data_typedef *data){


	return ERROR_status_NOERROR;
}

ERROR_status lsm9_driver_get_magnotemeter( mag_data_typedef *data){


	return ERROR_status_NOERROR;
}

ERROR_status lsm9_driver_write_register(uint8_t reg, uint8_t *value, uint8_t size){


	return ERROR_status_NOERROR;
}

ERROR_status lsm9_driver_read_register(uint8_t reg, uint8_t *value, uint8_t size){


	return ERROR_status_NOERROR;
}
