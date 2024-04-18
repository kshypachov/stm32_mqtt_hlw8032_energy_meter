This firmware works with bootloader and start execution from 0x08010000.
bootloader needed only for updating firmware from SPI Flash. You can use bootloader from my repository or write your own bootloader. 

This code writed for stm32f401ce and support Home Assistant via MQTT. You can connect module to HA without any another integrations, only MQTT and HA.
Module provide some data parameters, readed from HLW8032
1) Voltage
2) Current
3) Energy
4) Power Factor
5) Active Power
And additionaly calculate Appatern Power (Voltage * Current)
Module stor Energy data into Flash between reboot or poweroff. 
