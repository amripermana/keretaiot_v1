#ifndef globalDef_H
#define globalDef_H 

#include <HardwareSerial.h>

#define RXD2 16 // Pin RX ESP32 ke TX SIM7080G
#define TXD2 17 // Pin TX ESP32 ke RX SIM7080G
#define mux_A0 26
#define mux_A1 27
#define mux_EN 25

#define CS_PIN 15



struct master_data {
  float ax;
  float ay;
  float az;
  float gx;
  float gy;
  float gz;
  float latitude;
  float longitude;  
};

struct config_data {
  String wifi_ssid;
  String wifi_password;
  String mqttHost;
  int mqttPort;
};

extern master_data masterData;
extern master_data masterData_core1;
extern String core1_datetime;
extern HardwareSerial SerialAT;
extern config_data configData;
#endif