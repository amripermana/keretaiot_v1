#ifndef connection_H
#define connection_H    

#define TINY_GSM_MODEM_SIM7600

#include <WiFi.h>
#include <TinyGsmClient.h>
#include "globalDef.h"


// extern TinyGsm modem;
// extern TinyGsmClient gsmClient;
         

bool connectWiFi(String ssid, String password);
bool SIM_init();
void start_internet();

#endif