/*
 * Lsm6dsl.c
 *
 *  Created on: Oct 14, 2019
 *      Author: Akimoto Masane
 */


/* Includes ------------------------------------------------------------------*/
#include <string.h>
#include "stm32f4xx_hal.h"
#include "cmsis_os.h"
#include "ErrorCode.h"
#include "spi.h"
#include "Lsm6dsl.h"
#include "p_Lsm6dsl.h"


static AngularRate g_AngularRate;
static AngularRate g_PreAngularRate;

static LinearAcceleration g_LinearAcceleration;
static LinearAcceleration g_PreLinearAcceleration;


/**
 * @brief LSM6DSL task
 */
void Lsm6dslTask(void)
{
	static uint8_t addr;
	static uint8_t sendData[16u];
	static uint8_t receiveData[16u];
	eErrorCode result;

	// initialize task
	initLsm6dslTask();

	memset(sendData, 0, 16);
	memset(receiveData, 0, 16);

	addr = LSM6DSL_WRITE | LSM6DSL_CTRL3_C;
	sendData[0] = 0x0Cu;

	result = exeLsm6dslInterface(addr, 1u, 0u, sendData, receiveData);

	if (eErrorCodeOK == result) {

		memset(sendData, 0, 16);
		memset(receiveData, 0, 16);

		addr = LSM6DSL_READ | LSM6DSL_WHO_AM_I;

		result = exeLsm6dslInterface(addr, 0u, 1u, sendData, receiveData);
	}

	if (eErrorCodeOK == result) {

		memset(sendData, 0, 16);
		memset(receiveData, 0, 16);

		addr = LSM6DSL_WRITE | LSM6DSL_CTRL1_XL;
		sendData[0] = 0x50u;
		sendData[1] = 0x50u;

		result = exeLsm6dslInterface(addr, 2u, 0u, sendData, receiveData);
	}

	if (eErrorCodeOK == result) {

		memset(sendData, 0, 16);
		memset(receiveData, 0, 16);

		addr = LSM6DSL_WRITE | LSM6DSL_CTRL5_C;
		sendData[0] = 0x60u;

		result = exeLsm6dslInterface(addr, 1u, 0u, sendData, receiveData);
	}

	if (eErrorCodeOK == result) {

		memset(sendData, 0, 16);
		memset(receiveData, 0, 16);

		addr = LSM6DSL_WRITE | LSM6DSL_FIFO_CTRL5;
		sendData[0] = 0x04u;

		result = exeLsm6dslInterface(addr, 1u, 0u, sendData, receiveData);
	}

	if (eErrorCodeOK == result) {

		memset(sendData, 0, 16);
		memset(receiveData, 0, 16);

		addr = LSM6DSL_READ | LSM6DSL_OUTX_L_G;

		int16_t pitch, roll, yaw;
		int16_t x, y, z;

		// task
		for (;;) {

			result = exeLsm6dslInterface(addr, 0u, 12u, sendData, receiveData);

			if (eErrorCodeOK == result) {

				pitch = (int16_t)(((uint16_t)receiveData[1] << 8u) | (uint16_t)receiveData[0]);
				roll = (int16_t)(((uint16_t)receiveData[3] << 8u) | (uint16_t)receiveData[2]);
				yaw = (int16_t)(((uint16_t)receiveData[5] << 8u) | (uint16_t)receiveData[4]);

				g_AngularRate.pitch = ((int32_t)pitch * 875) / 100;
				g_AngularRate.roll = ((int32_t)roll * 875) / 100;
				g_AngularRate.yaw = ((int32_t)yaw * 875) / 100;

				// rc filter
				g_AngularRate.pitch = ((g_AngularRate.pitch * (ANGULAR_RATE_COFFICIENT_100PER - ANGULAR_RATE_COFFICIENT)) + (g_PreAngularRate.pitch * ANGULAR_RATE_COFFICIENT)) / ANGULAR_RATE_COFFICIENT_100PER;
				g_AngularRate.roll = ((g_AngularRate.roll * (ANGULAR_RATE_COFFICIENT_100PER - ANGULAR_RATE_COFFICIENT)) + (g_PreAngularRate.roll * ANGULAR_RATE_COFFICIENT)) / ANGULAR_RATE_COFFICIENT_100PER;
				g_AngularRate.yaw = ((g_AngularRate.yaw * (ANGULAR_RATE_COFFICIENT_100PER - ANGULAR_RATE_COFFICIENT)) + (g_PreAngularRate.yaw * ANGULAR_RATE_COFFICIENT)) / ANGULAR_RATE_COFFICIENT_100PER;

				// save previous value
				g_PreAngularRate.pitch = g_AngularRate.pitch;
				g_PreAngularRate.roll = g_AngularRate.roll;
				g_PreAngularRate.yaw = g_AngularRate.yaw;

				x = (int16_t)(((uint16_t)receiveData[7] << 8u) | (uint16_t)receiveData[6]);
				y = (int16_t)(((uint16_t)receiveData[9] << 8u) | (uint16_t)receiveData[8]);
				z = (int16_t)(((uint16_t)receiveData[11] << 8u) | (uint16_t)receiveData[10]);

				g_LinearAcceleration.xaxis = ((int32_t)x * 61) / 1000;
				g_LinearAcceleration.yaxis = ((int32_t)y * 61) / 1000;
				g_LinearAcceleration.zaxis = ((int32_t)z * 61) / 1000;

				// rc filter
				g_LinearAcceleration.xaxis = ((g_LinearAcceleration.xaxis * (ANGULAR_RATE_COFFICIENT_100PER - ANGULAR_RATE_COFFICIENT)) + (g_PreLinearAcceleration.xaxis * ANGULAR_RATE_COFFICIENT)) / ANGULAR_RATE_COFFICIENT_100PER;
				g_LinearAcceleration.yaxis = ((g_LinearAcceleration.yaxis * (ANGULAR_RATE_COFFICIENT_100PER - ANGULAR_RATE_COFFICIENT)) + (g_PreLinearAcceleration.yaxis * ANGULAR_RATE_COFFICIENT)) / ANGULAR_RATE_COFFICIENT_100PER;
				g_LinearAcceleration.zaxis = ((g_LinearAcceleration.zaxis * (ANGULAR_RATE_COFFICIENT_100PER - ANGULAR_RATE_COFFICIENT)) + (g_PreLinearAcceleration.zaxis * ANGULAR_RATE_COFFICIENT)) / ANGULAR_RATE_COFFICIENT_100PER;

				// save previous value
				g_PreLinearAcceleration.xaxis = g_LinearAcceleration.xaxis;
				g_PreLinearAcceleration.yaxis = g_LinearAcceleration.yaxis;
				g_PreLinearAcceleration.zaxis = g_LinearAcceleration.zaxis;

				osDelay(LSM6DSL_UPDATE_CYCLE);

			} else {

				osDelay(LSM6DSL_UPDATE_CYCLE);
			}
		}

	} else {

		for (;;) {

			osDelay(LSM6DSL_SYSTEM_ERROR_WAIT);
		}
	}
}


