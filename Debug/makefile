################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Drivers/STM32F4xx_HAL_Driver/Src/subdir.mk
-include Core/ThirdParty/FreeRTOS/portable/subdir.mk
-include Core/ThirdParty/FreeRTOS/Source/subdir.mk
-include Core/Startup/subdir.mk
-include Core/Src/ILI9341/subdir.mk
-include Core/Src/subdir.mk
-include Core/MyDRIVERS/USART/subdir.mk
-include Core/MyDRIVERS/GPIO/subdir.mk
-include Core/MyDRIVERS/DMA/subdir.mk
-include Core/MyDRIVERS/ADC/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := V2.4_ECU_STM32_PROJECT
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
V2.4_ECU_STM32_PROJECT.elf \

MAP_FILES += \
V2.4_ECU_STM32_PROJECT.map \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
V2.4_ECU_STM32_PROJECT.list \


# All Target
all: main-build

# Main-build Target
main-build: V2.4_ECU_STM32_PROJECT.elf secondary-outputs

# Tool invocations
V2.4_ECU_STM32_PROJECT.elf V2.4_ECU_STM32_PROJECT.map: $(OBJS) $(USER_OBJS) C:\Users\pc\Desktop\STM_PROJECTS\V2.4_ECU_STM32_PROJECT\STM32F446RETX_FLASH.ld makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-gcc -o "V2.4_ECU_STM32_PROJECT.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m4 -T"C:\Users\pc\Desktop\STM_PROJECTS\V2.4_ECU_STM32_PROJECT\STM32F446RETX_FLASH.ld" --specs=nosys.specs -Wl,-Map="V2.4_ECU_STM32_PROJECT.map" -Wl,--gc-sections -static --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

V2.4_ECU_STM32_PROJECT.list: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "V2.4_ECU_STM32_PROJECT.list"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) V2.4_ECU_STM32_PROJECT.elf V2.4_ECU_STM32_PROJECT.list V2.4_ECU_STM32_PROJECT.map default.size.stdout
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents main-build fail-specified-linker-script-missing warn-no-linker-script-specified

-include ../makefile.targets
