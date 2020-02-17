################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../App/LSM6DSL/Lsm6dsl.c 

OBJS += \
./App/LSM6DSL/Lsm6dsl.o 

C_DEPS += \
./App/LSM6DSL/Lsm6dsl.d 


# Each subdirectory must supply rules for building sources it contributes
App/LSM6DSL/Lsm6dsl.o: ../App/LSM6DSL/Lsm6dsl.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F401xC -DDEBUG -c -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Inc -I../Drivers/CMSIS/Include -I../Drivers/STM32F4xx_HAL_Driver/Inc -I"C:/Users/tomone/Documents/Work/Project/STM32CubeIDE/Drone/05_PG/App/Inc" -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"App/LSM6DSL/Lsm6dsl.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

