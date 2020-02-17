/*
 * Spi.h
 *
 *  Created on: Sep 28, 2019
 *      Author: Akimoto Masane
 */

#ifndef INC_SPI_H_
#define INC_SPI_H_


// device id
typedef enum {

	eSPBTLE = 0,	// bluetooth
	eLIS2MDL,		// magnetometer
	eLPS22HB,		// pressure sensor
	eLSM6DSL		// accelerometer and gyroscope

} eDeviceID;


typedef struct {

	eDeviceID	id;				// device id
	uint8_t		addr;			// register address
	uint16_t	slength;		// send data length
	uint16_t	rlength;		// receive data length
	void		*pTxBuffer;		// send buffer
	void		*pRxBuffer;		// receive buffer
	void (*pCallback)(HAL_StatusTypeDef status);	// callback function

} stSpiTransmit;


void SpiTask(void);


#endif /* INC_SPI_H_ */
