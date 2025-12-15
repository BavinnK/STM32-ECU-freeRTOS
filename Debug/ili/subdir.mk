################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ili/fonts.c \
../ili/ili9341.c 

OBJS += \
./ili/fonts.o \
./ili/ili9341.o 

C_DEPS += \
./ili/fonts.d \
./ili/ili9341.d 


# Each subdirectory must supply rules for building sources it contributes
ili/%.o ili/%.su ili/%.cyclo: ../ili/%.c ili/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F446xx -c -I../Core/Inc -I"C:/Users/pc/Desktop/STM_PROJECTS/V2.1_ECU_STM32_PROJECT/ili" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-ili

clean-ili:
	-$(RM) ./ili/fonts.cyclo ./ili/fonts.d ./ili/fonts.o ./ili/fonts.su ./ili/ili9341.cyclo ./ili/ili9341.d ./ili/ili9341.o ./ili/ili9341.su

.PHONY: clean-ili

