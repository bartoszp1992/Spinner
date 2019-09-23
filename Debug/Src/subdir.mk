################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/main.c \
../Src/matrixDisplay.c \
../Src/rtc.c \
../Src/stm32l0xx_hal_msp.c \
../Src/stm32l0xx_it.c \
../Src/syscalls.c \
../Src/system_stm32l0xx.c 

OBJS += \
./Src/main.o \
./Src/matrixDisplay.o \
./Src/rtc.o \
./Src/stm32l0xx_hal_msp.o \
./Src/stm32l0xx_it.o \
./Src/syscalls.o \
./Src/system_stm32l0xx.o 

C_DEPS += \
./Src/main.d \
./Src/matrixDisplay.d \
./Src/rtc.d \
./Src/stm32l0xx_hal_msp.d \
./Src/stm32l0xx_it.d \
./Src/syscalls.d \
./Src/system_stm32l0xx.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o: ../Src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -mfloat-abi=soft -DUSE_HAL_DRIVER -DSTM32L041xx '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -I"D:/projekty Embedded/Spinner/Inc" -I"D:/projekty Embedded/Spinner/Drivers/STM32L0xx_HAL_Driver/Inc" -I"D:/projekty Embedded/Spinner/Drivers/STM32L0xx_HAL_Driver/Inc/Legacy" -I"D:/projekty Embedded/Spinner/Drivers/CMSIS/Device/ST/STM32L0xx/Include" -I"D:/projekty Embedded/Spinner/Drivers/CMSIS/Include"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


