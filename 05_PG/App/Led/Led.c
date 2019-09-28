/*
 * Led.c
 *
 *  Created on: Sep 28, 2019
 *      Author: Akimoto Masane
 */


/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
#include "cmsis_os.h"
#include "Led.h"
#include "p_Led.h"


/* Private variables --------------------------------------------------------- */
static eLedOperating g_Led1;
static eLedOperating g_Led2;


/**
 * @brief led task
 */
void LedTask(void)
{
	// initialize task
	initLedTask();

	// task
	for (;;) {

		HAL_GPIO_TogglePin(GPIOB, LD1_PIN);
		HAL_GPIO_TogglePin(GPIOB, LD2_PIN);

		osDelay(1000u);
	}
}


/**
 * @brief initialize led task
 */
static void initLedTask(void)
{
	g_Led1 = eLedOff;

	g_Led2 = eLedOff;
}
