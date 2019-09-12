/*
 * p_Power.h
 *
 *  Created on: Sep 4, 2019
 *      Author: tomone
 */

#ifndef POWER_P_POWER_H_
#define POWER_P_POWER_H_


/* Exported types ------------------------------------------------------------*/
#define POWER_MOVING_AVERAGE_COUNT	(4u)
#define POWER_FILTER_COEFFICIENT	(0.1f)

#define POWER_AD_CONVERSION_TIMEOUT		(10u)
#define POWER_AD_CONVERSION_INTERVAL	(1000u)


typedef struct {

	uint32_t power;
	uint32_t index;
	uint32_t buffer[POWER_MOVING_AVERAGE_COUNT];

} stPowerBuffer;


/* Exported functions --------------------------------------------------------*/
static void initPowerTask(void);


#endif /* POWER_P_POWER_H_ */
