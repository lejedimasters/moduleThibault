
#ifndef BOARD_H
#define BOARD_H


//GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7

// Carte SD
#define GPIO_PIN_SPI3_MOSI			GPIO_PIN_12
#define GPIO_BLOCK_SPI3_MOSI		GPIOC
#define GPIO_PIN_SPI3_MISO			GPIO_PIN_11
#define GPIO_BLOCK_SPI3_MISO		GPIOC
#define GPIO_PIN_SPI3_CLK			GPIO_PIN_10
#define GPIO_BLOCK_SPI3_CLK			GPIOC

// LSM9DS1
#define GPIO_PIN_SPI1_MOSI			GPIO_PIN_7
#define GPIO_BLOCK_SPI1_MOSI		GPIOA
#define GPIO_PIN_SPI1_MISO			GPIO_PIN_6
#define GPIO_BLOCK_SPI1_MISO		GPIOA
#define GPIO_PIN_SPI1_CLK			GPIO_PIN_3
#define GPIO_BLOCK_SPI1_CLK			GPIOB

// Chip Select
#define GPIO_PIN_CS_SDCARD			GPIO_PIN_2
#define GPIO_BLOCK_CS_SDCARD		GPIOD
#define GPIO_PIN_CS_LSM_M			GPIO_PIN_1
#define GPIO_BLOCK_CS_LSM_M			GPIOA
#define GPIO_PIN_CS_LSM_AG			GPIO_PIN_1
#define GPIO_BLOCK_CS_LSM_AG		GPIOA
/*
#define GPIO_PIN_CS_LSM_M			GPIO_PIN
#define GPIO_BLOCK_CS_LSM_M			GPIO
#define GPIO_PIN_CS_LSM_AG			GPIO_PIN
#define GPIO_BLOCK_CS_LSM_AG		GPIO
*/
// UART
#define GPIO_PIN_UART2_TX			GPIO_PIN_2
#define GPIO_BLOCK_UART2_TX			GPIOA
#define GPIO_PIN_UART2_RX			GPIO_PIN_3
#define GPIO_BLOCK_UART2_RX			GPIOA



#endif
