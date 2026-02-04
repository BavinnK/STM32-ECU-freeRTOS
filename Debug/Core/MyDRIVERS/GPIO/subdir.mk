################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/MyDRIVERS/GPIO/gpiox.c 

OBJS += \
./Core/MyDRIVERS/GPIO/gpiox.o 

C_DEPS += \
./Core/MyDRIVERS/GPIO/gpiox.d 


# Each subdirectory must supply rules for building sources it contributes
Core/MyDRIVERS/GPIO/%.o Core/MyDRIVERS/GPIO/%.su Core/MyDRIVERS/GPIO/%.cyclo: ../Core/MyDRIVERS/GPIO/%.c Core/MyDRIVERS/GPIO/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F446xx -c -I"C:/Users/pc/Desktop/STM_PROJECTS/V2.4_ECU_STM32_PROJECT/Core/Inc/ILI9341" -I"C:/Users/pc/Desktop/STM_PROJECTS/V2.4_ECU_STM32_PROJECT/Core/Inc/LEGACY_inc_drivers" -I"C:/Users/pc/Desktop/STM_PROJECTS/V2.4_ECU_STM32_PROJECT/Core/MyDRIVERS/SPI" -I"C:/Users/pc/Desktop/STM_PROJECTS/V2.4_ECU_STM32_PROJECT/Core/MyDRIVERS/CLOCK" -I"C:/Users/pc/Desktop/STM_PROJECTS/V2.4_ECU_STM32_PROJECT/Core/MyDRIVERS/USART" -I"C:/Users/pc/Desktop/STM_PROJECTS/V2.4_ECU_STM32_PROJECT/Core/MyDRIVERS/GPIO" -I"C:/Users/pc/Desktop/STM_PROJECTS/V2.4_ECU_STM32_PROJECT/Core/MyDRIVERS/DMA" -I"C:/Users/pc/Desktop/STM_PROJECTS/V2.4_ECU_STM32_PROJECT/Core/MyDRIVERS/ADC" -I"C:/Users/pc/Desktop/STM_PROJECTS/V2.4_ECU_STM32_PROJECT/Core/Inc" -I"C:/Users/pc/Desktop/STM_PROJECTS/V2.4_ECU_STM32_PROJECT/Core/ThirdParty/FreeRTOS/include" -I"C:/Users/pc/Desktop/STM_PROJECTS/V2.4_ECU_STM32_PROJECT/Core/ThirdParty/FreeRTOS/portable" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Core/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-MyDRIVERS-2f-GPIO

clean-Core-2f-MyDRIVERS-2f-GPIO:
	-$(RM) ./Core/MyDRIVERS/GPIO/gpiox.cyclo ./Core/MyDRIVERS/GPIO/gpiox.d ./Core/MyDRIVERS/GPIO/gpiox.o ./Core/MyDRIVERS/GPIO/gpiox.su

.PHONY: clean-Core-2f-MyDRIVERS-2f-GPIO

