/*
 * Spi.c
 *
 *  Created on: Sep 28, 2019
 *      Author: Akimoto Masane
 */


/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
#include "cmsis_os.h"
#include "Spi.h"
#include "p_Spi.h"


/**
 * @brief spi task
 */
void SpiTask(void)
{
	osEvent       event;
	stSpiTransmit *pMessage;

	// initialize task
	initSpiTask();

	// task
	for (;;) {

		event = osMessageGet(spiQueueHandle, SPI_MESSAGE_TIMEOUT);

		if (osEventMessage == event.status) {

			pMessage = (stSpiTransmit *)event.value.v;

			if (NULL != pMessage) {

				switch (pMessage->id) {

				case eSPBTLE:		// bluetooth
					break;

				case eLIS2MDL:		// magnetometer
					break;

				case eLPS22HB:		// pressure sensor
					break;

				case eLSM6DSL:		// accelerometer and gyroscope

					onLsm6dsl(pMessage);

					break;

				default:
					break;
				}
			}
		}
	}
}


/**
 * @brief initialize spi task
 */
static void initSpiTask(void)
{
	// bluetooth chip select non active
	HAL_GPIO_WritePin(SPBTLE_CHIP_SELECT_GPIO, SPBTLE_CHIP_SELECT_PIN, CHIP_SELECT_NON_ACTIVE);

	// magnetometer chip select non active
	HAL_GPIO_WritePin(LIS2MDL_CHIP_SELECT_GPIO, LIS2MDL_CHIP_SELECT_PIN, CHIP_SELECT_NON_ACTIVE);

	// pressure sensor chip select non active
	HAL_GPIO_WritePin(LPS22HB_CHIP_SELECT_GPIO, LPS22HB_CHIP_SELECT_PIN, CHIP_SELECT_NON_ACTIVE);

	// accelerometer and gyroscope chip select non active
	HAL_GPIO_WritePin(LSM6DSL_CHIP_SELECT_GPIO, LSM6DSL_CHIP_SELECT_PIN, CHIP_SELECT_NON_ACTIVE);
}


/**
 *
 */
static void onSpbtle(const stSpiTransmit *pMessage)
{
}


/**
 *
 */
static void onLis2mdl(const stSpiTransmit *pMessage)
{
}


/**
 *
 */
static void onLps22hb(const stSpiTransmit *pMessage)
{
}


/**
 * @brief transmit LSM6DSL
 * @param pMessage message
 */
static void onLsm6dsl(const stSpiTransmit *pMessage)
{
	HAL_StatusTypeDef status;
	uint8_t           *pBuffer;

	// check parameter
	if (NULL != pMessage) {

		status = HAL_OK;

		// chip select active
		HAL_GPIO_WritePin(LSM6DSL_CHIP_SELECT_GPIO, LSM6DSL_CHIP_SELECT_PIN, CHIP_SELECT_ACTIVE);

		// send register address
		WriteSPI(pMessage->addr);

		if ( (0u < pMessage->slength) && (NULL != pMessage->pTxBuffer) ) {

			pBuffer = (uint8_t *)pMessage->pTxBuffer;

			// transmit
			for (uint32_t i = 0; i < pMessage->slength; i++) {

				WriteSPI(pBuffer[i]);
			}
		}

		// check parameter
		if ( (0U < pMessage->rlength) && (NULL != pMessage->pRxBuffer) ) {

			pBuffer = (uint8_t *)pMessage->pRxBuffer;

			if (1u < pMessage->rlength) {

				ReadMultipleSPI(pMessage->rlength, pBuffer);

			} else {

				ReadSPI(pBuffer);
			}
		}

		// chip select non active
		HAL_GPIO_WritePin(LSM6DSL_CHIP_SELECT_GPIO, LSM6DSL_CHIP_SELECT_PIN, CHIP_SELECT_NON_ACTIVE);

	} else {

		status = HAL_ERROR;
	}

	if (NULL != pMessage->pCallback) {

		// call callback function
		pMessage->pCallback(status);
	}
}


/**
 * @brief データを送信する
 * @param data 送信データ
 */
static void WriteSPI(const uint8_t data)
{
	while (SPI_FLAG_TXE != (hspi2.Instance->SR & SPI_FLAG_TXE)) {

		osDelay(1);
	}

	hspi2.Instance->DR = data;

	while (SPI_SR_TXE != (hspi2.Instance->SR & SPI_SR_TXE)) {

		osDelay(1);
	}

	while (SPI_FLAG_BSY == (hspi2.Instance->SR & SPI_FLAG_BSY)) {

		osDelay(1);
	}
}


