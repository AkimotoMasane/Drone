/*
 * p_Lsm6dsl.h
 *
 *  Created on: Oct 14, 2019
 *      Author: Akimoto Masane
 */

#ifndef LSM6DSL_P_LSM6DSL_H_
#define LSM6DSL_P_LSM6DSL_H_


extern osThreadId lsm6dslTaskHandle;
extern osMessageQId spiQueueHandle;


// direction
#define LSM6DSL_WRITE	(0x00u)
#define LSM6DSL_READ	(0x80u)

// registers address map
#define LSM6DSL_FUNC_CFG_ACCESS				(0x01u)
#define LSM6DSL_SENSOR_SYNC_TIME_FRAME		(0x04u)
#define LSM6DSL_SENSOR_SYNC_RES_RATIO		(0x05u)
#define LSM6DSL_FIFO_CTRL1					(0x06u)
#define LSM6DSL_FIFO_CTRL2					(0x07u)
#define LSM6DSL_FIFO_CTRL3					(0x08u)
#define LSM6DSL_FIFO_CTRL4					(0x09u)
#define LSM6DSL_FIFO_CTRL5					(0x0Au)
#define LSM6DSL_DRDY_PULSE_CFG_G			(0x0Bu)
#define LSM6DSL_INT1_CTRL					(0x0Du)
#define LSM6DSL_INT2_CTRL					(0x0Eu)
#define LSM6DSL_WHO_AM_I					(0x0Fu)
#define LSM6DSL_CTRL1_XL					(0x10u)
#define LSM6DSL_CTRL2_G						(0x11u)
#define LSM6DSL_CTRL3_C						(0x12u)
#define LSM6DSL_CTRL4_C						(0x13u)
#define LSM6DSL_CTRL5_C						(0x14u)
#define LSM6DSL_CTRL6_C						(0x15u)
#define LSM6DSL_CTRL7_G						(0x16u)
#define LSM6DSL_CTRL8_XL					(0x17u)
#define LSM6DSL_CTRL9_XL					(0x18u)
#define LSM6DSL_CTRL10_C					(0x19u)
#define LSM6DSL_MASTER_CONFIG				(0x1Au)
#define LSM6DSL_WAKE_UP_SRC					(0x1Bu)
#define LSM6DSL_TAP_SRC						(0x1Cu)
#define LSM6DSL_D6D_SRC						(0x1Du)
#define LSM6DSL_STATUS_REG					(0x1Eu)
#define LSM6DSL_OUT_TEMP_L					(0x20u)
#define LSM6DSL_OUT_TEMP_H					(0x21u)
#define LSM6DSL_OUTX_L_G					(0x22u)
#define LSM6DSL_OUTX_H_G					(0x23u)
#define LSM6DSL_OUTY_L_G					(0x24u)
#define LSM6DSL_OUTY_H_G					(0x25u)
#define LSM6DSL_OUTZ_L_G					(0x26u)
#define LSM6DSL_OUTZ_H_G					(0x27u)
#define LSM6DSL_OUTX_L_XL					(0x28u)
#define LSM6DSL_OUTX_H_XL					(0x29u)
#define LSM6DSL_OUTY_L_XL					(0x2Au)
#define LSM6DSL_OUTY_H_XL					(0x2Bu)
#define LSM6DSL_OUTZ_L_XL					(0x2Cu)
#define LSM6DSL_OUTZ_H_XL					(0x2Du)
#define LSM6DSL_SENSORHUB1_REG				(0x2Eu)
#define LSM6DSL_SENSORHUB2_REG				(0x2Fu)
#define LSM6DSL_SENSORHUB3_REG				(0x30u)
#define LSM6DSL_SENSORHUB4_REG				(0x31u)
#define LSM6DSL_SENSORHUB5_REG				(0x32u)
#define LSM6DSL_SENSORHUB6_REG				(0x33u)
#define LSM6DSL_SENSORHUB7_REG				(0x34u)
#define LSM6DSL_SENSORHUB8_REG				(0x35u)
#define LSM6DSL_SENSORHUB9_REG				(0x36u)
#define LSM6DSL_SENSORHUB10_REG				(0x37u)
#define LSM6DSL_SENSORHUB11_REG				(0x38u)
#define LSM6DSL_SENSORHUB12_REG				(0x39u)
#define LSM6DSL_FIFO_STATUS1				(0x3Au)
#define LSM6DSL_FIFO_STATUS2				(0x3Bu)
#define LSM6DSL_FIFO_STATUS3				(0x3Cu)
#define LSM6DSL_FIFO_STATUS4				(0x3Du)
#define LSM6DSL_FIFO_DATA_OUT_L				(0x3Eu)
#define LSM6DSL_FIFO_DATA_OUT_H				(0x3Fu)
#define LSM6DSL_TIMESTAMP0_REG				(0x40u)
#define LSM6DSL_TIMESTAMP1_REG				(0x41u)
#define LSM6DSL_TIMESTAMP2_REG				(0x42u)
#define LSM6DSL_STEP_TIMESTAMP_L			(0x49u)
#define LSM6DSL_STEP_TIMESTAMP_H			(0x4Au)
#define LSM6DSL_STEP_COUNTER_L				(0x4Bu)
#define LSM6DSL_STEP_COUNTER_H				(0x4Cu)
#define LSM6DSL_SENSORHUB13_REG				(0x4Du)
#define LSM6DSL_SENSORHUB14_REG				(0x4Eu)
#define LSM6DSL_SENSORHUB15_REG				(0x4Fu)
#define LSM6DSL_SENSORHUB16_REG				(0x50u)
#define LSM6DSL_SENSORHUB17_REG				(0x51u)
#define LSM6DSL_SENSORHUB18_REG				(0x52u)
#define LSM6DSL_FUNC_SRC1					(0x53u)
#define LSM6DSL_FUNC_SRC2					(0x54u)
#define LSM6DSL_WRIST_TILT_IA				(0x55u)
#define LSM6DSL_TAP_CFG						(0x58u)
#define LSM6DSL_TAP_THS_6D					(0x59u)
#define LSM6DSL_INT_DUR2					(0x5Au)
#define LSM6DSL_WAKE_UP_THS					(0x5Bu)
#define LSM6DSL_WAKE_UP_DUR					(0x5Cu)
#define LSM6DSL_FREE_FALL					(0x5Du)
#define LSM6DSL_MD1_CFG						(0x5Eu)
#define LSM6DSL_MD2_CFG						(0x5Fu)
#define LSM6DSL_MASTER_CMD_CODE				(0x60u)
#define LSM6DSL_SENS_SYNC_SPI_ERROR_CODE	(0x61u)
#define LSM6DSL_OUT_MAG_RAW_X_L				(0x66u)
#define LSM6DSL_OUT_MAG_RAW_X_H				(0x67u)
#define LSM6DSL_OUT_MAG_RAW_Y_L				(0x68u)
#define LSM6DSL_OUT_MAG_RAW_Y_H				(0x69u)
#define LSM6DSL_OUT_MAG_RAW_Z_L				(0x6Au)
#define LSM6DSL_OUT_MAG_RAW_Z_H				(0x6Bu)
#define LSM6DSL_X_OFS_USR					(0x73u)
#define LSM6DSL_Y_OFS_USR					(0x74u)
#define LSM6DSL_Z_OFS_USR					(0x75u)


typedef struct {

	uint16_t pitch;
	uint16_t roll;
	uint16_t yaw;

} AngularRate ;


typedef struct {

	uint16_t xaxis;
	uint16_t yaxis;
	uint16_t zaxis;

} LinearAcceleration;


static void initLsm6dslTask(void);
static void Lsd6dslCallback(const HAL_StatusTypeDef status);
static eErrorCode exeLsm6dslInterface(const uint8_t addr, const uint16_t slen, const uint16_t rlen, void *pSend, void *pReceive);


#endif /* LSM6DSL_P_LSM6DSL_H_ */
