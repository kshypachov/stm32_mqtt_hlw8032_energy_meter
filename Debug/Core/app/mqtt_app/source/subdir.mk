################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/app/mqtt_app/source/mqtt_app.c \
../Core/app/mqtt_app/source/mqtt_gen_strings.c 

OBJS += \
./Core/app/mqtt_app/source/mqtt_app.o \
./Core/app/mqtt_app/source/mqtt_gen_strings.o 

C_DEPS += \
./Core/app/mqtt_app/source/mqtt_app.d \
./Core/app/mqtt_app/source/mqtt_gen_strings.d 


# Each subdirectory must supply rules for building sources it contributes
Core/app/mqtt_app/source/%.o Core/app/mqtt_app/source/%.su Core/app/mqtt_app/source/%.cyclo: ../Core/app/mqtt_app/source/%.c Core/app/mqtt_app/source/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xC '-DMBEDTLS_CONFIG_FILE=<mbedtls_config.h>' -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Drivers/HLW8032/inc -I../Drivers/SPI_flash/inc -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Middlewares/Third_Party/Littlefs/Inlude -I../Middlewares/Third_Party/file_system_adstractions -I../Drivers/ioLibrary -I../Drivers/ioLibrary/Ethernet -I../Drivers/ioLibrary/Ethernet/W5500 -I../Drivers/ioLibrary/Internet -I../Drivers/ioLibrary/Internet/DHCP -I../Drivers/ioLibrary/Internet/DNS -I../Drivers/ioLibrary/Internet/httpServer -I../Drivers/ioLibrary/Internet/MQTT -I../Drivers/ioLibrary/Internet/MQTT/MQTTPacket/src -I../Drivers/ioLibrary/Internet/DNS/dns_abstractions -I../Core/app/http_serv_app/inc -I../MBEDTLS/App -I../Middlewares/Third_Party/mbedTLS/include/mbedtls -I../Middlewares/Third_Party/mbedTLS/include -I../Drivers/ioLibrary/Internet/FTPServer -I../Core/app/mqtt_app/include -I../Core/app/broadcast_message_app/include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-app-2f-mqtt_app-2f-source

clean-Core-2f-app-2f-mqtt_app-2f-source:
	-$(RM) ./Core/app/mqtt_app/source/mqtt_app.cyclo ./Core/app/mqtt_app/source/mqtt_app.d ./Core/app/mqtt_app/source/mqtt_app.o ./Core/app/mqtt_app/source/mqtt_app.su ./Core/app/mqtt_app/source/mqtt_gen_strings.cyclo ./Core/app/mqtt_app/source/mqtt_gen_strings.d ./Core/app/mqtt_app/source/mqtt_gen_strings.o ./Core/app/mqtt_app/source/mqtt_gen_strings.su

.PHONY: clean-Core-2f-app-2f-mqtt_app-2f-source

