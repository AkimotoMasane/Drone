/*
 * p_Battery.h
 *
 *  Created on: Sep 22, 2019
 *      Author: Akimoto Masane
 */

#ifndef BATTERY_P_BATTERY_H_
#define BATTERY_P_BATTERY_H_


extern ADC_HandleTypeDef hadc1;


/* Exported types ------------------------------------------------------------*/
#define BATTERY_MOVING_AVERAGE_COUNT	(4u)
#define BATTERY_RC_FILTER				(100u)
#define BATTERY_FILTER_COEFFICIENT		(10u)

#define BATTERY_AD_CONVERSION_TIMEOUT	(10u)
#define BATTERY_AD_CONVERSION_INTERVAL	(1000u)

#define AD_REFERENCE_VOLTAGE	(33u)		// reference voltage 3.3V
#define BATTERY_AD_MAX_VALUE	(0x0FFFu)	// 12bits
#define BAT_RUP					(10u)		// Pull-up resistor value [Kohm]
#define BAT_RDW					(20u)		// Pull-Down resistor value [Kohm]


typedef struct {

	uint32_t battery;
	uint32_t output;
	uint32_t index;
	uint32_t buffer[BATTERY_MOVING_AVERAGE_COUNT];

} stBatteryBuffer;


/* Exported functions --------------------------------------------------------*/
static void initBatteryTask(void);
static uint32_t exeRcFilter(const uint32_t preValue, const uint32_t value);
static uint32_t exeMovingAverage(const uint32_t size, const uint32_t * const pBuffer);


#endif /* BATTERY_P_BATTERY_H_ */
