
#ifndef BOARD_H
#define BOARD_H



#define		NUCLEO_BOARD	1
#define		THsBOARD		0



//GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7

// Carte SD
#define GPIO_PIN_SPI3_MOSI			GPIO_PIN_12	// verifie
#define GPIO_BLOCK_SPI3_MOSI		GPIOC		// verifie
#define GPIO_PIN_SPI3_MISO			GPIO_PIN_11	// verifie
#define GPIO_BLOCK_SPI3_MISO		GPIOC		// verifie
#define GPIO_PIN_SPI3_CLK			GPIO_PIN_10	// verifie
#define GPIO_BLOCK_SPI3_CLK			GPIOC		// verifie

#if THsBOARD
	// LSM9DS1 SPI
	#define GPIO_PIN_SPI1_MOSI			GPIO_PIN_7	// verifie
	#define GPIO_BLOCK_SPI1_MOSI		GPIOA		// verifie
	#define GPIO_PIN_SPI1_MISO			GPIO_PIN_6	// verifie
	#define GPIO_BLOCK_SPI1_MISO		GPIOA		// verifie
	#define GPIO_PIN_SPI1_CLK			GPIO_PIN_3	// verifie
	#define GPIO_BLOCK_SPI1_CLK			GPIOB		// verifie
#elif NUCLEO_BOARD
	// LSM9DS1 SPI
	#define GPIO_PIN_SPI1_MOSI			GPIO_PIN_7	// verifie
	#define GPIO_BLOCK_SPI1_MOSI		GPIOA		// verifie
	#define GPIO_PIN_SPI1_MISO			GPIO_PIN_6	// verifie
	#define GPIO_BLOCK_SPI1_MISO		GPIOA		// verifie
	#define GPIO_PIN_SPI1_CLK			GPIO_PIN_5	// verifie
	#define GPIO_BLOCK_SPI1_CLK			GPIOA		// verifie
#endif
// LSM9DS1 OTHER
#define GPIO_PIN_DRDY_M		GPIO_PIN_8
#define GPIO_BLOCK_DRDY_M	GPIOB
#define GPIO_PIN_INT_M		GPIO_PIN_7
#define GPIO_BLOCK_INT_M	GPIOB
#define GPIO_PIN_INT1_AG	GPIO_PIN_6
#define GPIO_BLOCK_INT1_AG	GPIOB
#define GPIO_PIN_INT2_AG	GPIO_PIN_5
#define GPIO_BLOCK_INT2_AG	GPIOB
#define GPIO_PIN_DEN_AG		GPIO_PIN_4
#define GPIO_BLOCK_DEN_AG	GPIOB





// Chip Select
#define GPIO_PIN_CS_SDCARD			GPIO_PIN_2	// verifie
#define GPIO_BLOCK_CS_SDCARD		GPIOD		// verifie

#if THsBOARD
	#define GPIO_PIN_CS_LSM_M			GPIO_PIN_9	// verifie
	#define GPIO_BLOCK_CS_LSM_M			GPIOB		// verifie
	#define GPIO_PIN_CS_LSM_AG			GPIO_PIN_0	// verifie
	#define GPIO_BLOCK_CS_LSM_AG		GPIOC		// verifie
#elif NUCLEO_BOARD
	#define GPIO_PIN_CS_LSM_M			GPIO_PIN_2	// verifie
	#define GPIO_BLOCK_CS_LSM_M			GPIOB		// verifie
	#define GPIO_PIN_CS_LSM_AG			GPIO_PIN_6	// verifie
	#define GPIO_BLOCK_CS_LSM_AG		GPIOB		// verifie
#endif

/*
#define GPIO_PIN_CS_LSM_M			GPIO_PIN
#define GPIO_BLOCK_CS_LSM_M			GPIO
#define GPIO_PIN_CS_LSM_AG			GPIO_PIN
#define GPIO_BLOCK_CS_LSM_AG		GPIO
*/
// UART
#define GPIO_PIN_UART2_TX			GPIO_PIN_2	// verifie
#define GPIO_BLOCK_UART2_TX			GPIOA		// verifie
#define GPIO_PIN_UART2_RX			GPIO_PIN_3	// verifie
#define GPIO_BLOCK_UART2_RX			GPIOA		// verifie

// I/O
#define GPIO_PIN_LED				GPIO_PIN_13	// verifie
#define GPIO_BLOCK_LED				GPIOC		// verifie
#define GPIO_PIN_BUTTON				GPIO_PIN_15	// verifie
#define GPIO_BLOCK_BUTTON			GPIOA		// verifie


#endif
