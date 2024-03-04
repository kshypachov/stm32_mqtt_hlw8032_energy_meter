/*
 * broadcast_mess.c
 *
 *  Created on: Mar 4, 2024
 *      Author: kirill
 */


#include "broadcast_mess.h"
#include "string.h"
#include "definition.h"
//#include "data_types.h"


#define mess_template	"{device_name: \"%s\", model_name: \"%s\", mac: \"%02X%02X%02X%02X%02X%02X\", ip: \"%u.%u.%u.%u\", netmask: \"%u.%u.%u.%u\", gw: \"%u.%u.%u.%u\", dns: \"%u.%u.%u.%u\"}"

char					uid[DEV_UID_LEN];
Ethernet_info_struct	eth_info;

void set_broadcast_message_eth_info(Ethernet_info_struct * eth){

	memcpy(&eth_info, &eth, sizeof(Ethernet_info_struct));

}

int16_t get_broadcast_message_payload(char * buffer, uint16_t buff_len){

	uint16_t len;

	strcpy(buffer, "\0");
	len = sprintf(buffer, mess_template, dev_system, dev_model_name, eth_info.mac[0], eth_info.mac[1], eth_info.mac[2], eth_info.mac[3], eth_info.mac[4], \
			eth_info.mac[5], eth_info.ip[0], eth_info.ip[1], eth_info.ip[2], eth_info.ip[4], eth_info.sn[0], eth_info.sn[1], eth_info.sn[2], eth_info.sn[3], \
			eth_info.gw[0], eth_info.gw[1], eth_info.gw[2], eth_info.gw[3], eth_info.dns[0], eth_info.dns[1], eth_info.dns[2], eth_info.dns[3]);

	return len;
}
