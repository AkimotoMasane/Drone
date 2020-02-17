/*
 * ErrorCode.h
 *
 *  Created on: 2020/01/26
 *      Author: Akimoto Masane
 */

#ifndef INC_ERRORCODE_H_
#define INC_ERRORCODE_H_


typedef enum {

	eErrorCodeOK = 0,
	eErrorCodeNG,
	eErrorCodeTimeOut,
	eErrorCodeCommErr,
	eErrorCodeParam

} eErrorCode;


#endif /* INC_ERRORCODE_H_ */
