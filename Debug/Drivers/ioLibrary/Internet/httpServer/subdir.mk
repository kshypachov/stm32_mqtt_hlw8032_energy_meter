################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/ioLibrary/Internet/httpServer/httpParser.c \
../Drivers/ioLibrary/Internet/httpServer/httpServer.c \
../Drivers/ioLibrary/Internet/httpServer/httpUtil.c 

OBJS += \
./Drivers/ioLibrary/Internet/httpServer/httpParser.o \
./Drivers/ioLibrary/Internet/httpServer/httpServer.o \
./Drivers/ioLibrary/Internet/httpServer/httpUtil.o 

C_DEPS += \
./Drivers/ioLibrary/Internet/httpServer/httpParser.d \
./Drivers/ioLibrary/Internet/httpServer/httpServer.d \
./Drivers/ioLibrary/Internet/httpServer/httpUtil.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/ioLibrary/Internet/httpServer/%.o Drivers/ioLibrary/Internet/httpServer/%.su Drivers/ioLibrary/Internet/httpServer/%.cyclo: ../Drivers/ioLibrary/Internet/httpServer/%.c Drivers/ioLibrary/Internet/httpServer/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xC '-DMBEDTLS_CONFIG_FILE=<mbedtls_config.h>' -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Drivers/HLW8032/inc -I../Drivers/SPI_flash/inc -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Middlewares/Third_Party/Littlefs/Inlude -I../Middlewares/Third_Party/file_system_adstractions -I../Drivers/ioLibrary -I../Drivers/ioLibrary/Ethernet -I../Drivers/ioLibrary/Ethernet/W5500 -I../Drivers/ioLibrary/Internet -I../Drivers/ioLibrary/Internet/DHCP -I../Drivers/ioLibrary/Internet/DNS -I../Drivers/ioLibrary/Internet/httpServer -I../Drivers/ioLibrary/Internet/MQTT -I../Drivers/ioLibrary/Internet/MQTT/MQTTPacket/src -I../Drivers/ioLibrary/Internet/DNS/dns_abstractions -I../Core/app/http_serv_app/inc -I../MBEDTLS/App -I../Middlewares/Third_Party/mbedTLS/include/mbedtls -I../Middlewares/Third_Party/mbedTLS/include -I../Drivers/ioLibrary/Internet/FTPServer -I../Core/app/mqtt_app/include -I../Core/app/broadcast_message_app/include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-ioLibrary-2f-Internet-2f-httpServer

clean-Drivers-2f-ioLibrary-2f-Internet-2f-httpServer:
	-$(RM) ./Drivers/ioLibrary/Internet/httpServer/httpParser.cyclo ./Drivers/ioLibrary/Internet/httpServer/httpParser.d ./Drivers/ioLibrary/Internet/httpServer/httpParser.o ./Drivers/ioLibrary/Internet/httpServer/httpParser.su ./Drivers/ioLibrary/Internet/httpServer/httpServer.cyclo ./Drivers/ioLibrary/Internet/httpServer/httpServer.d ./Drivers/ioLibrary/Internet/httpServer/httpServer.o ./Drivers/ioLibrary/Internet/httpServer/httpServer.su ./Drivers/ioLibrary/Internet/httpServer/httpUtil.cyclo ./Drivers/ioLibrary/Internet/httpServer/httpUtil.d ./Drivers/ioLibrary/Internet/httpServer/httpUtil.o ./Drivers/ioLibrary/Internet/httpServer/httpUtil.su

.PHONY: clean-Drivers-2f-ioLibrary-2f-Internet-2f-httpServer

