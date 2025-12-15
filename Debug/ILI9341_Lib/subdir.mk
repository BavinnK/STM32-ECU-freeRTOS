################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ILI9341_Lib/ILI9341_GFX.c \
../ILI9341_Lib/ILI9341_STM32_Driver.c 

OBJS += \
./ILI9341_Lib/ILI9341_GFX.o \
./ILI9341_Lib/ILI9341_STM32_Driver.o 

C_DEPS += \
./ILI9341_Lib/ILI9341_GFX.d \
./ILI9341_Lib/ILI9341_STM32_Driver.d 


# Each subdirectory must supply rules for building sources it contributes
ILI9341_Lib/%.o ILI9341_Lib/%.su ILI9341_Lib/%.cyclo: ../ILI9341_Lib/%.c ILI9341_Lib/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F446xx -c -I../Core/Inc -I"C:/Users/pc/Desktop/STM_PROJECTS/V2.1_ECU_STM32_PROJECT/ILI9341_Lib" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-ILI9341_Lib

clean-ILI9341_Lib:
	-$(RM) ./ILI9341_Lib/ILI9341_GFX.cyclo ./ILI9341_Lib/ILI9341_GFX.d ./ILI9341_Lib/ILI9341_GFX.o ./ILI9341_Lib/ILI9341_GFX.su ./ILI9341_Lib/ILI9341_STM32_Driver.cyclo ./ILI9341_Lib/ILI9341_STM32_Driver.d ./ILI9341_Lib/ILI9341_STM32_Driver.o ./ILI9341_Lib/ILI9341_STM32_Driver.su

.PHONY: clean-ILI9341_Lib

