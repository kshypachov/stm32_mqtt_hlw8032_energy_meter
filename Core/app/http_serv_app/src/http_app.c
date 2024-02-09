/*
 * http_app.c
 *
 *  Created on: 19 ����. 2023 �.
 *      Author: kir
 */
#include "http_app.h"
#include "data_types.h"
#include <stdio.h>
#include "base64.h"
#include "definition.h"
#include "stddef.h"
#include "spi_fs.h"
#include "cmsis_os.h"
#include "md_internal.h"
#include "mbedtls/md5.h"
#include "md5.h"





xQueueHandle MQTT_Q;
xQueueHandle HomeAsistant_Q;
xQueueHandle ModbusTCP_Q;
xQueueHandle Power_Data_Q;
xQueueHandle PowerSensSettings_Q;
xQueueHandle Uptime_Q;

float float_temp;

int			part = 0;
uint32_t	part_offset = 0;

int CharToDec(char c){
    if(c>='0' && c<='9') return c-'0';
    if(c>='a' && c<='f') return c-'a'+10;
    if(c>='A' && c<='F') return c-'A'+10;
    return 0;
}

void http_parse_params_init (xQueueHandle xQueue, uint8_t parameters_type){

	if (parameters_type == MQTT){
		if (xQueue){
			MQTT_Q = xQueue;
		}
	}else if (parameters_type == HA){
		if (xQueue){
			HomeAsistant_Q = xQueue;
		}
	}else if (parameters_type == ModBusTCP){
		if (xQueue){
			ModbusTCP_Q = xQueue;
		}
	}else if (parameters_type == PowrData){
		if (xQueue){
			Power_Data_Q = xQueue;
		}
	}else if (parameters_type == PowrSensSett){
		if (xQueue){
			PowerSensSettings_Q = xQueue;
		}
	}else if (parameters_type == Uptime){
		if (xQueue){
			Uptime_Q = xQueue;
		}
	}
}

void param_from_http_to_Q(char * http_resp, const uint8_t parameters_type){

	MQTT_cred_struct	MQTT_params;
	Home_assist_struct	HA_params;
	ModBusTCP_struct	ModBusTCP_parameters;				// MobBusTCP settins
	uint8_t				ip_addr[4];
	uint16_t			port;
	float				shunt_value;
	P_sens_sett_struct	PowShunSett;

	uint8_t * buf;

	switch (parameters_type) {

		case MQTT:

			memset(&MQTT_params, 0, sizeof(MQTT_params));

			if (strstr(get_http_param_value( http_resp, "mqtt"), "1")){
				MQTT_params.enable = 1;
			}else if (strstr(get_http_param_value( http_resp, "mqtt"), "0")) {
				MQTT_params.enable = 0;
			}

			buf = (uint8_t *) get_http_param_value( http_resp, "login");
			if (buf || (strlen(buf) < sizeof(MQTT_params.login) / sizeof(char)) ){
				strcpy(MQTT_params.login, buf);
				//TODO change to strncpy
			}

			buf = (uint8_t *) get_http_param_value( http_resp, "password");
			if (buf || (strlen(buf) < sizeof(MQTT_params.pass) / sizeof(char)) ){
				strcpy(MQTT_params.pass, buf);
				//TODO change to strncpy
			}

			buf = (uint8_t *) get_http_param_value( http_resp, "uri");
			if (buf || (strlen(buf) <= MAX_DOMAIN_NAME -1 ) ) {						 // 15 ��������, ������������ ����� IPv4
				//sscanf(buf, "%d.%d.%d.%d", &ip_addr[0], &ip_addr[1], &ip_addr[2], &ip_addr[3]);
				strncpy(MQTT_params.uri, buf, MAX_DOMAIN_NAME - 1);
			}

			buf = (uint8_t *) get_http_param_value( http_resp, "port");
			if (buf || (strlen(buf) <= 5) ) {						// 5 ��������, ������������ ����� ������ �����
				sscanf(buf, "%d", &port);
				if ((port > 0) && (port < 65535)){
					MQTT_params.port = port;
				}
			}

			MQTT_params.save = 1;

			xQueueOverwrite(MQTT_Q, (void *)&MQTT_params);

			break;

		case ModBusTCP:
			memset(&ModBusTCP_parameters, 0, sizeof(ModBusTCP_parameters));
			if (strstr(get_http_param_value( http_resp, "mb_tcp"), "1")){
				ModBusTCP_parameters.enable = 1;
			}else if (strstr(get_http_param_value( http_resp, "mb_tcp"), "0")) {
				ModBusTCP_parameters.enable = 0;
			}
			ModBusTCP_parameters.save = 1;

			xQueueOverwrite(ModbusTCP_Q, (void *)&ModBusTCP_parameters);
			break;

		case HA:

			break;
//TODO hui pizda zalupa
		case PowrSensSett:
			buf = (uint8_t *) get_http_param_value( http_resp, "shunt");
			if (buf ) {						// 5 ��������, ������������ ����� ������ �����
				sscanf(buf, "%f", &float_temp);							//TODO add validation
				if (float_temp > 0){									//validate value
					PowShunSett.resistance = float_temp;
					PowShunSett.save = 1;
					xQueueOverwrite(PowerSensSettings_Q, (void *)&PowShunSett);
				}
			}
			break;
		default:
			break;
	}
}

