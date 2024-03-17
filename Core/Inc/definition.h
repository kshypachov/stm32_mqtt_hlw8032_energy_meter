/*
 * definition.h
 *
 *  Created on: Jan 10, 2024
 *      Author: kirill
 */

#ifndef INC_DEFINITION_H_
#define INC_DEFINITION_H_

/*------------------------FIRMWARE----------------------------*/
#define UPGRADE_PATTERN			0xA5 //просто случайное число его ожидает считать бутлоадер чтобы начать апгрейд прошивки.
#define UPGRADE_PATERN_FILE		"upgrade_stat"
#define FIRMWARE_FILE			"firmware.bin"

/*----------------------DNS--------------------------*/
#define	MAX_DNS_BUF_SIZE		1024
#define MAX_DOMAIN_NAME   		128
#define	MAX_DNS_RETRY     		2
#define	DNS_WAIT_TIME     		3
#define DNS_USE_MUTEX

/*----------------MQTT-------------------------------*/
#define TOPIK_MAX_LEN				128
#define IP_v4_LEN					18
#define DEV_UID_LEN					14
#define MQTT_BUF_LEN				1024
#define MAX_MQTT_LOGIN_LEN			33
#define MAX_MQTT_PASS_LEN			33
#define SUBSCR_TOPIK_BUF_LEN		64
#define COMMAND_TIMEOUT_MS			10000
#define TOPIK_MAX_LEN				128
#define	SEND_PAYLOD_LEN				600
//#define NUMBER_SWITCH_TOPIKS		REG_COILS_NREGS
//#define NUMBER_INPUT_TOPIKS			REG_DISCRETE_NREGS
#define UPDATE_MQTT_PARAM_INTERVAL	30
#define RELOGIN_MQTT_INTERVAL		3600

#define dev_system						"vombat"
#define dev_common_name					"Energy-Counter"
#define dev_model_name					"PowerMeter3000"
#define dev_manufacturer_name			"Manufacturer"
#define dev_hw_ver						"0.1"
#define dev_sw_ver						"1.0.2"

#define dev_class_energy				"energy"
#define dev_class_energy_human			"Енергія"
#define dev_class_energy_state			"\"state_class\": \"total_increasing\",\n"
#define dev_class_energy_unit_of_measurement	"kWh"

#define dev_class_voltage				"voltage"
#define dev_class_voltage_human			"Напруга"
#define dev_class_voltage_unit_of_measurement	"V"

#define dev_class_power					"power"
#define dev_class_power_human			"Активна потужність"
#define dev_class_power_unit_of_measurement	"W"

#define dev_class_power_factor			"power_factor"
#define dev_class_power_factor_human	"Коефіцієнт потужності"
#define dev_class_power_factor_unit_of_measurement "%"

#define dev_class_current				"current"
#define dev_class_current_human			"Струм"
#define dev_class_current_unit_of_measurement	"A"

#define dev_class_apparent_power		"apparent_power"
#define dev_class_apparent_power_human	"Повна потужність"
#define dev_class_apparent_power_unit_of_measurement	"VA"

#define state_topik						"main"
#define component_sensor				"sensor"

/*--------App def----------------*/
#define delay1s			1000
#define delay2s			delay1s * 2
#define delay30s		delay1s * 30
#define delay10s		delay1s * 10
#define delay5s			delay1s * 5
#define delay3s			delay1s * 3
#define delay0_5s		delay1s / 2
#define delay0_2s		delay1s / 5
#define delay0_1s		delay1s / 10
//#define SPI_THREADSAFE
//#define UID_BASE		0x1FFF7A10 // адрес в котором хранится уникальный айди процессора

/*---------NetworkDef------------*/
#define SOCKET_BUFF_SIZE		2048 //buffer allocated in w5500 for socket
#define DATA_BUF_SIZE			SOCKET_BUFF_SIZE
#define MAX_DHCP_FAIL			1000000000
#define ETH_LINK_UP				1
#define ETH_LINK_DOWN			0

/*---------------HTTP_SERVER_DEFINEs------------------------*/
//#define HTTP_SERVER_NSOCKETS	3
#define HTTP_SERVER_PORT		80
#define MAX_CONTENT_NAME_LEN	50
#define MAX_CONTENT_CALLBACK	4
#define HTTP_FS_DIR				"web/"
#define	FIRMWARE_FS_DIR			"firmware/"
#define TMP_BUFF_FOR_FILE_RECV	512
#define TMP_BUF_FOR_MD5_CALC	64


/*---------------SOCKETS-------------------------------------*/
#define DHCP_SOCKET				0
#define HTTP_SERVER_SOCKET		1
#define HTTP_SERVER_SOCKET1		2
#define HTTP_SERVER_SOCKET2		3
#define SERVICE_SOCKET			4
#define MQTT_CLIENT_SOCKET		5

/*------------------------LFS--------------------------------*/
#define LFS_USE_MUTEX
#define POW_SETT_FILE			"power_sett.conf"
#define MQTT_SETT_FILE			"mqtt_sett.conf"
#define MB_TCP_SETT_FILE		"mb_tcp_sett.conf"
#define KW_COUNT_STOR_FILE		"kWh_count_stor.conf"


/*-------------------------POWER SHUNT SETTINGS--------------*/
#define DEFAULT_SHUNT_RESISTANSE	0.001
#define ENERGY_VALUE_SAVE_INTERVAL	3600
#define DETECT_POWER_TRASHOLD_W		15


#endif /* INC_DEFINITION_H_ */
