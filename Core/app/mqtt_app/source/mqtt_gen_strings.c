/*
 * mqtt_gen_strings.c
 *
 *  Created on: 26 ���. 2022 �.
 *      Author: kir
 */

#include "mqtt_gen_strings.h"
#include "definition.h"
#include "string.h"
#include "stdio.h"


#define key_value_float_JSON_template	"{\"%s\" : \"%.2f\"}"

#define universal_config_topik_template	"%s/%s/%s_%s/%s/config"
#define universal_status_topik_template	"%s_%s/%s"
//#define component_sensor				"sensor"



//#define voltage 						"voltage"
//#define energy							"energy"
//#define power_factor					"pf"
//#define apparent_power					"ap"
//#define current							"current"



unsigned char home_assistant_prefix[] = {"homeassistant"};
unsigned char bin_sens[] =				{"binary_sensor"};
unsigned char device_name[] = 			{"biver_"};
unsigned char switch_sens[] = 			{"switch"};
unsigned char input[] = 				{"input"};
const unsigned char dev_hw_version[]=	{"0.1"};
const unsigned char dev_sw_version[]=	{"0.1"};



const unsigned char config_topik_temlate[] = {"%s/%s/biver_%s/%s%u/config"};

const unsigned char switch_conf_payload_templ[] = {  //todo change to const char
		"{\n"
			"\t\"device_class\":\"switch\",\n"
			"\t\"expire_after\" : 1800 ,\n"
			"\t\"state_topic\":\"biver_%s/switches\",\n"
			"\t\"command_topic\" : \"biver_%s/sw%u/set\",\n"
			"\t\"value_template\":\"{{ value_json.SW%u }}\",\n"
			"\t\"name\":\"Switch%u\",\n"
			"\t\"unique_id\":\"biver_%s_switch%u\",\n"
			"\t\"device\":{\n"
					"\t\t\"identifiers\":[\"biver_%s\"],\n"
					"\t\t\"name\":\"biver_%s\",\n"
					"\t\t\"model\":\"unit sensors 3i 3o\",\n"
					"\t\t\"manufacturer\":\"Shypachov\",\n"
					"\t\t\"hw_version\" : \"v0.1\",\n"
					"\t\t\"sw_version\" : \"2023-08-18\",\n"
					"\t\t\"configuration_url\" : \"http://%s\"\n"
					"\t}\n"
		"}"
											};

unsigned const char input_conf_payload_templ[] = {  //todo change to const char
		"{\n"
			"\t\"device_class\" :\"power\",\n"
			"\t\"expire_after\" : 1800 ,\n"
			"\t\"state_topic\" :\"biver_%s/inputs\",\n"
			"\t\"value_template\":\"{{ value_json.INP%u }}\",\n"
			"\t\"name\":\"Input%u\",\n"
			"\t\"unique_id\":\"biver_%s_input%u\",\n"
			"\t\"device\":{\n"
					"\t\t\"identifiers\":[\"biver_%s\"],\n"
					"\t\t\"name\":\"biver_%s\",\n"
					"\t\t\"model\":\"unit sensors 3i 3o\",\n"
					"\t\t\"manufacturer\":\"Shypachov\",\n"
					"\t\t\"hw_version\" : \"v0.1\",\n"
					"\t\t\"sw_version\" : \"2023-08-18\",\n"
					"\t\t\"configuration_url\" : \"http://%s\"\n"
					"\t}\n"
		"}"
											};

const unsigned char universal_conf_template[]={
		"{\n"
				"\t\"device_class\" :\"%s\",\n"
				"\t\"expire_after\" : 1800 ,\n"
				"\t\"state_topic\" :\"%s_%s/%s\",\n"
				"\t\"value_template\":\"{{ value_json.%s }}\",\n"
				"\t%s"
				"\t\"name\":\"%s\",\n"
				"\t\"unique_id\":\"%s_%s_%s\",\n"
				"\t\"unit_of_measurement\": \"%s\",\n"
				"\t\"device\":{\n"
						"\t\t\"identifiers\":[\"%s_%s\"],\n"
						"\t\t\"name\":\"%s\",\n"
						"\t\t\"model\":\"%s\",\n"
						"\t\t\"manufacturer\":\"%s\",\n"
						"\t\t\"hw_version\" : \"%s\",\n"
						"\t\t\"sw_version\" : \"%s\",\n"
						"\t\t\"configuration_url\" : \"http://%s\"\n"
						"\t}\n"
		"}"
};

