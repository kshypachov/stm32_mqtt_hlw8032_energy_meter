/*
 * dns_service.c
 *
 *  Created on: 29 дек. 2023 г.
 *      Author: kirill
 */

#include "dns_service.h"
#include "definition.h"
#include "dns.h"
#include "string.h"


void Prototype(void){};

void (* DNSMutexGet)		(void) = Prototype;
void (* DNSMutexRelease)	(void) = Prototype;
int (* NetworkReady)		(void) = Prototype;

uint8_t  dns_server_ip[4];

//NetworkReady = *Prototype;

void dns_service_reg_cb_mutex(void (*get_mutex)(void), void (*release_mutex)(void)){

	if (get_mutex) DNSMutexGet = get_mutex;
	if (release_mutex) DNSMutexRelease = release_mutex;

}

void dns_service_reg_cb_net_ready(void (*func)){

	if ( func ) NetworkReady = func;

}

int dns_service_init(uint8_t socket, uint8_t * buf, uint16_t buf_len){

	if (buf_len < MAX_DNS_BUF_SIZE) return -1;
	// if buff  less then MAX_DNS_BUF_SIZE return error;
	DNS_init(socket, buf);
	return 0;
}

void dns_service_set_dns_ip(uint8_t * ip_addr){
	memcpy(dns_server_ip, ip_addr, sizeof(dns_server_ip));
}

int8_t dns_service_resolve_name(const char * domain_name, uint8_t * resolved_ip){
#ifdef DNS_USE_MUTEX
	DNSMutexGet();
#endif
	int8_t err;
	if (NetworkReady){
		err = DNS_run(dns_server_ip, domain_name, resolved_ip);
	}else{
		err = -1;
	}


#ifdef DNS_USE_MUTEX
	DNSMutexRelease();
#endif
	return err;
}

void dns_service_increment_second(void){
	DNS_time_handler();
}

int validate_number(char *str) {
    while (*str) {
        if(!isdigit(*str)){ //if the character is not a number, return false
            return 0;
        }
        str++; //point to next character
    }
    return 1;
}

bool isValidIPv4(const char* ipAddress) {
    if (ipAddress == NULL) {
        return false;
    }

    int num = 0;    // Current segment value
    int count = 0;  // Count of segments in the IP address
    int segmentLength = 0;

    for (size_t i = 0; ipAddress[i] != '\0'; ++i) {
        if (isdigit((unsigned char)ipAddress[i])) {
            num = num * 10 + (ipAddress[i] - '0');

            // Check if the segment value is in the valid range
            if (num < 0 || num > 255) {
                return false;
            }

            segmentLength++;
        } else if (ipAddress[i] == '.') {
            // Check if the segment has leading zeros
            if (segmentLength > 1 && ipAddress[i - segmentLength] == '0') {
                return false;
            }

            // Move to the next segment
            num = 0;
            count++;
            segmentLength = 0;

            // Check if there are more than 4 segments
            if (count > 3) {
                return false;
            }
        } else {
            // Invalid character in the IP address
            return false;
        }
    }

    // Check if the last segment has leading zeros
    if (segmentLength > 1 && ipAddress[strlen(ipAddress) - segmentLength] == '0') {
        return false;
    }

    // Check if there are exactly 4 segments in the IP address
    return count == 3;
}

/*
uint8_t isValidIP(const char * ip){

	regex_t regex;
	int check = regcomp(&regex,
	                      "^([0-9]|[1-9][0-9]|1([0-9][0-9])|2([0-4][0-9]|5[0-5]))."
	                      "([0-9]|[1-9][0-9]|1([0-9][0-9])|2([0-4][0-9]|5[0-5]))."
	                      "([0-9]|[1-9][0-9]|1([0-9][0-9])|2([0-4][0-9]|5[0-5]))."
	                      "([0-9]|[1-9][0-9]|1([0-9][0-9])|2([0-4][0-9]|5[0-5]))$", REG_EXTENDED);
	int status = regexec(&regex, ip, (size_t) 0, NULL, 0);
	if (status !=0){
		return -1;
	}
	return 0;

}
*/
