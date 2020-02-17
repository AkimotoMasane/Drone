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
static LinearAcceleration g_LinearAcceleration;


/**
 * @brief LSM6DSL task
 */
void Lsm6dslTask(void)
{
	static uint8_t addr;
	static uint8_t sendData[16u];
	static uint8_t receiveData[16u];

	// initialize task
	initLsm6dslTask();

	eErrorCode result;

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

		// task
		for (;;) {

			result = exeLsm6dslInterface(addr, 0u, 12u, sendData, receiveData);

			if (eErrorCodeOK == result) {

				g_AngularRate.pitch = (uint16_t)receiveData[0];
				g_AngularRate.pitch |= (((uint16_t)receiveData[1]) << 8u);

				g_AngularRate.roll = (uint16_t)receiveData[2];
				g_AngularRate.roll |= (((uint16_t)receiveData[3]) << 8u);

				g_AngularRate.yaw = (uint16_t)receiveData[4];
				g_AngularRate.yaw |= (((uint16_t)receiveData[5]) << 8u);

				g_LinearAcceleration.xaxis = (uint16_t)receiveData[6];
				g_LinearAcceleration.xaxis |= (((uint16_t)receiveData[7]) << 8u);

				g_LinearAcceleration.yaxis = (uint16_t)receiveData[8];
				g_LinearAcceleration.yaxis |= (((uint16_t)receiveData[9]) << 8u);

				g_LinearAcceleration.zaxis = (uint16_t)receiveData[10];
				g_LinearAcceleration.zaxis |= (((uint16_t)receiveData[11]) << 8u);

				osDelay(100u);

			} else {

				osDelay(100u);
			}
		}

	} else {

		for (;;) {

			osDelay(100);
		}
	}
}


/**
 * @brief initialize task
 */
static void initLsm6dslTask(void)
{
	g_AngularRate.pitch = 0u;
	g_AngularRate.roll = 0u;
	g_AngularRate.yaw = 0u;

	g_LinearAcceleration.xaxis = 0u;
	g_LinearAcceleration.yaxis = 0u;
	g_LinearAcceleration.zaxis = 0u;
}


/**
 * @brief call back
 */
static void Lsd6dslCallback(const HAL_StatusTypeDef status)
{
	int32_t preSignal;

	// set signal
	preSignal = osSignalSet(lsm6dslTaskHandle, 0x00000001);
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

	status = osMessagePut(spiQueueHandle, (uint32_t)&transmit, 100u);

	if (osOK == status) {

		event = osSignalWait(0x00000001, 100u);

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
