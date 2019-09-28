/*
 * Led.h
 *
 *  Created on: Sep 28, 2019
 *      Author: Akimoto Masane
 */

#ifndef INC_LED_H_
#define INC_LED_H_


/* Exported functions -------------------------------------------------------- */
// led
typedef enum {

	LED1 = 0,
	LED2

} eLed;


// led operating
typedef enum {

	eLedOff = 0,
	eLedOn,
	eLedBlink

} eLedOperating;


//
typedef struct {

	eLed          led;
	eLedOperating operating;

} stLedControl;


/* Exported functions -------------------------------------------------------- */
void LedTask(void);


#endif /* INC_LED_H_ */
