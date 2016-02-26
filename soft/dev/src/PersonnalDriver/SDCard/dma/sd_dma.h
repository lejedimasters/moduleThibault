/*
 *  Théo Folin
 *  2016
 * 	sd_dma.h
 *
 * A REFAIRE
 *
 *
 * */


#ifndef SD_DMA_H
#define SD_DMA_H

#include "stm32f4xx_hal.h"
#include "sd_spi.h"
#include "error.h"

void sd_dma_init();
void sd_dma_start();
void sd_dma_complete_IT();
void sd_dma_error_IT();
void sd_dma_set_flag_complete();
void sd_dma_get_flag_complete();



#endif
