/*
 * definition.h
 *
 *  Created on: Jan 10, 2024
 *      Author: kirill
 */

#ifndef INC_DEFINITION_H_
#define INC_DEFINITION_H_

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
//#define NUMBER_SWITCH_TOPIKS		REG_COILS_NREGS
//#define NUMBER_INPUT_TOPIKS			REG_DISCRETE_NREGS
#define UPDATE_MQTT_PARAM_INTERVAL	30
#define RELOGIN_MQTT_INTERVAL		3600

/*--------App def----------------*/
#define delay1s			1000
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
#define MAX_DHCP_FAIL			10
#define ETH_LINK_UP				1
#define ETH_LINK_DOWN			0

/*---------------HTTP_SERVER_DEFINEs------------------------*/
//#define HTTP_SERVER_NSOCKETS	3
#define HTTP_SERVER_PORT		80
#define MAX_CONTENT_NAME_LEN	50
#define MAX_CONTENT_CALLBACK	4
#define HTTP_FS_DIR				"web/"
#define TMP_BUFF_FOR_FILE_RECV	512


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


/*-------------------------POWER SHUNT SETTINGS--------------*/
#define DEFAULT_SHUNT_RESISTANSE	0.001


#endif /* INC_DEFINITION_H_ */
