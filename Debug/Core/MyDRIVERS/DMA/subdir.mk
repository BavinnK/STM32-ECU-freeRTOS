################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/MyDRIVERS/DMA/MyDMA.c 

OBJS += \
./Core/MyDRIVERS/DMA/MyDMA.o 

C_DEPS += \
./Core/MyDRIVERS/DMA/MyDMA.d 


# Each subdirectory must supply rules for building sources it contributes
Core/MyDRIVERS/DMA/%.o Core/MyDRIVERS/DMA/%.su Core/MyDRIVERS/DMA/%.cyclo: ../Core/MyDRIVERS/DMA/%.c Core/MyDRIVERS/DMA/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F446xx -c -I"../Core/MyDRIVERS/SPI" -I"../Core/Inc/ILI9341" -I"../Core/MyDRIVERS/CLOCK" -I"../Core/Inc/LEGACY_inc_drivers" -I"../Core/MyDRIVERS/USART" -I"../Core/MyDRIVERS/GPIO" -I"../Core/MyDRIVERS/DMA" -I"../Core/MyDRIVERS/ADC" -I"../Core/Inc" -I"../Core/ThirdParty/FreeRTOS/include" -I"../Core/ThirdParty/FreeRTOS/portable" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Core/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-MyDRIVERS-2f-DMA

clean-Core-2f-MyDRIVERS-2f-DMA:
	-$(RM) ./Core/MyDRIVERS/DMA/MyDMA.cyclo ./Core/MyDRIVERS/DMA/MyDMA.d ./Core/MyDRIVERS/DMA/MyDMA.o ./Core/MyDRIVERS/DMA/MyDMA.su

.PHONY: clean-Core-2f-MyDRIVERS-2f-DMA