const unsigned char status_topik_temlate[]	= {"%s_%s/%s"};
char subscr_topik_template[] 	= {"%s_%s/sw%u/set"	};
char input_status_topik_temp[] 	= {"%s_%s/inputs"	};
char switch_status_topik_temp[] = {"%s_%s/switches"	};

unsigned char unical_id[DEV_UID_LEN] = {'\0'};
unsigned char dev_conf_ip[IP_v4_LEN] = {'\0'};

int set_device_id(unsigned char * dev_id){
	uint8_t cpy_len = 0;
	if (strlen(dev_id) >= DEV_UID_LEN ){
		cpy_len = DEV_UID_LEN;
	}else{
		cpy_len = strlen(dev_id);
	}
	strncpy(unical_id, dev_id, cpy_len);
	return 0;
}

int set_device_conf_ip(unsigned char * chr_ip){

	strcpy(dev_conf_ip, "\0");
	if(strlen(chr_ip) <= IP_v4_LEN){
		strncpy(dev_conf_ip, chr_ip, strlen(chr_ip));
		return 0;
	}
	return -1;
}

int set_home_assistant_prefix(char * prefix_string, uint8_t prefix_len){
//TODO validation need
 	strncpy(home_assistant_prefix, prefix_string, prefix_len);

	return 0;
}

int get_config_topik_string (char * buff, uint8_t topik_type, uint8_t obj_number){

	strcpy(buff, '\0');
	switch (topik_type) {
		case INPUT_TOPIK:
			sprintf(buff, config_topik_temlate, home_assistant_prefix, bin_sens, unical_id, input, obj_number);
			break;

		case OUTPUT_TOPIK:
			sprintf(buff, config_topik_temlate, home_assistant_prefix, switch_sens, unical_id, switch_sens, obj_number);
			break;

		case ENERGY_SENSOR_TOPIK:
			sprintf(buff, universal_config_topik_template, home_assistant_prefix, component_sensor, dev_system, unical_id, dev_class_energy);
			break;
		case VOLTAGE_SENSOR_TOPIK:
			sprintf(buff, universal_config_topik_template, home_assistant_prefix, component_sensor, dev_system, unical_id, dev_class_voltage);
			break;
		case POWER_SENSOR_TOPIK:
			sprintf(buff, universal_config_topik_template, home_assistant_prefix, component_sensor, dev_system, unical_id, dev_class_power);
			break;
		case APPARENT_POWER_SENSOR_TOPIK:
			sprintf(buff, universal_config_topik_template, home_assistant_prefix, component_sensor, dev_system, unical_id, dev_class_apparent_power);
			break;
		case POWER_FACTOR_SENSOR_TOPIK:
			sprintf(buff, universal_config_topik_template, home_assistant_prefix, component_sensor, dev_system, unical_id, dev_class_power_factor);
			break;
		case CURRENT_SENSOR_TOPIK:
			sprintf(buff, universal_config_topik_template, home_assistant_prefix, component_sensor, dev_system, unical_id, dev_class_current);
			break;
		default:
			return -1;
			break;
	}


	return 0;
}

