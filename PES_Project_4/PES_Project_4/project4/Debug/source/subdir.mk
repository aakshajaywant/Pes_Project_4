################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/TMP102.c \
../source/led.c \
../source/logger.c \
../source/mtb.c \
../source/project.c \
../source/retarget_itm.c \
../source/semihost_hardfault.c \
../source/state_driven.c \
../source/system.c \
../source/tabledriven.c \
../source/unittest.c 

OBJS += \
./source/TMP102.o \
./source/led.o \
./source/logger.o \
./source/mtb.o \
./source/project.o \
./source/retarget_itm.o \
./source/semihost_hardfault.o \
./source/state_driven.o \
./source/system.o \
./source/tabledriven.o \
./source/unittest.o 

C_DEPS += \
./source/TMP102.d \
./source/led.d \
./source/logger.d \
./source/mtb.d \
./source/project.d \
./source/retarget_itm.d \
./source/semihost_hardfault.d \
./source/state_driven.d \
./source/system.d \
./source/tabledriven.d \
./source/unittest.d 


# Each subdirectory must supply rules for building sources it contributes
source/%.o: ../source/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DCPU_MKL25Z128VLK4 -DCPU_MKL25Z128VLK4_cm0plus -DFSL_RTOS_BM -DSDK_OS_BAREMETAL -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -DSDK_DEBUGCONSOLE_ITM -DSDK_DEBUGCONSOLE_UART -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -DSDK_DEBUGCONSOLE=1 -I../board -I../source -I../ -I../drivers -I../CMSIS -I../utilities -I../startup -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


