/*
 * mqtt_app.h
 *
 *  Created on: 27 апр. 2023 г.
 *      Author: kir
 */

#ifndef APP_FILES_MQTT_APP_INCLUDE_MQTT_APP_H_
#define APP_FILES_MQTT_APP_INCLUDE_MQTT_APP_H_

#include "FreeRTOSConfig.h"
#include "FreeRTOS.h"
#include "queue.h"
#include "MQTTClient.h"
#include "data_types.h"

void init_mqtt_call_mutex(void (* set_mut), void (* rel_mut));
void init_mqtt_call_rw_coils(void (* call_read_coils), void (* call_write_coils));
void mqtt_IO_coil_q_init(xQueueHandle qRead, xQueueHandle qWrite);
void mqtt_message_resieve(MessageData* data);
int  mqtt_client_init(Ethernet_info_struct* eth_data, MQTT_cred_struct * mqtt_data, char * send_buf, \
		uint16_t send_buf_suze, char * receive_buf, uint16_t receive_buf_len);
int16_t mqtt_client_connect(void);
int8_t mqtt_client_reg_dev_on_home_assist(void);
int8_t mqtt_subscrabe_on_topik(void);
int8_t send_data_to_topik(const char* topik, char* payload);
int8_t mqtt_handler(void);
void mqtt_1ms_tik(void);

#endif /* APP_FILES_MQTT_APP_INCLUDE_MQTT_APP_H_ */
