################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/ioLibrary/Internet/MQTT/MQTTPacket/src/MQTTConnectClient.c \
../Drivers/ioLibrary/Internet/MQTT/MQTTPacket/src/MQTTConnectServer.c \
../Drivers/ioLibrary/Internet/MQTT/MQTTPacket/src/MQTTDeserializePublish.c \
../Drivers/ioLibrary/Internet/MQTT/MQTTPacket/src/MQTTFormat.c \
../Drivers/ioLibrary/Internet/MQTT/MQTTPacket/src/MQTTPacket.c \
../Drivers/ioLibrary/Internet/MQTT/MQTTPacket/src/MQTTSerializePublish.c \
../Drivers/ioLibrary/Internet/MQTT/MQTTPacket/src/MQTTSubscribeClient.c \
../Drivers/ioLibrary/Internet/MQTT/MQTTPacket/src/MQTTSubscribeServer.c \
../Drivers/ioLibrary/Internet/MQTT/MQTTPacket/src/MQTTUnsubscribeClient.c \
../Drivers/ioLibrary/Internet/MQTT/MQTTPacket/src/MQTTUnsubscribeServer.c 

OBJS += \
./Drivers/ioLibrary/Internet/MQTT/MQTTPacket/src/MQTTConnectClient.o \
./Drivers/ioLibrary/Internet/MQTT/MQTTPacket/src/MQTTConnectServer.o \
./Drivers/ioLibrary/Internet/MQTT/MQTTPacket/src/MQTTDeserializePublish.o \
./Drivers/ioLibrary/Internet/MQTT/MQTTPacket/src/MQTTFormat.o \
./Drivers/ioLibrary/Internet/MQTT/MQTTPacket/src/MQTTPacket.o \
./Drivers/ioLibrary/Internet/MQTT/MQTTPacket/src/MQTTSerializePublish.o \
./Drivers/ioLibrary/Internet/MQTT/MQTTPacket/src/MQTTSubscribeClient.o \
./Drivers/ioLibrary/Internet/MQTT/MQTTPacket/src/MQTTSubscribeServer.o \
./Drivers/ioLibrary/Internet/MQTT/MQTTPacket/src/MQTTUnsubscribeClient.o \
./Drivers/ioLibrary/Internet/MQTT/MQTTPacket/src/MQTTUnsubscribeServer.o 

C_DEPS += \
./Drivers/ioLibrary/Internet/MQTT/MQTTPacket/src/MQTTConnectClient.d \
./Drivers/ioLibrary/Internet/MQTT/MQTTPacket/src/MQTTConnectServer.d \
./Drivers/ioLibrary/Internet/MQTT/MQTTPacket/src/MQTTDeserializePublish.d \
./Drivers/ioLibrary/Internet/MQTT/MQTTPacket/src/MQTTFormat.d \
./Drivers/ioLibrary/Internet/MQTT/MQTTPacket/src/MQTTPacket.d \
./Drivers/ioLibrary/Internet/MQTT/MQTTPacket/src/MQTTSerializePublish.d \
./Drivers/ioLibrary/Internet/MQTT/MQTTPacket/src/MQTTSubscribeClient.d \
./Drivers/ioLibrary/Internet/MQTT/MQTTPacket/src/MQTTSubscribeServer.d \
./Drivers/ioLibrary/Internet/MQTT/MQTTPacket/src/MQTTUnsubscribeClient.d \
./Drivers/ioLibrary/Internet/MQTT/MQTTPacket/src/MQTTUnsubscribeServer.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/ioLibrary/Internet/MQTT/MQTTPacket/src/%.o Drivers/ioLibrary/Internet/MQTT/MQTTPacket/src/%.su Drivers/ioLibrary/Internet/MQTT/MQTTPacket/src/%.cyclo: ../Drivers/ioLibrary/Internet/MQTT/MQTTPacket/src/%.c Drivers/ioLibrary/Internet/MQTT/MQTTPacket/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xC '-DMBEDTLS_CONFIG_FILE=<mbedtls_config.h>' -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Drivers/HLW8032/inc -I../Drivers/SPI_flash/inc -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Middlewares/Third_Party/Littlefs/Inlude -I../Middlewares/Third_Party/file_system_adstractions -I../Drivers/ioLibrary -I../Drivers/ioLibrary/Ethernet -I../Drivers/ioLibrary/Ethernet/W5500 -I../Drivers/ioLibrary/Internet -I../Drivers/ioLibrary/Internet/DHCP -I../Drivers/ioLibrary/Internet/DNS -I../Drivers/ioLibrary/Internet/httpServer -I../Drivers/ioLibrary/Internet/MQTT -I../Drivers/ioLibrary/Internet/MQTT/MQTTPacket/src -I../Drivers/ioLibrary/Internet/DNS/dns_abstractions -I../Core/app/http_serv_app/inc -I../MBEDTLS/App -I../Middlewares/Third_Party/mbedTLS/include/mbedtls -I../Middlewares/Third_Party/mbedTLS/include -I../Drivers/ioLibrary/Internet/FTPServer -I../Core/app/mqtt_app/include -I../Core/app/broadcast_message_app/include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-ioLibrary-2f-Internet-2f-MQTT-2f-MQTTPacket-2f-src