void param_from_Q_to_JSON(char * buf, const uint8_t parameters_type, uint16_t * len){

	MQTT_cred_struct	MQTT_params;
	PowerSensStruct		PowerParm;
	P_sens_sett_struct	PowShunSett;

	unsigned const char template_mqtt_data[] 	= {"{\"login\": \"%s\", \"pass\": \"********\", \"addr\": \"%s\", \"port\": \"%u\", \"enabled\": \"%u\"}"};//{"login": "admin", "pass": "1234", "addr": "10.0.2.20", "port": "1883", "enabled": 1 }
	unsigned const char template_power_data[] 	= {"{\"voltage\": \"%.2f\", \"current\": \"%.2f\", \"active_power_w\": \"%.2f\", \"apparent_power_w\": \"%.2f\", \"power_factor\": \"%.2f\", \"W_h\": \"%.2f\"}"};//{"voltage": "233.2", "current": "0.56", "active_power_w": "33.4", "apparent_power_w": "65.2", "power_factor": "0.5", "KW/h": "0.5634"}
	unsigned const char template_shunt_sett[]   = {"{\"shunt\": \"%.4f\"}"};

	switch (parameters_type) {

		case MQTT:
			xQueuePeek(MQTT_Q ,&MQTT_params,0);
			sprintf(buf, (const char *)template_mqtt_data, MQTT_params.login, MQTT_params.uri, MQTT_params.port, MQTT_params.enable);
			*len = strlen(buf);

			break;
		case PowrData:
			xQueuePeek(Power_Data_Q ,&PowerParm,0);
			sprintf(buf, (const char *)template_power_data, PowerParm.Voltage, PowerParm.Current, PowerParm.ActivPower, PowerParm.ApparPower, PowerParm.PowerFactor, PowerParm.KWatt_h);
			*len = strlen(buf);
			break;
		case PowrSensSett:
			xQueuePeek(PowerSensSettings_Q ,&PowShunSett,0);
			sprintf(buf, (const char *)template_shunt_sett, PowShunSett.resistance);
			*len = strlen(buf);
			break;
		default:
			break;
	}
}

int write_to_file(char * buf, uint16_t * len, char * response, char * base_path){
	char 		tmp_data_buf[TMP_BUFF_FOR_FILE_RECV];
	char 		filename[MAX_CONTENT_NAME_LEN];
	char * 		param_value;
	char *		parsed_digest;
	char *		step_number;
	int32_t 	recv_len;
	size_t 		parsed_len;
	size_t *	p_len;
	int32_t		err;
	uint32_t	number;
	unsigned char output[17];
	unsigned char recv_digest_bin[17];
	int i, t ,t2 ,r;

	p_len = &parsed_len;

	param_value = get_http_param_value((char *)buf, "filename");
	if (param_value){
		strcpy(filename, base_path);
		strncat(filename, param_value, MAX_CONTENT_NAME_LEN-5);
	}else{
		strncpy(response, "error", strlen("error")+1);
		*len = strlen("error");
		return;
	}

	//step_number = get_http_param_value((char *)buf, "step");

	param_value = get_http_param_value((char *)buf, "data");

	if (strlen(param_value) >=  TMP_BUFF_FOR_FILE_RECV){ //check if resieved data in parameter "data" not bigger then buffer

	}else if (param_value){								//check if resieved data len > 0
		recv_len = strlen(param_value);
//		replacetochar(param_value, ' ', '+');
		err = mbedtls_base64_decode((unsigned char *)tmp_data_buf, TMP_BUFF_FOR_FILE_RECV, p_len, (const unsigned char *)param_value, recv_len);

		parsed_digest = get_http_param_value((char *)buf, "digest");

	    for (i = 0; i< 32 ; i+=2){
	        t = CharToDec(parsed_digest[i]);
	        t2 = CharToDec(parsed_digest[i+1]);
	        recv_digest_bin[i/2] = t << 4 | t2;
	    }
	    recv_digest_bin[16] = '\0';


		mbedtls_md5_context md5_ctx;

		mbedtls_md5_init(&md5_ctx);
		mbedtls_md5_starts_ret(&md5_ctx);
		mbedtls_md5_update_ret(&md5_ctx, tmp_data_buf, *p_len);
		mbedtls_md5_finish_ret(&md5_ctx, output);
		mbedtls_md5_free(&md5_ctx);
		output[16] = '\0';



		if (strncmp(&recv_digest_bin, &output, 16)){
			err = -1;
			return err;
		}

		step_number = get_http_param_value((char *)buf, "step");
		number = ATOI(step_number, 10);

		if(number == 0){
			part =0;
			err = spi_fs_over_write_file(filename, tmp_data_buf, *p_len);
		}else{

			if(ATOI(step_number, 10)!= part){
				err = -1;
				return err;
			}

			err = spi_fs_write_file_to_end(filename, tmp_data_buf, *p_len);
		}

		part++;

		if (err < 0){
			err = 0;
		}

		//strncpy(tmp_data_buf, param_value, TMP_BUFF_FOR_FILE_RECV-1);
	}else{
		strncpy(response, "error", strlen("error")+1);
		*len = strlen("error");
		return;
	}
	strncpy(response, "ok", strlen("ok")+1);
	*len = strlen("ok");
}

