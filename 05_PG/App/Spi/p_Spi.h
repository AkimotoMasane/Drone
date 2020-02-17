/*
 * p_Spi.h
 *
 *  Created on: Sep 28, 2019
 *      Author: Akimoto Masane
 */

#ifndef SPI_P_SPI_H_
#define SPI_P_SPI_H_


extern osMessageQId spiQueueHandle;
extern SPI_HandleTypeDef hspi2;


#define SPI_MESSAGE_TIMEOUT		(100u)
#define SPI_TRANSMIT_TIMEOUT	(100u)

// chip select port
#define SPBTLE_CHIP_SELECT_GPIO		(GPIOB)		// bluetooth
#define LIS2MDL_CHIP_SELECT_GPIO	(GPIOB)		// magnetometer
#define LPS22HB_CHIP_SELECT_GPIO	(GPIOC)		// pressure sensor
#define LSM6DSL_CHIP_SELECT_GPIO	(GPIOA)		// accelerometer and gyroscope

// chip select pin
#define SPBTLE_CHIP_SELECT_PIN	(GPIO_PIN_0)	// bluetooth
#define LIS2MDL_CHIP_SELECT_PIN	(GPIO_PIN_12)	// magnetometer
#define LPS22HB_CHIP_SELECT_PIN	(GPIO_PIN_13)	// pressure sensor
#define LSM6DSL_CHIP_SELECT_PIN	(GPIO_PIN_8)	// accelerometer and gyroscope

// chip select
#define CHIP_SELECT_NON_ACTIVE	(GPIO_PIN_SET)
#define CHIP_SELECT_ACTIVE		(GPIO_PIN_RESET)


static void initSpiTask(void);
static void onSpbtle(const stSpiTransmit *pMessage);
static void onLis2mdl(const stSpiTransmit *pMessage);
static void onLps22hb(const stSpiTransmit *pMessage);
static void onLsm6dsl(const stSpiTransmit *pMessage);
static void WriteSPI(const uint8_t data);
static void ReadSPI(uint8_t *pData);
static void ReadMultipleSPI(const uint8_t length, uint8_t *pData);


#endif /* SPI_P_SPI_H_ */
