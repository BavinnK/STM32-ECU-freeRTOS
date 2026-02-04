################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/LEGACY_src_drivers/MyAdc.c \
../Core/Src/LEGACY_src_drivers/MyHcsr04.c \
../Core/Src/LEGACY_src_drivers/MyPwm.c \
../Core/Src/LEGACY_src_drivers/MyRelay.c \
../Core/Src/LEGACY_src_drivers/MySpi.c \
../Core/Src/LEGACY_src_drivers/myUSART2.c 

OBJS += \
./Core/Src/LEGACY_src_drivers/MyAdc.o \
./Core/Src/LEGACY_src_drivers/MyHcsr04.o \
./Core/Src/LEGACY_src_drivers/MyPwm.o \
./Core/Src/LEGACY_src_drivers/MyRelay.o \
./Core/Src/LEGACY_src_drivers/MySpi.o \
./Core/Src/LEGACY_src_drivers/myUSART2.o 

C_DEPS += \
./Core/Src/LEGACY_src_drivers/MyAdc.d \
./Core/Src/LEGACY_src_drivers/MyHcsr04.d \
./Core/Src/LEGACY_src_drivers/MyPwm.d \
./Core/Src/LEGACY_src_drivers/MyRelay.d \
./Core/Src/LEGACY_src_drivers/MySpi.d \
./Core/Src/LEGACY_src_drivers/myUSART2.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/LEGACY_src_drivers/%.o Core/Src/LEGACY_src_drivers/%.su Core/Src/LEGACY_src_drivers/%.cyclo: ../Core/Src/LEGACY_src_drivers/%.c Core/Src/LEGACY_src_drivers/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F446xx -c -I"C:/Users/pc/Desktop/STM_PROJECTS/V2.4_ECU_STM32_PROJECT/Core/Inc/ILI9341" -I"C:/Users/pc/Desktop/STM_PROJECTS/V2.4_ECU_STM32_PROJECT/Core/Inc/LEGACY_inc_drivers" -I"C:/Users/pc/Desktop/STM_PROJECTS/V2.4_ECU_STM32_PROJECT/Core/MyDRIVERS/SPI" -I"C:/Users/pc/Desktop/STM_PROJECTS/V2.4_ECU_STM32_PROJECT/Core/MyDRIVERS/CLOCK" -I"C:/Users/pc/Desktop/STM_PROJECTS/V2.4_ECU_STM32_PROJECT/Core/MyDRIVERS/USART" -I"C:/Users/pc/Desktop/STM_PROJECTS/V2.4_ECU_STM32_PROJECT/Core/MyDRIVERS/GPIO" -I"C:/Users/pc/Desktop/STM_PROJECTS/V2.4_ECU_STM32_PROJECT/Core/MyDRIVERS/DMA" -I"C:/Users/pc/Desktop/STM_PROJECTS/V2.4_ECU_STM32_PROJECT/Core/MyDRIVERS/ADC" -I"C:/Users/pc/Desktop/STM_PROJECTS/V2.4_ECU_STM32_PROJECT/Core/Inc" -I"C:/Users/pc/Desktop/STM_PROJECTS/V2.4_ECU_STM32_PROJECT/Core/ThirdParty/FreeRTOS/include" -I"C:/Users/pc/Desktop/STM_PROJECTS/V2.4_ECU_STM32_PROJECT/Core/ThirdParty/FreeRTOS/portable" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Core/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-LEGACY_src_drivers

clean-Core-2f-Src-2f-LEGACY_src_drivers:
	-$(RM) ./Core/Src/LEGACY_src_drivers/MyAdc.cyclo ./Core/Src/LEGACY_src_drivers/MyAdc.d ./Core/Src/LEGACY_src_drivers/MyAdc.o ./Core/Src/LEGACY_src_drivers/MyAdc.su ./Core/Src/LEGACY_src_drivers/MyHcsr04.cyclo ./Core/Src/LEGACY_src_drivers/MyHcsr04.d ./Core/Src/LEGACY_src_drivers/MyHcsr04.o ./Core/Src/LEGACY_src_drivers/MyHcsr04.su ./Core/Src/LEGACY_src_drivers/MyPwm.cyclo ./Core/Src/LEGACY_src_drivers/MyPwm.d ./Core/Src/LEGACY_src_drivers/MyPwm.o ./Core/Src/LEGACY_src_drivers/MyPwm.su ./Core/Src/LEGACY_src_drivers/MyRelay.cyclo ./Core/Src/LEGACY_src_drivers/MyRelay.d ./Core/Src/LEGACY_src_drivers/MyRelay.o ./Core/Src/LEGACY_src_drivers/MyRelay.su ./Core/Src/LEGACY_src_drivers/MySpi.cyclo ./Core/Src/LEGACY_src_drivers/MySpi.d ./Core/Src/LEGACY_src_drivers/MySpi.o ./Core/Src/LEGACY_src_drivers/MySpi.su ./Core/Src/LEGACY_src_drivers/myUSART2.cyclo ./Core/Src/LEGACY_src_drivers/myUSART2.d ./Core/Src/LEGACY_src_drivers/myUSART2.o ./Core/Src/LEGACY_src_drivers/myUSART2.su

.PHONY: clean-Core-2f-Src-2f-LEGACY_src_drivers