int8_t read_all_parameters(uint8_t * buf, uint16_t * len){
	PowerSensStruct		PowerParm;
	P_sens_sett_struct	PowShunSett;
	MQTT_cred_struct	MQTT_params;
	ModBusTCP_struct	mb_tcp_params;
	uint32_t			uptime;

	unsigned const char template_data[] = {"{\"voltage\": \"%.2f\", \"current\": \"%.2f\", \"active_power_w\": \"%.2f\", \"apparent_power_w\": \"%.2f\", \"power_factor\": \"%.2f\", \"kWh\": \"%.2f\", \"shunt\": \"%.8f\", \"mb_tcp\": %u, \"mqtt\": %u, \"mqtt_login\": \"%s\", \"mqtt_port\": \"%u\", \"uri\": \"%s\", \"test_pulse\": \"%u\",  \"readed_pulse\": \"%u\", \"PF_reg\": \"%u\", \"uptime\": \"%u\"}"};

	xQueuePeek(Power_Data_Q,			(void *)&PowerParm,0);
	xQueuePeek(PowerSensSettings_Q ,	(void *)&PowShunSett,0);
	xQueuePeek(MQTT_Q ,					(void *)&MQTT_params,0);
	xQueuePeek(ModbusTCP_Q,				(void *)&mb_tcp_params, 0);
	xQueuePeek(Uptime_Q,				(void *)&uptime, 0);


	sprintf(buf, (const char *)template_data, PowerParm.Voltage, PowerParm.Current, PowerParm.ActivPower, PowerParm.ApparPower, PowerParm.PowerFactor, PowerParm.KWatt_h, PowShunSett.resistance, mb_tcp_params.enable, MQTT_params.enable, MQTT_params.login, MQTT_params.port, MQTT_params.uri, PowerParm.test_pulse_counter, PowerParm.readed_counter, PowerParm.PF_reg, uptime);
	*len = strlen(buf);

	return 0 ;
}

int calculate_md5_file(char * base_path, char * filename, char * buffer, uint16_t * len){
	unsigned char 			md5sum[17];
	mbedtls_md5_context 	md5_ctx;
	uint8_t 				read_buffer[TMP_BUF_FOR_MD5_CALC+1];
	uint32_t				offset = 0;
	uint16_t				readed_len;
	char 					path[64];

	mbedtls_md5_init(&md5_ctx);
	mbedtls_md5_starts_ret(&md5_ctx);

	strcpy(path, base_path);
	strncat(path, filename, 20);

	for (;;){
		memset(&read_buffer, 0, TMP_BUF_FOR_MD5_CALC+1);
		readed_len = spi_fs_read_file_offset(path, read_buffer, offset, TMP_BUF_FOR_MD5_CALC);
		if (readed_len < 0){
			mbedtls_md5_free(&md5_ctx);
			* len = 0;
			return -1;
		}else{
			if (readed_len == TMP_BUF_FOR_MD5_CALC){
				mbedtls_md5_update_ret(&md5_ctx, &read_buffer, readed_len);
				offset += readed_len;
			}else{
				mbedtls_md5_update_ret(&md5_ctx, &read_buffer, readed_len);
				mbedtls_md5_finish_ret(&md5_ctx, &md5sum);
				mbedtls_md5_free(&md5_ctx);
				md5sum[16] = '\0';
				break;
			}
		}
	}
	sprintf((char *)buffer,"%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X", md5sum[0], md5sum[1], md5sum[2], md5sum[3], md5sum[4], md5sum[5], md5sum[6], md5sum[7], md5sum[8], md5sum[9], md5sum[10], md5sum[11], md5sum[12], md5sum[13], md5sum[14], md5sum[15]);
	//strncpy(buffer, md5sum, 17);
	* len = 32;
	return 0;
}

