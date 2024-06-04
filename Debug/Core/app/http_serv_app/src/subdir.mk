################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/app/http_serv_app/src/http_app.c 

OBJS += \
./Core/app/http_serv_app/src/http_app.o 

C_DEPS += \
./Core/app/http_serv_app/src/http_app.d 


# Each subdirectory must supply rules for building sources it contributes
Core/app/http_serv_app/src/%.o Core/app/http_serv_app/src/%.su Core/app/http_serv_app/src/%.cyclo: ../Core/app/http_serv_app/src/%.c Core/app/http_serv_app/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xC '-DMBEDTLS_CONFIG_FILE=<mbedtls_config.h>' -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Drivers/HLW8032/inc -I../Drivers/SPI_flash/inc -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Middlewares/Third_Party/Littlefs/Inlude -I../Middlewares/Third_Party/file_system_adstractions -I../Drivers/ioLibrary -I../Drivers/ioLibrary/Ethernet -I../Drivers/ioLibrary/Ethernet/W5500 -I../Drivers/ioLibrary/Internet -I../Drivers/ioLibrary/Internet/DHCP -I../Drivers/ioLibrary/Internet/DNS -I../Drivers/ioLibrary/Internet/httpServer -I../Drivers/ioLibrary/Internet/MQTT -I../Drivers/ioLibrary/Internet/MQTT/MQTTPacket/src -I../Drivers/ioLibrary/Internet/DNS/dns_abstractions -I../Core/app/http_serv_app/inc -I../MBEDTLS/App -I../Middlewares/Third_Party/mbedTLS/include/mbedtls -I../Middlewares/Third_Party/mbedTLS/include -I../Drivers/ioLibrary/Internet/FTPServer -I../Core/app/mqtt_app/include -I../Core/app/broadcast_message_app/include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-app-2f-http_serv_app-2f-src

clean-Core-2f-app-2f-http_serv_app-2f-src:
	-$(RM) ./Core/app/http_serv_app/src/http_app.cyclo ./Core/app/http_serv_app/src/http_app.d ./Core/app/http_serv_app/src/http_app.o ./Core/app/http_serv_app/src/http_app.su

.PHONY: clean-Core-2f-app-2f-http_serv_app-2f-src

