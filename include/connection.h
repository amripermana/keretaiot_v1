#define TINY_GSM_MODEM_SIM7600

#include <WiFi.h>
#include <TinyGsmClient.h>
#include "globalDef.h"


// extern TinyGsm modem;
// extern TinyGsmClient gsmClient;
         

void connectWiFi(char* ssid, char* password);
void SIM_init();