int activate_firmware(char * buf, uint16_t * len){

	char old_path[60];
	int err;

	strcpy(old_path, FIRMWARE_FS_DIR);
	strncat(old_path, "file.bin" , 20);

	err = spi_fs_mv((const char *)old_path, FIRMWARE_FILE);

	if(err >= 0){
		strcpy(buf, "OK");
		* len = 2;
		return 1;
	}

 	return 0;
}

uint8_t http_post_cgi_processor(uint8_t * uri_name, uint8_t * uri, uint8_t * buf, uint16_t * len){

	uint8_t ret = HTTP_FAILED;
	len = 0;

	if(strcmp((const char *)uri_name, "settings_mqtt.cgi") == 0){
		param_from_http_to_Q((char *)uri, MQTT);
		ret = HTTP_OK;
	}else if (strcmp((const char *)uri_name, "mb_tcp_settings.cgi") == 0){
		param_from_http_to_Q((char *)uri, ModBusTCP);
		ret = HTTP_OK;
	}else if (strcmp((const char *)uri_name, "file_upload.cgi") == 0){
		if (write_to_file((char *)uri, len, (char *) buf, HTTP_FS_DIR) < 0 ){
			ret = HTTP_FAILED;
		}else{
			ret = HTTP_OK;
		}
	}else if (strcmp((const char *)uri_name, "settings_resistance.cgi") == 0){
		param_from_http_to_Q((char *)uri, PowrSensSett);
		ret = HTTP_OK;
	}else if (strcmp((const char *)uri_name, "firmware_upload.cgi") == 0){
		if (write_to_file((char *)uri, len, (char *) buf, FIRMWARE_FS_DIR) < 0 ){
			ret = HTTP_FAILED;
		}else{
			ret = HTTP_OK;
		}
	}

	return ret;
}

uint8_t http_get_cgi_processor(uint8_t * uri_name, uint8_t * buf, uint16_t * len){

	uint8_t ret = HTTP_FAILED;

	if(strcmp((const char *)uri_name, "settings_MQTT.cgi") == 0){
		param_from_Q_to_JSON((char *)buf, MQTT, len);
		ret = HTTP_OK;
	}else if(strcmp((const char *)uri_name, "test.cgi") == 0){
		strncpy((const char *)buf, "oK", strlen("oK"));
		ret = HTTP_OK;
		*len = strlen("oK");
	}else if(strcmp((const char *)uri_name, "power.cgi") == 0){
		param_from_Q_to_JSON((char *)buf, PowrData, len);
		ret = HTTP_OK;
	}else if(strcmp((const char *)uri_name, "get_shunt_sett.cgi") == 0){
		param_from_Q_to_JSON((char *)buf, PowrSensSett, len);
		ret = HTTP_OK;
	}else if(strcmp((const char *)uri_name, "get_all.cgi") == 0){
		read_all_parameters((char *)buf, len);
		ret = HTTP_OK;
	}else if(strcmp((const char *)uri_name, "get_firmware_md5.cgi") == 0){
		if (calculate_md5_file(FIRMWARE_FS_DIR, "file.bin", buf, len) == 0){
			ret = HTTP_OK;
		}else{
			* len = 0;
			ret = HTTP_FAILED;
		}
	}else if(strcmp((const char *)uri_name, "activate_firmware.cgi") == 0){
		ret = activate_firmware((char *)buf, len);
	}else if(strcmp((const char *)uri_name, "reset_energy.cgi") == 0){ ///---------------------------------------FOR DEBUG-------------------------------------
		spi_fs_remove(KW_COUNT_STOR_FILE);
		ret = HTTP_OK;
	}else if(strcmp((const char *)uri_name, "format_flash.cgi") == 0){ ///---------------------------------------FOR DEBUG-------------------------------------
		spi_fs_remove_recurcuve_in("/");
		ret = HTTP_OK;
	}

	return ret;
}
