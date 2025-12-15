################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ILI9341/fonts.c \
../ILI9341/ili9341.c 

OBJS += \
./ILI9341/fonts.o \
./ILI9341/ili9341.o 

C_DEPS += \
./ILI9341/fonts.d \
./ILI9341/ili9341.d 


# Each subdirectory must supply rules for building sources it contributes
ILI9341/%.o ILI9341/%.su ILI9341/%.cyclo: ../ILI9341/%.c ILI9341/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F446xx -c -I"C:/Users/pc/Desktop/STM_PROJECTS/V2.1_ECU_STM32_PROJECT/ILI9341" -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-ILI9341

clean-ILI9341:
	-$(RM) ./ILI9341/fonts.cyclo ./ILI9341/fonts.d ./ILI9341/fonts.o ./ILI9341/fonts.su ./ILI9341/ili9341.cyclo ./ILI9341/ili9341.d ./ILI9341/ili9341.o ./ILI9341/ili9341.su

.PHONY: clean-ILI9341

