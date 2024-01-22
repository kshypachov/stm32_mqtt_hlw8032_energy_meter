/*
 * mqtt_app.c
 *
 *  Created on: 27 ���. 2023 �.
 *      Author: kir
 */
#include "mqtt_app.h"

#include "httpParser.h"
#include "stdio.h"
#include "string.h"
#include "definition.h"
#include "mqtt_gen_strings.h"
#include "socket.h"

#include "dns_service.h"
#include "stdbool.h"
#include "definition.h"


#define SUBSCR_TOPIK_BUF_LEN		64
#define COMMAND_TIMEOUT_MS			1000
#define TOPIK_MAX_LEN				128
#define	SEND_PAYLOD_LEN				600


#ifndef MQTT_CLIENT_SOCKET
	#error "please define MQTT_CLIENT_SOCKET - number  "
#endif

/*-------------------local_var------------------*/
xQueueHandle 			coil_q_read, coil_q_write;
MQTT_cred_struct * 		MQTT_credentials;
Ethernet_info_struct*	EthernetInfo;
unsigned char 			MAC_ADDR_CHR[14];
unsigned char			IP_ADDR_CHR[IP_v4_LEN];
unsigned char *			mqtt_recv_buf;
unsigned char *			mqtt_send_buf;
char 					buf_topik[TOPIK_MAX_LEN];
char		 			buf_payload[SEND_PAYLOD_LEN];
uint16_t				mqtt_recv_buf_len;
uint16_t				mqtt_send_buf_len;
MQTTPacket_connectData 	mqtt_packet_data = MQTTPacket_connectData_initializer;
uint8_t					mqtt_server_ip[4];
uint16_t				mqtt_server_port;
Network 				MQTT_network;
MQTTClient 				MQTT_Client;
MQTTMessage 			mqtt_message;


//need optimaze
char		 			sub_topik_template[] = "biver_%s/+/set";
char					sub_topik[SUBSCR_TOPIK_BUF_LEN];

void func_prototype(void){};

void (* set_mutex)(void) 		= &func_prototype;
void (* release_mutex)(void) 	= &func_prototype;
uint8_t (* read_coils)(void)	= &func_prototype;
void (* write_coils)(uint8_t)	= &func_prototype;

void init_mqtt_call_mutex(void (* set_mut), void (* rel_mut)){

	if(set_mut) set_mutex 		= set_mut;
	if(rel_mut) release_mutex 	= rel_mut;
}

void init_mqtt_call_rw_coils(void (* call_read_coils), void (* call_write_coils)){

	if (call_read_coils) read_coils 	= call_read_coils;
	if (call_write_coils) write_coils	= call_write_coils;

}

void mqtt_IO_coil_q_init(xQueueHandle qRead, xQueueHandle qWrite){

	coil_q_read		= qRead;
	coil_q_write	= qWrite;
}



int mqtt_client_init(Ethernet_info_struct* eth_data, MQTT_cred_struct * mqtt_data, char * send_buf, \
		uint16_t send_buf_suze, char * receive_buf, uint16_t receive_buf_len){

	EthernetInfo 		= eth_data;
	MQTT_credentials	= mqtt_data;
	mqtt_send_buf		= send_buf;
	mqtt_recv_buf		= receive_buf;
	mqtt_send_buf_len	= send_buf_suze;
	mqtt_recv_buf_len	= receive_buf_len;

	sprintf(MAC_ADDR_CHR,"%02X%02X%02X%02X%02X%02X", EthernetInfo->mac[0],EthernetInfo->mac[1],EthernetInfo->mac[2],EthernetInfo->mac[3],EthernetInfo->mac[4],EthernetInfo->mac[5]);
	set_device_id(&MAC_ADDR_CHR);
	sprintf(IP_ADDR_CHR, "%u.%u.%u.%u", EthernetInfo->ip[0], EthernetInfo->ip[1], EthernetInfo->ip[2], EthernetInfo->ip[3]);
	set_device_conf_ip(&IP_ADDR_CHR);

	//strncpy(mqtt_send_buf, MQTT_credentials->uri, MAX_DOMAIN_NAME);
	if ( isValidIPv4(MQTT_credentials->uri)){
		sscanf(MQTT_credentials->uri, "%d.%d.%d.%d", &mqtt_server_ip[0], &mqtt_server_ip[1], &mqtt_server_ip[2], &mqtt_server_ip[3]);
	}else if(dns_service_resolve_name(MQTT_credentials->uri, &mqtt_server_ip)== -1){
		return -1; // DNS resolve error;
	}

	mqtt_packet_data.willFlag			= 0;
	mqtt_packet_data.MQTTVersion		= 3;
	mqtt_packet_data.clientID.cstring	= &MAC_ADDR_CHR;
	mqtt_packet_data.keepAliveInterval	= 5000;
	mqtt_packet_data.cleansession		= 1;
	mqtt_packet_data.username.cstring 	= &MQTT_credentials->login;
	mqtt_packet_data.password.cstring 	= &MQTT_credentials->pass;
//	mqtt_server_ip						= MQTT_credentials->ip;
	mqtt_server_port					= (uint16_t) MQTT_credentials->port;

	mqtt_message.id						= 0;
	mqtt_message.qos					= QOS0;
	mqtt_message.dup					= 0;
	mqtt_message.retained				= 0;

	NewNetwork(&MQTT_network, MQTT_CLIENT_SOCKET);
	MQTTClientInit(&MQTT_Client, &MQTT_network, COMMAND_TIMEOUT_MS, mqtt_send_buf, mqtt_send_buf_len, mqtt_recv_buf, mqtt_recv_buf_len);

	return 0;
}


