/*
 * mqqt_gen_strings.h
 *
 *  Created on: 26 ���. 2022 �.
 *      Author: kir
 */

#ifndef USERLIB_INC_MQTT_GEN_STRINGS_H_
#define USERLIB_INC_MQTT_GEN_STRINGS_H_


#include <stdint.h>

#define dev_system						"zalupa"
#define dev_common_name					"ZalupaKonskaya"
#define dev_model_name					"PowerMeter3000"
#define dev_manufacturer_name			"Manufacturer"
#define dev_hw_ver						"hv0.1"
#define dev_sw_ver						"sw0.1"

#define dev_class_energy				"energy"
#define dev_class_energy_human			"Energy"
#define dev_class_energy_state			"\"state_class\": \"total_increasing\",\n"
#define dev_class_energy_unit_of_measurement	"Wh"

#define dev_class_voltage				"voltage"
#define dev_class_voltage_human			"Voltage"
#define dev_class_voltage_unit_of_measurement	"V"

#define dev_class_power					"power"
#define dev_class_power_human			"Power"
#define dev_class_power_unit_of_measurement	"W"

#define dev_class_power_factor			"power_factor"
#define dev_class_power_factor_human	"PF"
#define dev_class_power_factor_unit_of_measurement "%"

#define dev_class_current				"current"
#define dev_class_current_human			"Струм"
#define dev_class_current_unit_of_measurement	"A"

typedef enum{
	INPUT_TOPIK = 1,
	OUTPUT_TOPIK = 2,
	ENERGY_SENSOR_TOPIK = 3,
	POWER_SENSOR_TOPIK = 4,
	VOLTAGE_SENSOR_TOPIK = 5,
	POWER_FACTOR_SENSOR_TOPIK = 6,
	CURRENT_SENSOR_TOPIK = 7
}mqtt_topik_string_type;

typedef enum{
	INP_CONF_PAYLOAD = 1,
	OUT_CONF_PAYLOAD = 2,
	ENERGY_SENSOR_PAYLOAD = 3,
	POWER_SENSOR_PAYLOAD = 4,
	VOLTAGE_SENSOR_PAYLOAD = 5,
	POWER_FACTOR_SENSOR_PAYLOAD = 6,
	CURRENT_SENSOR_PAYLOAD = 7
}mqqt_conf_payload_string_type;

int set_device_id(unsigned char * dev_id);
int set_device_conf_ip(unsigned char * chr_ip);
int set_home_assistant_prefix(char * prefix_string, uint8_t prefix_len);
int get_config_topik_string (char * buff, uint8_t topik_type, uint8_t obj_number);
int get_config_payload_string( char * payload, uint8_t payload_type, uint8_t obj_number);
int convert_bint_to_JSON_statusIO(char * buff, uint8_t bin, char * on_mess, char * off_mess, char * key_name, uint8_t number_io);
int generate_comand_topik_for_subscrabe(char * buff, uint8_t obj_number);
int generate_status_topik(char * buff, mqtt_topik_string_type topik_type);
void generate_key_value_JSON(char * buf, char * key, float value);

#endif /* USERLIB_INC_MQTT_GEN_STRINGS_H_ */
