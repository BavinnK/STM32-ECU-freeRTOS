################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/ThirdParty/FreeRTOS/portable/heap_4.c \
../Core/ThirdParty/FreeRTOS/portable/port.c 

OBJS += \
./Core/ThirdParty/FreeRTOS/portable/heap_4.o \
./Core/ThirdParty/FreeRTOS/portable/port.o 

C_DEPS += \
./Core/ThirdParty/FreeRTOS/portable/heap_4.d \
./Core/ThirdParty/FreeRTOS/portable/port.d 


# Each subdirectory must supply rules for building sources it contributes
Core/ThirdParty/FreeRTOS/portable/%.o Core/ThirdParty/FreeRTOS/portable/%.su Core/ThirdParty/FreeRTOS/portable/%.cyclo: ../Core/ThirdParty/FreeRTOS/portable/%.c Core/ThirdParty/FreeRTOS/portable/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F446xx -c -I"../Core/MyDRIVERS/SPI" -I"../Core/Inc/ILI9341" -I"../Core/MyDRIVERS/CLOCK" -I"../Core/Inc/LEGACY_inc_drivers" -I"../Core/MyDRIVERS/USART" -I"../Core/MyDRIVERS/GPIO" -I"../Core/MyDRIVERS/DMA" -I"../Core/MyDRIVERS/ADC" -I"../Core/Inc" -I"../Core/ThirdParty/FreeRTOS/include" -I"../Core/ThirdParty/FreeRTOS/portable" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Core/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-ThirdParty-2f-FreeRTOS-2f-portable

clean-Core-2f-ThirdParty-2f-FreeRTOS-2f-portable:
	-$(RM) ./Core/ThirdParty/FreeRTOS/portable/heap_4.cyclo ./Core/ThirdParty/FreeRTOS/portable/heap_4.d ./Core/ThirdParty/FreeRTOS/portable/heap_4.o ./Core/ThirdParty/FreeRTOS/portable/heap_4.su ./Core/ThirdParty/FreeRTOS/portable/port.cyclo ./Core/ThirdParty/FreeRTOS/portable/port.d ./Core/ThirdParty/FreeRTOS/portable/port.o ./Core/ThirdParty/FreeRTOS/portable/port.su

.PHONY: clean-Core-2f-ThirdParty-2f-FreeRTOS-2f-portable

