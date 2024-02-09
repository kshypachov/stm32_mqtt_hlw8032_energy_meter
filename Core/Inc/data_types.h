/*
 * data_types.h
 *
 *  Created on: Jan 11, 2024
 *      Author: kirill
 */

#ifndef INC_DATA_TYPES_H_
#define INC_DATA_TYPES_H_

#include "stdbool.h"
#include "definition.h"

typedef struct MQTT_cred_t{
	bool save;
	bool enable;
	char uri[MAX_DOMAIN_NAME];
	uint16_t port;
	char login[MAX_MQTT_LOGIN_LEN];
	char pass[MAX_MQTT_PASS_LEN];
}MQTT_cred_struct;

typedef struct Home_assist_t{
	bool save;
	bool enable;
	char topik_prefix[64];
}Home_assist_struct;

typedef struct ModBusTCP_t{
	bool save;
	bool enable;
}ModBusTCP_struct;

typedef struct Ethernet_info_t{
//	bool	save;		/* save settings to flash after change if dhcp static*/
	bool 	link;		/* cable conect 1-connected, 0-disconnected */
	uint8_t duplex; 	/* 0 - half, 1-full */
	uint8_t speed;		/* 0 - 10Mbit/s, 1 - 100Mbit/s */
	uint8_t mac[6];  	/* Source Mac Address */
	uint8_t ip[4];   	/* Source IP Address */
	uint8_t sn[4];   	/* Subnet Mask */
	uint8_t gw[4];  	/* Gateway IP Address */
	uint8_t dns[4];  	/* DNS server IP Address */
	uint8_t dhcp;		/* 1 - Static, 2 - DHCP */
	uint32_t lease_s;	/* DHCP lease time in seconds */
}Ethernet_info_struct;

typedef struct Power_sens_info_t{
	bool 	save;
	float	resistance;
}P_sens_sett_struct;

enum parameters_type{
	MQTT			= 0,
	HA				= 1,
	ModBusTCP 		= 2,
	PowrData    	= 3,
	PowrSensSett	= 4,
	Uptime			= 5,
};

typedef struct Power_sensor_data_t{

	float Voltage;
	float Current;
	float KWatt_h;
	float ActivPower;
	float ApparPower;
	float PowerFactor;
	uint32_t test_pulse_counter;
	uint32_t readed_counter;
	uint32_t PF_reg;
} PowerSensStruct;
#endif /* INC_DATA_TYPES_H_ */
