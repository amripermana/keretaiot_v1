#ifndef globalDef_H
#define globalDef_H 

#include <HardwareSerial.h>

#define RXD2 16 // Pin RX ESP32 ke TX SIM7080G
#define TXD2 17 // Pin TX ESP32 ke RX SIM7080G
#define mux_A0 26
#define mux_A1 27
#define mux_RS485 1
#define mux_LORA 2
#define mux_SIM7670 3
#define mux_RS232 4

#define CS_PIN 15
#define SIM7670_S_PIN 2
#define SIM7670_K_PIN 25
#define DECODER_A 32
#define DECODER_B 8
#define DECODER_C 7



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
  String deviceID;
  String wifi_ssid;
  String wifi_password;
  String mqttHost;
  String mqttUsername;
  String mqttTopic;
  int mqttPort;
};

struct Status
{
  bool WIFI = false;
  bool SIM = false;
  bool MQTT = false;
  bool SD = false;
  bool ADXL = false;
  bool MPU = false;
};


void setMux(int val);
void setDecoder(int8_t val);
void testDecoder();

extern master_data masterData;
extern master_data masterData_core1;
extern String core1_datetime;
extern HardwareSerial SerialAT;
extern config_data configData;
extern Status status;
#endif