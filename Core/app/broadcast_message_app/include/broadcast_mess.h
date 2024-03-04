/*
 * broadcast_mess.h
 *
 *  Created on: Mar 4, 2024
 *      Author: kirill
 */

#ifndef APP_BROADCAST_MESSAGE_APP_INCLUDE_BROADCAST_MESS_H_
#define APP_BROADCAST_MESSAGE_APP_INCLUDE_BROADCAST_MESS_H_

#include "stdio.h"
#include "stdint.h"
#include "data_types.h"

void set_broadcast_message_eth_info(Ethernet_info_struct * eth);
int16_t get_broadcast_message_payload(char * buffer, uint16_t buff_len);

#endif /* APP_BROADCAST_MESSAGE_APP_INCLUDE_BROADCAST_MESS_H_ */