clean-Drivers-2f-ioLibrary-2f-Internet-2f-MQTT-2f-MQTTPacket-2f-src:
	-$(RM) ./Drivers/ioLibrary/Internet/MQTT/MQTTPacket/src/MQTTConnectClient.cyclo ./Drivers/ioLibrary/Internet/MQTT/MQTTPacket/src/MQTTConnectClient.d ./Drivers/ioLibrary/Internet/MQTT/MQTTPacket/src/MQTTConnectClient.o ./Drivers/ioLibrary/Internet/MQTT/MQTTPacket/src/MQTTConnectClient.su ./Drivers/ioLibrary/Internet/MQTT/MQTTPacket/src/MQTTConnectServer.cyclo ./Drivers/ioLibrary/Internet/MQTT/MQTTPacket/src/MQTTConnectServer.d ./Drivers/ioLibrary/Internet/MQTT/MQTTPacket/src/MQTTConnectServer.o ./Drivers/ioLibrary/Internet/MQTT/MQTTPacket/src/MQTTConnectServer.su ./Drivers/ioLibrary/Internet/MQTT/MQTTPacket/src/MQTTDeserializePublish.cyclo ./Drivers/ioLibrary/Internet/MQTT/MQTTPacket/src/MQTTDeserializePublish.d ./Drivers/ioLibrary/Internet/MQTT/MQTTPacket/src/MQTTDeserializePublish.o ./Drivers/ioLibrary/Internet/MQTT/MQTTPacket/src/MQTTDeserializePublish.su ./Drivers/ioLibrary/Internet/MQTT/MQTTPacket/src/MQTTFormat.cyclo ./Drivers/ioLibrary/Internet/MQTT/MQTTPacket/src/MQTTFormat.d ./Drivers/ioLibrary/Internet/MQTT/MQTTPacket/src/MQTTFormat.o ./Drivers/ioLibrary/Internet/MQTT/MQTTPacket/src/MQTTFormat.su ./Drivers/ioLibrary/Internet/MQTT/MQTTPacket/src/MQTTPacket.cyclo ./Drivers/ioLibrary/Internet/MQTT/MQTTPacket/src/MQTTPacket.d ./Drivers/ioLibrary/Internet/MQTT/MQTTPacket/src/MQTTPacket.o ./Drivers/ioLibrary/Internet/MQTT/MQTTPacket/src/MQTTPacket.su ./Drivers/ioLibrary/Internet/MQTT/MQTTPacket/src/MQTTSerializePublish.cyclo ./Drivers/ioLibrary/Internet/MQTT/MQTTPacket/src/MQTTSerializePublish.d ./Drivers/ioLibrary/Internet/MQTT/MQTTPacket/src/MQTTSerializePublish.o ./Drivers/ioLibrary/Internet/MQTT/MQTTPacket/src/MQTTSerializePublish.su ./Drivers/ioLibrary/Internet/MQTT/MQTTPacket/src/MQTTSubscribeClient.cyclo ./Drivers/ioLibrary/Internet/MQTT/MQTTPacket/src/MQTTSubscribeClient.d ./Drivers/ioLibrary/Internet/MQTT/MQTTPacket/src/MQTTSubscribeClient.o ./Drivers/ioLibrary/Internet/MQTT/MQTTPacket/src/MQTTSubscribeClient.su ./Drivers/ioLibrary/Internet/MQTT/MQTTPacket/src/MQTTSubscribeServer.cyclo ./Drivers/ioLibrary/Internet/MQTT/MQTTPacket/src/MQTTSubscribeServer.d ./Drivers/ioLibrary/Internet/MQTT/MQTTPacket/src/MQTTSubscribeServer.o ./Drivers/ioLibrary/Internet/MQTT/MQTTPacket/src/MQTTSubscribeServer.su ./Drivers/ioLibrary/Internet/MQTT/MQTTPacket/src/MQTTUnsubscribeClient.cyclo ./Drivers/ioLibrary/Internet/MQTT/MQTTPacket/src/MQTTUnsubscribeClient.d ./Drivers/ioLibrary/Internet/MQTT/MQTTPacket/src/MQTTUnsubscribeClient.o ./Drivers/ioLibrary/Internet/MQTT/MQTTPacket/src/MQTTUnsubscribeClient.su ./Drivers/ioLibrary/Internet/MQTT/MQTTPacket/src/MQTTUnsubscribeServer.cyclo ./Drivers/ioLibrary/Internet/MQTT/MQTTPacket/src/MQTTUnsubscribeServer.d ./Drivers/ioLibrary/Internet/MQTT/MQTTPacket/src/MQTTUnsubscribeServer.o ./Drivers/ioLibrary/Internet/MQTT/MQTTPacket/src/MQTTUnsubscribeServer.su

.PHONY: clean-Drivers-2f-ioLibrary-2f-Internet-2f-MQTT-2f-MQTTPacket-2f-src