/**
 * @brief データを受信する
 * @param pData データを格納するためのバッファへのポインタ
 */
static void ReadSPI(uint8_t *pData)
{
	if (NULL != pData) {

		__HAL_SPI_DISABLE(&hspi2);

		SPI_1LINE_RX(&hspi2);

		__disable_irq();

		__HAL_SPI_ENABLE(&hspi2);

		__asm("dsb\n");
		__asm("dsb\n");
		__asm("dsb\n");
		__asm("dsb\n");
		__asm("dsb\n");
		__asm("dsb\n");
		__asm("dsb\n");
		__asm("dsb\n");
		__asm("dsb\n");
		__asm("dsb\n");
		__asm("dsb\n");
		__asm("dsb\n");
		__asm("dsb\n");
		__asm("dsb\n");
		__asm("dsb\n");
		__asm("dsb\n");
		__asm("dsb\n");
		__asm("dsb\n");
		__asm("dsb\n");
		__asm("dsb\n");
		__asm("dsb\n");
		__asm("dsb\n");
		__asm("dsb\n");
		__asm("dsb\n");
		__asm("dsb\n");
		__asm("dsb\n");
		__asm("dsb\n");
		__asm("dsb\n");
		__asm("dsb\n");
		__asm("dsb\n");
		__asm("dsb\n");
		__asm("dsb\n");
		__asm("dsb\n");
		__asm("dsb\n");
		__asm("dsb\n");
		__asm("dsb\n");
		__asm("dsb\n");
		__asm("dsb\n");
		__asm("dsb\n");
		__asm("dsb\n");
		__asm("dsb\n");
		__asm("dsb\n");
		__asm("dsb\n");
		__asm("dsb\n");
		__asm("dsb\n");
		__asm("dsb\n");
		__asm("dsb\n");
		__asm("dsb\n");
		__asm("dsb\n");
		__asm("dsb\n");
		__asm("dsb\n");
		__asm("dsb\n");
		__asm("dsb\n");
		__asm("dsb\n");
		__asm("dsb\n");
		__asm("dsb\n");
		__asm("dsb\n");
		__asm("dsb\n");
		__asm("dsb\n");
		__asm("dsb\n");
		__asm("dsb\n");
		__asm("dsb\n");
		__asm("dsb\n");
		__asm("dsb\n");
		__asm("dsb\n");
		__asm("dsb\n");
		__asm("dsb\n");

		__HAL_SPI_DISABLE(&hspi2);

		__enable_irq();

		while (SPI_FLAG_RXNE != (hspi2.Instance->SR & SPI_FLAG_RXNE)) {

			osDelay(1);
		}

		*pData = (uint8_t)hspi2.Instance->DR;

		while (SPI_FLAG_BSY == (hspi2.Instance->SR & SPI_FLAG_BSY)) {

			osDelay(1);
		}

		SPI_1LINE_TX(&hspi2);

		__HAL_SPI_ENABLE(&hspi2);
	}
}


/**
 * @brief データを受信する
 * @param length 受信データ数
 * @param pData データを格納するためのバッファへのポインタ
 */
static void ReadMultipleSPI(const uint8_t length, uint8_t *pData)
{
	uint8_t received;

	if ( (0u < length) && (NULL != pData) ) {

		__HAL_SPI_DISABLE(&hspi2);

		SPI_1LINE_RX(&hspi2);

		received = 0u;

		__disable_irq();

		__HAL_SPI_ENABLE(&hspi2);

		while (received < length) {

			if (SPI_FLAG_RXNE == (hspi2.Instance->SR & SPI_FLAG_RXNE)) {

				*pData = (uint8_t)hspi2.Instance->DR;

				pData++;

				received++;

			} else {

				__NOP();
			}
		}

		__DSB();
		__DSB();

		__HAL_SPI_DISABLE(&hspi2);

		__enable_irq();

		while (SPI_FLAG_RXNE != (hspi2.Instance->SR & SPI_FLAG_RXNE)) {

			osDelay(1);
		}

		*pData = (uint8_t)hspi2.Instance->DR;

		while (SPI_FLAG_BSY == (hspi2.Instance->SR & SPI_FLAG_BSY)) {

			osDelay(1);
		}

		SPI_1LINE_TX(&hspi2);

		__HAL_SPI_ENABLE(&hspi2);
	}
}
