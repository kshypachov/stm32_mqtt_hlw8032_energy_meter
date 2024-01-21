/*
 * dns_service.h
 *
 *  Created on: 29 ���. 2023 �.
 *      Author: kirill
 */

#ifndef HIGH_LEVEL_ABSTRACTIONS_DNS_ABSTRACTIONS_DNS_SERVICE_H_
#define HIGH_LEVEL_ABSTRACTIONS_DNS_ABSTRACTIONS_DNS_SERVICE_H_

#include "stdio.h"
#include "stdbool.h"
#include "stdint.h"

void dns_service_reg_cb_mutex(void (*get_mutex)(void), void (*release_mutex)(void));
void dns_service_reg_cb_net_ready(void (*func));
int dns_service_init(uint8_t socket, uint8_t * buf, uint16_t buf_len);
int8_t dns_service_resolve_name(const char * domain_name, uint8_t * resolved_ip);
void dns_service_set_dns_ip(uint8_t * ip_addr);
void dns_service_increment_second(void);
bool isValidIPv4(const char* ipAddress);


#endif /* HIGH_LEVEL_ABSTRACTIONS_DNS_ABSTRACTIONS_DNS_SERVICE_H_ */