int get_config_payload_string( char * payload, uint8_t payload_type, uint8_t obj_number){

	uint8_t len = 0;
	strcpy(payload, "\0");

	switch (payload_type) {
		case OUT_CONF_PAYLOAD:
			len = sprintf(payload, switch_conf_payload_templ, unical_id, unical_id, obj_number, obj_number, obj_number, unical_id, obj_number, unical_id, unical_id, dev_conf_ip);
			return len;
			break;

		case INP_CONF_PAYLOAD:
			len = sprintf(payload, input_conf_payload_templ, unical_id, obj_number, obj_number,  unical_id, obj_number, unical_id, unical_id, dev_conf_ip);
			return len;
			break;
		case ENERGY_SENSOR_PAYLOAD:
			len = sprintf(payload, universal_conf_template, dev_class_energy, dev_system, \
					unical_id, state_topik, dev_class_energy, dev_class_energy_state, dev_class_energy_human, dev_system, unical_id, \
					dev_class_energy, dev_class_energy_unit_of_measurement, dev_system, unical_id, dev_common_name, dev_model_name,\
					dev_manufacturer_name, dev_hw_ver, dev_sw_ver, dev_conf_ip);
			break;
		case VOLTAGE_SENSOR_PAYLOAD:
			len = sprintf(payload, universal_conf_template, dev_class_voltage, dev_system, \
					unical_id, state_topik, dev_class_voltage, "\n", dev_class_voltage_human, dev_system, unical_id, \
					dev_class_voltage, dev_class_voltage_unit_of_measurement, dev_system, unical_id, dev_common_name, dev_model_name,\
					dev_manufacturer_name, dev_hw_ver, dev_sw_ver, dev_conf_ip);
			break;
		case POWER_SENSOR_PAYLOAD:
			len = sprintf(payload, universal_conf_template, dev_class_power, dev_system, \
					unical_id, state_topik, dev_class_power, "\n", dev_class_power_human, dev_system, unical_id, \
					dev_class_power, dev_class_power_unit_of_measurement, dev_system, unical_id, dev_common_name, dev_model_name,\
					dev_manufacturer_name, dev_hw_ver, dev_sw_ver, dev_conf_ip);
			break;
		case APPARENT_POWER_SENSOR_PAYLOAD:
			len = sprintf(payload, universal_conf_template, dev_class_apparent_power, dev_system, \
					unical_id, state_topik, dev_class_apparent_power, "\n", dev_class_apparent_power_human, dev_system, unical_id, \
					dev_class_apparent_power, dev_class_apparent_power_unit_of_measurement, dev_system, unical_id, dev_common_name, dev_model_name,\
					dev_manufacturer_name, dev_hw_ver, dev_sw_ver, dev_conf_ip);
			break;

		case POWER_FACTOR_SENSOR_PAYLOAD:
			len = sprintf(payload, universal_conf_template, dev_class_power_factor, dev_system, \
					unical_id, state_topik, dev_class_power_factor, "\n", dev_class_power_factor_human, dev_system, unical_id, \
					dev_class_power_factor, dev_class_power_factor_unit_of_measurement, dev_system, unical_id, dev_common_name, dev_model_name,\
					dev_manufacturer_name, dev_hw_ver, dev_sw_ver, dev_conf_ip);
			break;
		case CURRENT_SENSOR_PAYLOAD:
			len = sprintf(payload, universal_conf_template, dev_class_current, dev_system, \
					unical_id, state_topik, dev_class_current, "\n", dev_class_current_human, dev_system, unical_id, \
					dev_class_current, dev_class_current_unit_of_measurement, dev_system, unical_id, dev_common_name, dev_model_name,\
					dev_manufacturer_name, dev_hw_ver, dev_sw_ver, dev_conf_ip);
			break;

		default:
			return -1;
			break;
	}
}

int convert_bint_to_JSON_statusIO(char * buff, uint8_t bin, char * on_mess, char * off_mess, char * key_name, uint8_t number_io){

	unsigned char template[] = {"\t\"%s%u\" : \"%s\""};
	uint8_t test;
	unsigned char internal_buff[30];

	strcpy(buff, "\0");
	strcat(buff, "{\n");
	while (number_io > 0){
		test = bin & 0b00000001 << number_io - 1;
		if (test){
			sprintf(internal_buff, template, key_name, number_io, on_mess);
		}else{
			sprintf(internal_buff, template, key_name, number_io, off_mess);
		}
		strcat(buff, internal_buff);

		number_io --;

		if (number_io) {
			strcat(buff, ",\n");
		}
	}

	strcat(buff, "\n}");

	return 0;
}

int generate_comand_topik_for_subscrabe(char * buff, uint8_t obj_number){

	strcpy(buff, "\0");
	sprintf(buff, subscr_topik_template, unical_id, obj_number);
	return 0;
}

int generate_status_topik(char * buff, mqtt_topik_string_type topik_type){

	strcpy(buff, "\0");

	sprintf(buff, universal_status_topik_template, dev_system, unical_id, state_topik);

	switch (topik_type) {
		case INPUT_TOPIK:
			sprintf(buff, input_status_topik_temp, unical_id);
			break;

		case OUTPUT_TOPIK:
			sprintf(buff, switch_status_topik_temp, unical_id);
			break;

		default:
			return -1;
			break;
	}

	return 0;
}

void generate_key_value_JSON(char * buf, char * key, float value){

	sprintf(buf, key_value_float_JSON_template, key, value);
}
