################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/ThirdParty/FreeRTOS/Source/croutine.c \
../Core/ThirdParty/FreeRTOS/Source/event_groups.c \
../Core/ThirdParty/FreeRTOS/Source/list.c \
../Core/ThirdParty/FreeRTOS/Source/queue.c \
../Core/ThirdParty/FreeRTOS/Source/stream_buffer.c \
../Core/ThirdParty/FreeRTOS/Source/tasks.c \
../Core/ThirdParty/FreeRTOS/Source/timers.c 

OBJS += \
./Core/ThirdParty/FreeRTOS/Source/croutine.o \
./Core/ThirdParty/FreeRTOS/Source/event_groups.o \
./Core/ThirdParty/FreeRTOS/Source/list.o \
./Core/ThirdParty/FreeRTOS/Source/queue.o \
./Core/ThirdParty/FreeRTOS/Source/stream_buffer.o \
./Core/ThirdParty/FreeRTOS/Source/tasks.o \
./Core/ThirdParty/FreeRTOS/Source/timers.o 

C_DEPS += \
./Core/ThirdParty/FreeRTOS/Source/croutine.d \
./Core/ThirdParty/FreeRTOS/Source/event_groups.d \
./Core/ThirdParty/FreeRTOS/Source/list.d \
./Core/ThirdParty/FreeRTOS/Source/queue.d \
./Core/ThirdParty/FreeRTOS/Source/stream_buffer.d \
./Core/ThirdParty/FreeRTOS/Source/tasks.d \
./Core/ThirdParty/FreeRTOS/Source/timers.d 


# Each subdirectory must supply rules for building sources it contributes
Core/ThirdParty/FreeRTOS/Source/%.o Core/ThirdParty/FreeRTOS/Source/%.su Core/ThirdParty/FreeRTOS/Source/%.cyclo: ../Core/ThirdParty/FreeRTOS/Source/%.c Core/ThirdParty/FreeRTOS/Source/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F446xx -c -I"C:/Users/pc/Desktop/STM_PROJECTS/V2.4_ECU_STM32_PROJECT/Core/Inc/ILI9341" -I"C:/Users/pc/Desktop/STM_PROJECTS/V2.4_ECU_STM32_PROJECT/Core/MyDRIVERS/CLOCK" -I"C:/Users/pc/Desktop/STM_PROJECTS/V2.4_ECU_STM32_PROJECT/Core/MyDRIVERS/USART" -I"C:/Users/pc/Desktop/STM_PROJECTS/V2.4_ECU_STM32_PROJECT/Core/MyDRIVERS/GPIO" -I"C:/Users/pc/Desktop/STM_PROJECTS/V2.4_ECU_STM32_PROJECT/Core/MyDRIVERS/DMA" -I"C:/Users/pc/Desktop/STM_PROJECTS/V2.4_ECU_STM32_PROJECT/Core/MyDRIVERS/ADC" -I"C:/Users/pc/Desktop/STM_PROJECTS/V2.4_ECU_STM32_PROJECT/Core/Inc" -I"C:/Users/pc/Desktop/STM_PROJECTS/V2.4_ECU_STM32_PROJECT/Core/ThirdParty/FreeRTOS/include" -I"C:/Users/pc/Desktop/STM_PROJECTS/V2.4_ECU_STM32_PROJECT/Core/ThirdParty/FreeRTOS/portable" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Core/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-ThirdParty-2f-FreeRTOS-2f-Source

clean-Core-2f-ThirdParty-2f-FreeRTOS-2f-Source:
	-$(RM) ./Core/ThirdParty/FreeRTOS/Source/croutine.cyclo ./Core/ThirdParty/FreeRTOS/Source/croutine.d ./Core/ThirdParty/FreeRTOS/Source/croutine.o ./Core/ThirdParty/FreeRTOS/Source/croutine.su ./Core/ThirdParty/FreeRTOS/Source/event_groups.cyclo ./Core/ThirdParty/FreeRTOS/Source/event_groups.d ./Core/ThirdParty/FreeRTOS/Source/event_groups.o ./Core/ThirdParty/FreeRTOS/Source/event_groups.su ./Core/ThirdParty/FreeRTOS/Source/list.cyclo ./Core/ThirdParty/FreeRTOS/Source/list.d ./Core/ThirdParty/FreeRTOS/Source/list.o ./Core/ThirdParty/FreeRTOS/Source/list.su ./Core/ThirdParty/FreeRTOS/Source/queue.cyclo ./Core/ThirdParty/FreeRTOS/Source/queue.d ./Core/ThirdParty/FreeRTOS/Source/queue.o ./Core/ThirdParty/FreeRTOS/Source/queue.su ./Core/ThirdParty/FreeRTOS/Source/stream_buffer.cyclo ./Core/ThirdParty/FreeRTOS/Source/stream_buffer.d ./Core/ThirdParty/FreeRTOS/Source/stream_buffer.o ./Core/ThirdParty/FreeRTOS/Source/stream_buffer.su ./Core/ThirdParty/FreeRTOS/Source/tasks.cyclo ./Core/ThirdParty/FreeRTOS/Source/tasks.d ./Core/ThirdParty/FreeRTOS/Source/tasks.o ./Core/ThirdParty/FreeRTOS/Source/tasks.su ./Core/ThirdParty/FreeRTOS/Source/timers.cyclo ./Core/ThirdParty/FreeRTOS/Source/timers.d ./Core/ThirdParty/FreeRTOS/Source/timers.o ./Core/ThirdParty/FreeRTOS/Source/timers.su

.PHONY: clean-Core-2f-ThirdParty-2f-FreeRTOS-2f-Source

