
/*
 *  Théo Folin
 *  2016
 * 	diskio_subfunction.c
 *
 * A REFAIRE
 *
 *
 * */
#define FATFS_USE_WRITEPROTECT_PIN	0


SD_Error SD_Init (void)
{
	__IO SD_Error errorstatus = SD_OK;

	/* SDIO Peripheral Low Level Init */
	//SD_LowLevel_Init();
	SDIO_DeInit ();
	errorstatus = SD_PowerON ();

	if (errorstatus != SD_OK) {
		logf ("SD_PowerON failed\r\n");
		/*!< CMD Response TimeOut (wait for CMDSENT flag) */
		return (errorstatus);
	}

	logf ("SD_PowerON OK\r\n");

	errorstatus = SD_InitializeCards ();

	if (errorstatus != SD_OK) {
		logf ("SD_InitializeCards failed\r\n");
		/*!< CMD Response TimeOut (wait for CMDSENT flag) */
		return (errorstatus);
	}

	logf ("SD_InitializeCards OK\r\n");

	/*!< Configure the SDIO peripheral */
	/*!< SDIO_CK = SDIOCLK / (SDIO_TRANSFER_CLK_DIV + 2) */
	/*!< on STM32F4xx devices, SDIOCLK is fixed to 48MHz */
	SDIO_InitStructure.SDIO_ClockDiv = SDIO_TRANSFER_CLK_DIV;
	SDIO_InitStructure.SDIO_ClockEdge = SDIO_ClockEdge_Rising;
	SDIO_InitStructure.SDIO_ClockBypass = SDIO_ClockBypass_Disable;
	SDIO_InitStructure.SDIO_ClockPowerSave = SDIO_ClockPowerSave_Disable;
	SDIO_InitStructure.SDIO_BusWide = SDIO_BusWide_1b;
	SDIO_InitStructure.SDIO_HardwareFlowControl = SDIO_HardwareFlowControl_Disable;
	SDIO_Init (&SDIO_InitStructure);

	/*----------------- Read CSD/CID MSD registers ------------------*/
	errorstatus = SD_GetCardInfo (&SDCardInfo);

	if (errorstatus == SD_OK) {
		/*----------------- Select Card --------------------------------*/
		logf ("SD_GetCardInfo OK\r\n");
		errorstatus = SD_SelectDeselect ((uint32_t) (SDCardInfo.RCA << 16));
	}
	else {
		logf ("SD_SelectDeselect failed\r\n");
	}

	if (errorstatus == SD_OK) {
		logf ("SD_SelectDeselect OK\r\n");
#if FATFS_SDIO_4BIT == 1
		//4 bit mode
		errorstatus = SD_EnableWideBusOperation (SDIO_BusWide_4b);
#else
		//1 bit mode
		errorstatus = SD_EnableWideBusOperation (SDIO_BusWide_1b);
#endif
	}
	else {
		logf ("SD_EnableWideBusOperation failed\r\n");
	}

	if (errorstatus == SD_OK) {
		logf ("SD_EnableWideBusOperation OK\r\n");
	}

	return (errorstatus);
}






uint8_t TM_FATFS_SDIO_WriteEnabled(void) {
#if FATFS_USE_WRITEPROTECT_PIN > 0
	return 0;
#else
	return 1;
#endif
}