int16_t mqtt_client_connect(void){

	int16_t result;

	set_mutex();
	result = ConnectNetwork(&MQTT_network, mqtt_server_ip, mqtt_server_port);
	release_mutex();
	if (result != 1) {
		set_mutex();
		//disconnect(MQTT_network.my_socket);
		close(MQTT_network.my_socket);
		release_mutex();
		return result - 10;    // 1 means SOCK_OK;
	}
	set_mutex();
	result = MQTTConnect(&MQTT_Client, &mqtt_packet_data);
	release_mutex();
	if (result != SUCCESSS) return result - 20;
	return result; // if returned value < 0 then means error
}

int8_t mqtt_client_reg_dev_on_home_assist(void){

	uint8_t i;
	int8_t result;
//------------------------------REG ENERGY SENSOR-------------------------------
		memset(buf_topik, 0, TOPIK_MAX_LEN);
		get_config_topik_string(buf_topik, ENERGY_SENSOR_TOPIK, 0);
		get_config_payload_string(buf_payload, ENERGY_SENSOR_PAYLOAD, 0);
		mqtt_message.payloadlen = strlen(buf_payload);
		mqtt_message.payload = buf_payload;
		set_mutex();
		result = MQTTPublish(&MQTT_Client, &buf_topik , &mqtt_message);
		release_mutex();
		if (result != SUCCESSS) return result;
		mqtt_message.id++;
//------------------------------REG ENERGY SENSOR-------------------------------
//------------------------------REG VOLTAGE SENSOR-------------------------------
		memset(buf_topik, 0, TOPIK_MAX_LEN);
		get_config_topik_string(buf_topik, VOLTAGE_SENSOR_TOPIK, 0);
		get_config_payload_string(buf_payload, VOLTAGE_SENSOR_PAYLOAD, 0);
		mqtt_message.payloadlen = strlen(buf_payload);
		mqtt_message.payload = buf_payload;
		set_mutex();
		result = MQTTPublish(&MQTT_Client, &buf_topik , &mqtt_message);
		release_mutex();
		if (result != SUCCESSS) return result;
		mqtt_message.id++;
//------------------------------REG VOLTAGE SENSOR-------------------------------
//------------------------------REG POWER SENSOR-------------------------------
		memset(buf_topik, 0, TOPIK_MAX_LEN);
		get_config_topik_string(buf_topik, POWER_SENSOR_TOPIK, 0);
		get_config_payload_string(buf_payload, POWER_SENSOR_PAYLOAD, 0);
		mqtt_message.payloadlen = strlen(buf_payload);
		mqtt_message.payload = buf_payload;
		set_mutex();
		result = MQTTPublish(&MQTT_Client, &buf_topik , &mqtt_message);
		release_mutex();
		if (result != SUCCESSS) return result;
		mqtt_message.id++;

//------------------------------REG POWER SENSOR-------------------------------
//------------------------------REG POWER FACTOR SENSOR-------------------------------
		memset(buf_topik, 0, TOPIK_MAX_LEN);
		get_config_topik_string(buf_topik, POWER_FACTOR_SENSOR_TOPIK, 0);
		get_config_payload_string(buf_payload, POWER_FACTOR_SENSOR_PAYLOAD, 0);
		mqtt_message.payloadlen = strlen(buf_payload);
		mqtt_message.payload = buf_payload;
		set_mutex();
		result = MQTTPublish(&MQTT_Client, &buf_topik , &mqtt_message);
		release_mutex();
		if (result != SUCCESSS) return result;
		mqtt_message.id++;

//------------------------------REG POWER FACTOR SENSOR-------------------------------
//------------------------------REG CURRENT SENSOR-------------------------------
		memset(buf_topik, 0, TOPIK_MAX_LEN);
		get_config_topik_string(buf_topik, CURRENT_SENSOR_TOPIK, 0);
		get_config_payload_string(buf_payload, CURRENT_SENSOR_PAYLOAD, 0);
		mqtt_message.payloadlen = strlen(buf_payload);
		mqtt_message.payload = buf_payload;
		set_mutex();
		result = MQTTPublish(&MQTT_Client, &buf_topik , &mqtt_message);
		release_mutex();
		if (result != SUCCESSS) return result;
		mqtt_message.id++;

//------------------------------REG CURRENT SENSOR-------------------------------
		return 0;
		/*
	//-------------------Register Inputs on Home assistant---------------------------
	for(i = 1; i <= NUMBER_INPUT_TOPIKS; i++){ //config input topiks
		memset(buf_topik, 0, TOPIK_MAX_LEN);
		get_config_topik_string(buf_topik, INPUT_TOPIK, i);
		get_config_payload_string(buf_payload, INP_CONF_PAYLOAD, i);
		mqtt_message.payloadlen = strlen(buf_payload);
		mqtt_message.payload = buf_payload;
		set_mutex();
		result = MQTTPublish(&MQTT_Client, &buf_topik , &mqtt_message);
		release_mutex();
		if (result != SUCCESSS) return result;
		mqtt_message.id++;
	}
	//-------------------Register Outputs(Coils) on Home assistant---------------------------
	//Generate and send registration device info to home assistant (Coils)
	for(i = 1; i <= NUMBER_SWITCH_TOPIKS; i++){ // config outputs topiks
		memset(buf_topik, 0, TOPIK_MAX_LEN);
		get_config_topik_string(buf_topik, OUTPUT_TOPIK, i);
		get_config_payload_string(buf_payload, OUT_CONF_PAYLOAD, i);
		mqtt_message.payloadlen = strlen(buf_payload);
		mqtt_message.payload = buf_payload;
		set_mutex();
		result = MQTTPublish(&MQTT_Client, buf_topik , &mqtt_message);
		release_mutex();
		if (result != SUCCESSS) return result;
		mqtt_message.id++;
	}
	return result;// if all Ok, return SUCCESSS. SUCCESSS = 0;
	*/
}

