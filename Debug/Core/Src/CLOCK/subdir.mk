################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/CLOCK/clock.c 

OBJS += \
./Core/Src/CLOCK/clock.o 

C_DEPS += \
./Core/Src/CLOCK/clock.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/CLOCK/%.o Core/Src/CLOCK/%.su Core/Src/CLOCK/%.cyclo: ../Core/Src/CLOCK/%.c Core/Src/CLOCK/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F446xx -c -I"../Core/Inc/ILI9341" -I"../Core/Src/CLOCK" -I"../Core/Inc/LEGACY_inc_drivers" -I"../Core/MyDRIVERS/SPI" -I"../Core/MyDRIVERS/USART" -I"../Core/MyDRIVERS/GPIO" -I"../Core/MyDRIVERS/DMA" -I"../Core/MyDRIVERS/ADC" -I"../Core/Inc" -I"../Core/ThirdParty/FreeRTOS/include" -I"../Core/ThirdParty/FreeRTOS/portable" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Core/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-CLOCK

clean-Core-2f-Src-2f-CLOCK:
	-$(RM) ./Core/Src/CLOCK/clock.cyclo ./Core/Src/CLOCK/clock.d ./Core/Src/CLOCK/clock.o ./Core/Src/CLOCK/clock.su

.PHONY: clean-Core-2f-Src-2f-CLOCK

