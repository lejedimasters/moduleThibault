
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

// LSM9DS1
#define GPIO_PIN_SPI1_MOSI			GPIO_PIN_7	// verifie
#define GPIO_BLOCK_SPI1_MOSI		GPIOA		// verifie
#define GPIO_PIN_SPI1_MISO			GPIO_PIN_6	// verifie
#define GPIO_BLOCK_SPI1_MISO		GPIOA		// verifie
#define GPIO_PIN_SPI1_CLK			GPIO_PIN_3	// verifie
#define GPIO_BLOCK_SPI1_CLK			GPIOB		// verifie

// Chip Select
#define GPIO_PIN_CS_SDCARD			GPIO_PIN_2	// verifie
#define GPIO_BLOCK_CS_SDCARD		GPIOD		// verifie
#define GPIO_PIN_CS_LSM_M			GPIO_PIN_9	// verifie
#define GPIO_BLOCK_CS_LSM_M			GPIOB		// verifie
#define GPIO_PIN_CS_LSM_AG			GPIO_PIN_0	// verifie
#define GPIO_BLOCK_CS_LSM_AG		GPIOC		// verifie
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
