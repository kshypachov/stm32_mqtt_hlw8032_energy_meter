/*
 * ethernet_init.c
 *
 *  Created on: 15 янв. 2023 г.
 *      Author: kir
 */
#include "ethernet_init.h"
//#include "gpio.h"
//#include "spi.h"
#include "dhcp.h"
#include "definition.h"
#include "stdbool.h"

bool ip_dhcp_assigned = false;
wiz_NetInfo * NetInfo;
uint8_t my_dhcp_retry = 0;

void (*delay_ms)(uint32_t sec);

void (*ResetON)	(void);
void (*ResetOFF)(void);

void proto_reset(void){};

void proto_delay_func(uint32_t sec){
	sec = sec * 10000;

	while (sec){
		sec--;
	}

}

void w5500_lib_init(wiz_NetInfo * NetInfoStructure)
{
	NetInfo = NetInfoStructure;
}

void network_init(void)
{	wiz_NetTimeout 	nettimeout;

	nettimeout.retry_cnt	= 3;
	nettimeout.time_100us	= 500;

	// Set Network information from netinfo structure
	ctlnetwork(CN_SET_NETINFO, NetInfo);
	ctlnetwork(CN_SET_TIMEOUT, (void*)&nettimeout);
}

void Callback_IPConflict(void)
{
	ip_dhcp_assigned = false;
}

void Callback_IPAssigned(void)
{
   getIPfromDHCP(NetInfo->ip);
   getGWfromDHCP(NetInfo->gw);
   getSNfromDHCP(NetInfo->sn);
   getDNSfromDHCP(NetInfo->dns);
   NetInfo->dhcp = NETINFO_DHCP;
   // Network initialization
   network_init();      // apply from dhcp

   ip_dhcp_assigned = true;
#ifdef _MAIN_DEBUG_
   printf("DHCP LEASED TIME : %ld Sec.\r\n", getDHCPLeasetime());//Ãƒï¿½Ã‚Â Ãƒâ€˜Ã¢â‚¬â€�Ãƒï¿½Ã‚Â Ãƒâ€˜Ã¢â‚¬Â¢Ãƒï¿½Ã‚Â Ãƒâ€šÃ‚Â»Ãƒï¿½Ã‚Â¡Ãƒâ€˜Ã¢â‚¬Å“Ãƒï¿½Ã‚Â¡ÃƒÂ¢Ã¢â€šÂ¬Ã‚Â¡Ãƒï¿½Ã‚Â Ãƒâ€˜Ã¢â‚¬ËœÃƒï¿½Ã‚Â¡ÃƒÂ¢Ã¢â€šÂ¬Ã…Â¡Ãƒï¿½Ã‚Â¡Ãƒï¿½Ã…Â  Ãƒï¿½Ã‚Â Ãƒï¿½Ã¢â‚¬Â Ãƒï¿½Ã‚Â¡Ãƒï¿½Ã¢â‚¬Å¡Ãƒï¿½Ã‚Â Ãƒâ€šÃ‚ÂµÃƒï¿½Ã‚Â Ãƒâ€˜Ã‹Å“Ãƒï¿½Ã‚Â¡Ãƒï¿½Ã¯Â¿Â½ Ãƒï¿½Ã‚Â Ãƒâ€šÃ‚Â°Ãƒï¿½Ã‚Â¡Ãƒï¿½Ã¢â‚¬Å¡Ãƒï¿½Ã‚Â Ãƒâ€šÃ‚ÂµÃƒï¿½Ã‚Â Ãƒï¿½Ã¢â‚¬Â¦Ãƒï¿½Ã‚Â Ãƒâ€™Ã¢â‚¬ËœÃƒï¿½Ã‚Â¡ÃƒÂ¢Ã¢â€šÂ¬Ã‚Â¹ Ãƒï¿½Ã‚Â Ãƒï¿½Ã¢â‚¬Â¦Ãƒï¿½Ã‚Â Ãƒâ€šÃ‚Â° Ãƒï¿½Ã‚Â¡Ãƒï¿½Ã†â€™Ãƒï¿½Ã‚Â Ãƒâ€šÃ‚ÂµÃƒï¿½Ã‚Â¡Ãƒï¿½Ã¢â‚¬Å¡Ãƒï¿½Ã‚Â Ãƒï¿½Ã¢â‚¬Â Ãƒï¿½Ã‚Â Ãƒâ€šÃ‚ÂµÃƒï¿½Ã‚Â¡Ãƒï¿½Ã¢â‚¬Å¡Ãƒï¿½Ã‚Â Ãƒâ€šÃ‚Âµ DHCP
#endif
}

void dhcp_rutine(void){
	switch(DHCP_run())
			{
			case DHCP_IP_ASSIGN:
			case DHCP_IP_CHANGED:
			case DHCP_IP_LEASED:
			break;
			case DHCP_FAILED:
				my_dhcp_retry++;
				break;
				if(my_dhcp_retry > MAX_DHCP_FAIL)
				{
					#ifdef _MAIN_DEBUG_
					printf(">> DHCP %d Failed\r\n", my_dhcp_retry);
					#endif
					my_dhcp_retry = 0;
					DHCP_stop();      // if restart, recall DHCP_init()
					network_init();
					ip_dhcp_assigned = false;
				}
			default:
				break;
			}
}

int link_status(void){
	uint8_t temp;
	ctlwizchip(CW_GET_PHYLINK, (void*)&temp);
	if (!temp)ip_dhcp_assigned = false;
	return temp;
}

int link_duplex(void){
	wiz_PhyConf phy_status;
	wizphy_getphystat(&phy_status);
	return phy_status.duplex;
}

int link_speed(void){
	wiz_PhyConf phy_status;
	wizphy_getphystat(&phy_status);
	return phy_status.speed;
}

int assigned_ip(void){
	return ip_dhcp_assigned;
}

void set_ip_aasigned(void){
	ip_dhcp_assigned = true;
}

int w5500_init(void)
{
  uint8_t W5500FifoSize[2][8] = {{2, 2, 2, 2, 2, 2, 2, 2, }, {2, 2, 2, 2, 2, 2, 2, 2}};

  ResetON();
  delay_ms(delay0_5s);
  ResetOFF();
  delay_ms(delay3s);

  if (ctlwizchip(CW_INIT_WIZCHIP, (void*)W5500FifoSize) == -1)
  {
	  return -1;
  }

  if (link_status()==PHY_LINK_OFF){
	   return -1;
  }

  ip_dhcp_assigned = false;
  return 0;
}

void w5500_delay_cb(void (*function)(uint32_t time))
{
	delay_ms = proto_delay_func;

	if (function){
		delay_ms = function;
	}
}

void w5500_reset_cb(void(* reset)(void), void (* unreset)(void)){

	ResetON 	= proto_reset;
	ResetOFF	= proto_reset;
	if (reset) 	ResetON =  reset;
	if (unreset)ResetOFF = unreset;
}
