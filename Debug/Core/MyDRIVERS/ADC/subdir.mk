################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/MyDRIVERS/ADC/MyAdcDMA.c 

OBJS += \
./Core/MyDRIVERS/ADC/MyAdcDMA.o 

C_DEPS += \
./Core/MyDRIVERS/ADC/MyAdcDMA.d 


# Each subdirectory must supply rules for building sources it contributes
Core/MyDRIVERS/ADC/%.o Core/MyDRIVERS/ADC/%.su Core/MyDRIVERS/ADC/%.cyclo: ../Core/MyDRIVERS/ADC/%.c Core/MyDRIVERS/ADC/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F446xx -c -I"../Core/MyDRIVERS/SPI" -I"../Core/Inc/ILI9341" -I"../Core/MyDRIVERS/CLOCK" -I"../Core/Inc/LEGACY_inc_drivers" -I"../Core/MyDRIVERS/USART" -I"../Core/MyDRIVERS/GPIO" -I"../Core/MyDRIVERS/DMA" -I"../Core/MyDRIVERS/ADC" -I"../Core/Inc" -I"../Core/ThirdParty/FreeRTOS/include" -I"../Core/ThirdParty/FreeRTOS/portable" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Core/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-MyDRIVERS-2f-ADC

clean-Core-2f-MyDRIVERS-2f-ADC:
	-$(RM) ./Core/MyDRIVERS/ADC/MyAdcDMA.cyclo ./Core/MyDRIVERS/ADC/MyAdcDMA.d ./Core/MyDRIVERS/ADC/MyAdcDMA.o ./Core/MyDRIVERS/ADC/MyAdcDMA.su

.PHONY: clean-Core-2f-MyDRIVERS-2f-ADC

