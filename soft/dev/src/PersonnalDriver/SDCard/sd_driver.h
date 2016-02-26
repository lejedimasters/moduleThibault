/*
 *  Théo Folin
 *  2016
 * 	sd_driver.h
 *
 * A REFAIRE
 *
 *
 * */


#ifndef SD_DRIVER_H
#define SD_DRIVER_H

#include "stm32f4xx_hal.h"
#include "sd_spi.h"
#include "ff.h"
#include "error.h"
#include "lsm9_driver.h"

void sd_driver_init();
ErrorStatus sd_driver_fill_buffer(lsm9_data_typedef *data, uint32_t time_ms);


#endif
