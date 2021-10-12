################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/main.c \
../source/mtb.c \
../source/pwm.c \
../source/semihost_hardfault.c \
../source/statemachine.c \
../source/switch.c \
../source/timer.c \
../source/touchslider.c 

OBJS += \
./source/main.o \
./source/mtb.o \
./source/pwm.o \
./source/semihost_hardfault.o \
./source/statemachine.o \
./source/switch.o \
./source/timer.o \
./source/touchslider.o 

C_DEPS += \
./source/main.d \
./source/mtb.d \
./source/pwm.d \
./source/semihost_hardfault.d \
./source/statemachine.d \
./source/switch.d \
./source/timer.d \
./source/touchslider.d 


# Each subdirectory must supply rules for building sources it contributes
source/%.o: ../source/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DCPU_MKL25Z128VLK4 -DCPU_MKL25Z128VLK4_cm0plus -DFSL_RTOS_BM -DSDK_OS_BAREMETAL -DSDK_DEBUGCONSOLE=0 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -DSDK_DEBUGCONSOLE_UART -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"C:\Users\prabh\Documents\MCUXpressoIDE_11.2.0_4120\workspace\Buffhati_PES_Assignment_4\board" -I"C:\Users\prabh\Documents\MCUXpressoIDE_11.2.0_4120\workspace\Buffhati_PES_Assignment_4\source" -I"C:\Users\prabh\Documents\MCUXpressoIDE_11.2.0_4120\workspace\Buffhati_PES_Assignment_4" -I"C:\Users\prabh\Documents\MCUXpressoIDE_11.2.0_4120\workspace\Buffhati_PES_Assignment_4\drivers" -I"C:\Users\prabh\Documents\MCUXpressoIDE_11.2.0_4120\workspace\Buffhati_PES_Assignment_4\CMSIS" -I"C:\Users\prabh\Documents\MCUXpressoIDE_11.2.0_4120\workspace\Buffhati_PES_Assignment_4\utilities" -I"C:\Users\prabh\Documents\MCUXpressoIDE_11.2.0_4120\workspace\Buffhati_PES_Assignment_4\startup" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fmerge-constants -fmacro-prefix-map="../$(@D)/"=. -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