int8_t mqtt_subscrabe_on_topik(void){
	int8_t result;

	sprintf(&sub_topik, sub_topik_template, MAC_ADDR_CHR);
	set_mutex();
	result = MQTTSubscribe(&MQTT_Client, sub_topik, QOS1, mqtt_message_resieve);
	release_mutex();
	return result;  // if all Ok, return SUCCESSS. SUCCESSS = 0;
}

int8_t send_data_to_topik(const char* topik, char* payload){
	int8_t result;

	mqtt_message.payloadlen = strlen(payload);
	mqtt_message.payload	= payload;
	mqtt_message.id++;
	set_mutex();
	result = MQTTPublish(&MQTT_Client, topik , &mqtt_message);
	release_mutex();
	return result; // if all Ok, return SUCCESSS. SUCCESSS = 0;
}

int8_t mqtt_handler(void){
	int8_t result;

	set_mutex();
	result = MQTTYield(&MQTT_Client, mqtt_packet_data.keepAliveInterval);
	release_mutex();

	return result;
}

void mqtt_1ms_tik(void){
	MilliTimer_Handler();
}

void mqtt_message_resieve(MessageData* data){
	char 	tmp_buf_payload[SUBSCR_TOPIK_BUF_LEN];
	char 	tmp_buf_topik[SUBSCR_TOPIK_BUF_LEN];
	char *	token;
	uint8_t sw_addr;
	uint8_t	CoilStatus_new;

	memset(tmp_buf_payload, 0, SUBSCR_TOPIK_BUF_LEN);
	memset(tmp_buf_topik, 0, SUBSCR_TOPIK_BUF_LEN);

	MQTTMessage* message	= data->message;
	MQTTString*  topik		= data->topicName;

	strncpy(tmp_buf_payload, (char*)message->payload, (int)message->payloadlen);
	strncpy(tmp_buf_topik, (char*)topik->lenstring.data, (int)topik->lenstring.len);
	if (strstr(tmp_buf_topik, "sw")){
		//xQueuePeek(coil_q_read ,&CoilStatus_new,0);
		CoilStatus_new 	= read_coils();
		token 			= strstr(tmp_buf_topik, "sw");
		token 			+= strlen("sw");
		token 			= strtok(token, "/");
		sw_addr 		= ATOI(token, 10);
		sw_addr 		-= 1;
		if (strstr(tmp_buf_payload, "ON")){
			xMBUtilSetBits( &CoilStatus_new, sw_addr, 1, 1 );
		}
		if (strstr(tmp_buf_payload, "OFF")){
			xMBUtilSetBits( &CoilStatus_new, sw_addr, 1, 0 );
		}
		//xQueueOverwrite(coil_q_write, (void *)&CoilStatus_new);
		write_coils(CoilStatus_new);
	}
}




