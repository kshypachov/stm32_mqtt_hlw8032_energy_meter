################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Middlewares/Third_Party/mbedTLS/library/subdir.mk
-include Middlewares/Third_Party/file_system_adstractions/subdir.mk
-include Middlewares/Third_Party/Littlefs/Source/subdir.mk
-include Middlewares/Third_Party/FreeRTOS/Source/portable/MemMang/subdir.mk
-include Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F/subdir.mk
-include Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/subdir.mk
-include Middlewares/Third_Party/FreeRTOS/Source/subdir.mk
-include MBEDTLS/App/subdir.mk
-include Drivers/ioLibrary/Internet/httpServer/subdir.mk
-include Drivers/ioLibrary/Internet/MQTT/MQTTPacket/src/subdir.mk
-include Drivers/ioLibrary/Internet/MQTT/subdir.mk
-include Drivers/ioLibrary/Internet/DNS/dns_abstractions/subdir.mk
-include Drivers/ioLibrary/Internet/DNS/subdir.mk
-include Drivers/ioLibrary/Internet/DHCP/subdir.mk
-include Drivers/ioLibrary/Ethernet/W5500/subdir.mk
-include Drivers/ioLibrary/Ethernet/subdir.mk
-include Drivers/ioLibrary/subdir.mk
-include Drivers/STM32F4xx_HAL_Driver/Src/subdir.mk
-include Drivers/SPI_flash/src/subdir.mk
-include Drivers/HLW8032/src/subdir.mk
-include Core/app/mqtt_app/source/subdir.mk
-include Core/app/http_serv_app/src/subdir.mk
-include Core/Startup/subdir.mk
-include Core/Src/subdir.mk
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


BUILD_ARTIFACT_NAME := stm32_mqtt_hlw8032_energy_meter
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
stm32_mqtt_hlw8032_energy_meter.elf \

MAP_FILES += \
stm32_mqtt_hlw8032_energy_meter.map \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
stm32_mqtt_hlw8032_energy_meter.list \

OBJCOPY_HEX += \
stm32_mqtt_hlw8032_energy_meter.hex \

OBJCOPY_BIN += \
stm32_mqtt_hlw8032_energy_meter.bin \


# All Target
all: main-build

# Main-build Target
main-build: stm32_mqtt_hlw8032_energy_meter.elf secondary-outputs

# Tool invocations
stm32_mqtt_hlw8032_energy_meter.elf stm32_mqtt_hlw8032_energy_meter.map: $(OBJS) $(USER_OBJS) C:\Users\kirill\STM32CubeIDE\workspace_1.13.2\stm32_mqtt_hlw8032_energy_meter\STM32F401CCUX_FLASH.ld makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-gcc -o "stm32_mqtt_hlw8032_energy_meter.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m4 -T"C:\Users\kirill\STM32CubeIDE\workspace_1.13.2\stm32_mqtt_hlw8032_energy_meter\STM32F401CCUX_FLASH.ld" --specs=nosys.specs -Wl,-Map="stm32_mqtt_hlw8032_energy_meter.map" -Wl,--gc-sections -static --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -u _printf_float -u _scanf_float -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

stm32_mqtt_hlw8032_energy_meter.list: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "stm32_mqtt_hlw8032_energy_meter.list"
	@echo 'Finished building: $@'
	@echo ' '

stm32_mqtt_hlw8032_energy_meter.hex: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objcopy  -O ihex $(EXECUTABLES) "stm32_mqtt_hlw8032_energy_meter.hex"
	@echo 'Finished building: $@'
	@echo ' '

stm32_mqtt_hlw8032_energy_meter.bin: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "stm32_mqtt_hlw8032_energy_meter.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) default.size.stdout stm32_mqtt_hlw8032_energy_meter.bin stm32_mqtt_hlw8032_energy_meter.elf stm32_mqtt_hlw8032_energy_meter.hex stm32_mqtt_hlw8032_energy_meter.list stm32_mqtt_hlw8032_energy_meter.map
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_HEX) $(OBJCOPY_BIN)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents main-build fail-specified-linker-script-missing warn-no-linker-script-specified

-include ../makefile.targets