/**
 * @brief initialize task
 */
static void initLsm6dslTask(void)
{
	g_AngularRate.pitch = 0;
	g_AngularRate.roll = 0;
	g_AngularRate.yaw = 0;

	g_PreAngularRate.pitch = 0;
	g_PreAngularRate.roll = 0;
	g_PreAngularRate.yaw = 0;

	g_LinearAcceleration.xaxis = 0;
	g_LinearAcceleration.yaxis = 0;
	g_LinearAcceleration.zaxis = 0;

	g_PreLinearAcceleration.xaxis = 0;
	g_PreLinearAcceleration.yaxis = 0;
	g_PreLinearAcceleration.zaxis = 0;
}


/**
 * @brief call back function
 */
static void Lsd6dslCallback(const HAL_StatusTypeDef status)
{
	int32_t preSignal;

	// set signal
	preSignal = osSignalSet(lsm6dslTaskHandle, LSM6DSL_COMPLETE_SPI);
}


/**
 * @brief LSM6DSLとの通信を行う
 * @param addr レジスタのアドレス
 * @param slen 送信データ数
 * @param rlen 受信データ数
 * @param pSend 送信データバッファへのポインタ
 * @param pReceive 受信データバッファへのポインタ
 */
static eErrorCode exeLsm6dslInterface(const uint8_t addr, const uint16_t slen, const uint16_t rlen, void *pSend, void *pReceive)
{
	eErrorCode    result;
	osEvent       event;
	osStatus      status;
	stSpiTransmit transmit;

	transmit.id			= eLSM6DSL;
	transmit.addr		= addr;
	transmit.slength	= slen;
	transmit.rlength	= rlen;
	transmit.pTxBuffer	= pSend;
	transmit.pRxBuffer	= pReceive;
	transmit.pCallback	= Lsd6dslCallback;

	status = osMessagePut(spiQueueHandle, (uint32_t)&transmit, LSM6DSL_SYSTEM_CALL_WAIT);

	if (osOK == status) {

		event = osSignalWait(LSM6DSL_COMPLETE_SPI, LSM6DSL_SYSTEM_CALL_WAIT);

		if (osEventSignal == event.status) {

			result = eErrorCodeOK;

		} else {

			result = eErrorCodeTimeOut;
		}

	} else {

		result = eErrorCodeCommErr;
	}

	return result;
}
