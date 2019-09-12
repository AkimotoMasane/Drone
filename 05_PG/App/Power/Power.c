/*
 * Power.c
 *
 *  Created on: Sep 4, 2019
 *      Author: tomone
 */


/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
#include "cmsis_os.h"
#include "Power.h"
#include "p_Power.h"


/* Private variables ---------------------------------------------------------*/
static stPowerBuffer g_Power;

extern ADC_HandleTypeDef hadc1;


/**
 * @brief power task entry
 */
void PowerTask(void)
{
	uint32_t in  = 0u;
	uint32_t out = 0u;
	HAL_StatusTypeDef status;

	// initialize
	initPowerTask();

	// task
	for (;;) {

		// start ad converter
		status = HAL_ADC_Start(&hadc1);

		if (HAL_OK == status) {

			status = HAL_ADC_PollForConversion(&hadc1, POWER_AD_CONVERSION_TIMEOUT);
		}

		if (HAL_OK == status) {

			in = HAL_ADC_GetValue(&hadc1);

			out = (uint32_t)(((float)in * (1.0f - POWER_FILTER_COEFFICIENT)) + ((float)g_Power.power * POWER_FILTER_COEFFICIENT));
//			out = ((in * 90u) / 100u) + ((g_Power.power * 10u) / 100u);

			g_Power.power = out;

			if (g_Power.index < POWER_MOVING_AVERAGE_COUNT) {

				g_Power.buffer[g_Power.index] = out;

				g_Power.index++;

			} else {

				g_Power.index = 0u;

				g_Power.buffer[g_Power.index] = out;
			}
		}

		osDelay(POWER_AD_CONVERSION_INTERVAL);
	}
}


/**
 * @brief get power
 * @return power
 */
uint32_t GetPower(void)
{
	uint32_t power = 0u;

	for (uint32_t i = 0u; i < POWER_MOVING_AVERAGE_COUNT; i++) {

		power += g_Power.buffer[i];
	}

	power /= POWER_MOVING_AVERAGE_COUNT;

	return power;
}


/**
 *@brief initialize power task
 */
static void initPowerTask(void)
{

	g_Power.power = 0u;
	g_Power.index = 0u;

	for (uint32_t i = 0u; i < POWER_MOVING_AVERAGE_COUNT; i++) {

		g_Power.buffer[i] = 0u;
	}
}
