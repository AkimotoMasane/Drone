/*
 * Battery.c
 *
 *  Created on: Sep 22, 2019
 *      Author: Akimoto Masane
 */


/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
#include "cmsis_os.h"
#include "Battery.h"
#include "p_Battery.h"


/* Private variables --------------------------------------------------------- */
static stBatteryBuffer g_Battery;


/**
 * @brief battery task
 */
void BatteryTask(void)
{
	uint32_t input;
	HAL_StatusTypeDef status;

	// task
	for (;;) {

		// initialize
		initBatteryTask();

		// task
		for (;;) {

			// start ad converter
			status = HAL_ADC_Start(&hadc1);

			if (HAL_OK == status) {

				status = HAL_ADC_PollForConversion(&hadc1, BATTERY_AD_CONVERSION_TIMEOUT);
			}

			if (HAL_OK == status) {

				input = HAL_ADC_GetValue(&hadc1);

				// RC filter
				g_Battery.output = exeRcFilter(g_Battery.output, input);

				if (g_Battery.index < BATTERY_MOVING_AVERAGE_COUNT) {

					g_Battery.buffer[g_Battery.index] = g_Battery.output;

					g_Battery.index++;

				} else {

					g_Battery.index = 0u;

					g_Battery.buffer[g_Battery.index] = g_Battery.output;

					g_Battery.index++;
				}

				// moving average filter
				g_Battery.battery = exeMovingAverage(BATTERY_MOVING_AVERAGE_COUNT, g_Battery.buffer);
			}

			osDelay(BATTERY_AD_CONVERSION_INTERVAL);
		}
	}
}


/**
 * @brief get the remaining battery capacity
 * @return the remaining battery capacity
 */
uint32_t GetBattery(void)
{
	uint32_t value;
	uint32_t voltage;

	value = g_Battery.battery;

	// 12bits
	voltage = ((value * AD_REFERENCE_VOLTAGE) * (BAT_RUP + BAT_RDW)) / (BATTERY_AD_MAX_VALUE * BAT_RDW);

	return voltage;
}


/**
 * @brief initialize battery task
 */
static void initBatteryTask(void)
{
	g_Battery.battery = 0u;
	g_Battery.output  = 0u;
	g_Battery.index   = 0u;

	for (uint32_t i = 0u; i < BATTERY_MOVING_AVERAGE_COUNT; i++) {

		g_Battery.buffer[i] = 0u;
	}
}


/**
 * @brief rc digital filter
 * @param preValue pre value
 * @param current value
 * @return rc digital filter value
 */
static uint32_t exeRcFilter(const uint32_t preValue, const uint32_t value)
{
	uint32_t digital;

	// rc filter
	digital = ((value * (BATTERY_RC_FILTER - BATTERY_FILTER_COEFFICIENT)) / BATTERY_RC_FILTER) + ((preValue * BATTERY_FILTER_COEFFICIENT) / BATTERY_RC_FILTER);
//	output = (uint32_t)(((float)input * (1.0f - 0.1f)) + ((float)g_Battery.battery * 0.1f));

	return digital;
}


/**
 * @brief moving average
 * @param size buffer size
 * @param pBuffer buffer pointer
 * @retrun moving average values
 */
static uint32_t exeMovingAverage(const uint32_t size, const uint32_t * const pBuffer)
{
	uint32_t average;

	average = 0u;

	for (uint32_t i = 0u; i < size; i++) {

		average += pBuffer[i];
	}

	average /= size;

	return average;
}
