################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Drivers/STM32F4xx_HAL_Driver/Src/subdir.mk
-include Core/Startup/subdir.mk
<<<<<<< HEAD
-include Core/Src/subdir.mk
=======
-include Core/Src/ILI9341/subdir.mk
-include Core/Src/subdir.mk
-include Core/Inc/subdir.mk
>>>>>>> 0fdbc30 (did a brain surgery on lib for th ili9341)
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


<<<<<<< HEAD
BUILD_ARTIFACT_NAME := V1.0_ECU_PROJECT_STM32
=======
BUILD_ARTIFACT_NAME := V2.1_ECU_STM32_PROJECT
>>>>>>> 0fdbc30 (did a brain surgery on lib for th ili9341)
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
<<<<<<< HEAD
V1.0_ECU_PROJECT_STM32.elf \

MAP_FILES += \
V1.0_ECU_PROJECT_STM32.map \
=======
V2.1_ECU_STM32_PROJECT.elf \

MAP_FILES += \
V2.1_ECU_STM32_PROJECT.map \
>>>>>>> 0fdbc30 (did a brain surgery on lib for th ili9341)

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
<<<<<<< HEAD
V1.0_ECU_PROJECT_STM32.list \
=======
V2.1_ECU_STM32_PROJECT.list \
>>>>>>> 0fdbc30 (did a brain surgery on lib for th ili9341)


# All Target
all: main-build

# Main-build Target
<<<<<<< HEAD
main-build: V1.0_ECU_PROJECT_STM32.elf secondary-outputs

# Tool invocations
V1.0_ECU_PROJECT_STM32.elf V1.0_ECU_PROJECT_STM32.map: $(OBJS) $(USER_OBJS) C:\Users\pc\Documents\STM_32_CORTEX_M4\Projects\V1.0_ECU_PROJECT_STM32\STM32F446RETX_FLASH.ld makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-gcc -o "V1.0_ECU_PROJECT_STM32.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m4 -T"C:\Users\pc\Documents\STM_32_CORTEX_M4\Projects\V1.0_ECU_PROJECT_STM32\STM32F446RETX_FLASH.ld" --specs=nosys.specs -Wl,-Map="V1.0_ECU_PROJECT_STM32.map" -Wl,--gc-sections -static --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
=======
main-build: V2.1_ECU_STM32_PROJECT.elf secondary-outputs

# Tool invocations
V2.1_ECU_STM32_PROJECT.elf V2.1_ECU_STM32_PROJECT.map: $(OBJS) $(USER_OBJS) C:\Users\pc\Desktop\STM_PROJECTS\V2.1_ECU_STM32_PROJECT\STM32F446RETX_FLASH.ld makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-gcc -o "V2.1_ECU_STM32_PROJECT.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m4 -T"C:\Users\pc\Desktop\STM_PROJECTS\V2.1_ECU_STM32_PROJECT\STM32F446RETX_FLASH.ld" --specs=nosys.specs -Wl,-Map="V2.1_ECU_STM32_PROJECT.map" -Wl,--gc-sections -static --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
>>>>>>> 0fdbc30 (did a brain surgery on lib for th ili9341)
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

<<<<<<< HEAD
V1.0_ECU_PROJECT_STM32.list: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "V1.0_ECU_PROJECT_STM32.list"
=======
V2.1_ECU_STM32_PROJECT.list: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "V2.1_ECU_STM32_PROJECT.list"
>>>>>>> 0fdbc30 (did a brain surgery on lib for th ili9341)
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
<<<<<<< HEAD
	-$(RM) V1.0_ECU_PROJECT_STM32.elf V1.0_ECU_PROJECT_STM32.list V1.0_ECU_PROJECT_STM32.map default.size.stdout
=======
	-$(RM) V2.1_ECU_STM32_PROJECT.elf V2.1_ECU_STM32_PROJECT.list V2.1_ECU_STM32_PROJECT.map default.size.stdout
>>>>>>> 0fdbc30 (did a brain surgery on lib for th ili9341)
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents main-build fail-specified-linker-script-missing warn-no-linker-script-specified

-include ../makefile.targets
