################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/MyDRIVERS/SPI/MySPI.c 

OBJS += \
./Core/MyDRIVERS/SPI/MySPI.o 

C_DEPS += \
./Core/MyDRIVERS/SPI/MySPI.d 


# Each subdirectory must supply rules for building sources it contributes
Core/MyDRIVERS/SPI/%.o Core/MyDRIVERS/SPI/%.su Core/MyDRIVERS/SPI/%.cyclo: ../Core/MyDRIVERS/SPI/%.c Core/MyDRIVERS/SPI/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F446xx -c -I"../Core/MyDRIVERS/SPI" -I"../Core/Inc/ILI9341" -I"../Core/MyDRIVERS/CLOCK" -I"../Core/Inc/LEGACY_inc_drivers" -I"../Core/MyDRIVERS/USART" -I"../Core/MyDRIVERS/GPIO" -I"../Core/MyDRIVERS/DMA" -I"../Core/MyDRIVERS/ADC" -I"../Core/Inc" -I"../Core/ThirdParty/FreeRTOS/include" -I"../Core/ThirdParty/FreeRTOS/portable" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Core/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-MyDRIVERS-2f-SPI

clean-Core-2f-MyDRIVERS-2f-SPI:
	-$(RM) ./Core/MyDRIVERS/SPI/MySPI.cyclo ./Core/MyDRIVERS/SPI/MySPI.d ./Core/MyDRIVERS/SPI/MySPI.o ./Core/MyDRIVERS/SPI/MySPI.su

.PHONY: clean-Core-2f-MyDRIVERS-2f-SPI

