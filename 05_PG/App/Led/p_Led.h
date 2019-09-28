/*
 * p_Led.h
 *
 *  Created on: Sep 28, 2019
 *      Author: Akimoto Masane
 */

#ifndef LED_P_LED_H_
#define LED_P_LED_H_


#define LD1_PIN		(GPIO_PIN_5)
#define LD2_PIN		(GPIO_PIN_4)

#define LED_ON		(GPIO_PIN_RESET)
#define LED_OFF		(GPIO_PIN_SET)


typedef struct {

	uint32_t tick;

} st;


static void initLedTask(void);


#endif /* LED_P_LED_H_ */
