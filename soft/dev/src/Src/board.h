
#ifndef BOARD_H
#define BOARD_H



#define		NUCLEO_BOARD	0
#define		THsBOARD		1



//GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7

// Carte SD
#define GPIO_PIN_SPI3_MOSI			GPIO_PIN_12	// verifie
#define GPIO_BLOCK_SPI3_MOSI		GPIOC		// verifie
#define GPIO_PIN_SPI3_MISO			GPIO_PIN_11	// verifie
#define GPIO_BLOCK_SPI3_MISO		GPIOC		// verifie
#define GPIO_PIN_SPI3_CLK			GPIO_PIN_10	// verifie
#define GPIO_BLOCK_SPI3_CLK			GPIOC		// verifie

// LSM9DS1
/*
 *
 *  n'est plus utilisé !!!!!!!!!!!!!!
#define GPIO_PIN_SPI1_MOSI			GPIO_PIN_7	// verifie
#define GPIO_BLOCK_SPI1_MOSI		GPIOA		// verifie
#define GPIO_PIN_SPI1_MISO			GPIO_PIN_6	// verifie
#define GPIO_BLOCK_SPI1_MISO		GPIOA		// verifie
#define GPIO_PIN_SPI1_CLK			GPIO_PIN_3	// verifie
#define GPIO_BLOCK_SPI1_CLK			GPIOB		// verifie
*/

// LSM9DS0
#define GPIO_PIN_SPI2_MOSI			GPIO_PIN_3	// verifie
#define GPIO_BLOCK_SPI2_MOSI		GPIOC		// verifie
#define GPIO_PIN_SPI2_MISO			GPIO_PIN_2	// verifie
#define GPIO_BLOCK_SPI2_MISO		GPIOC		// verifie
#define GPIO_PIN_SPI2_CLK			GPIO_PIN_10	// verifie
#define GPIO_BLOCK_SPI2_CLK			GPIOB		// verifie

// Chip Select
#define GPIO_PIN_CS_SDCARD			GPIO_PIN_2	// verifie
#define GPIO_BLOCK_CS_SDCARD		GPIOD		// verifie


#warning a reverifier
#define GPIO_PIN_CS_LSM_M			GPIO_PIN_1	// verifie
#define GPIO_BLOCK_CS_LSM_M			GPIOB		// verifie
#define GPIO_PIN_CS_LSM_G			GPIO_PIN_0	// verifie
#define GPIO_BLOCK_CS_LSM_G			GPIOC		// verifie
#define GPIO_PIN_CS_LSM_X			GPIO_PIN_1	// verifie
#define GPIO_BLOCK_CS_LSM_X			GPIOB		// verifie
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
#if	NUCLEO_BOARD

	#define GPIO_PIN_BUTTON 				GPIO_PIN_13	// verifie
	#define GPIO_BLOCK_BUTTON 				GPIOC		// verifie
	#define GPIO_PIN_LED					GPIO_PIN_15	// verifie
	#define GPIO_BLOCK_LED					GPIOA		// verifie
#elif	THsBOARD
	#define GPIO_PIN_LED				GPIO_PIN_13	// verifie
	#define GPIO_BLOCK_LED				GPIOC		// verifie
	#define GPIO_PIN_BUTTON				GPIO_PIN_15	// verifie
	#define GPIO_BLOCK_BUTTON			GPIOA		// verifie
#define

#endif
