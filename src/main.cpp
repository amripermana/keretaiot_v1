#include <Arduino.h>
#include "globalDef.h"
#include "timer.h"
#include "MPU9250.h"
#include "connection.h"
#include "mqtt.h"
#include "Datalogger.h"
#include "ADXL314.h"
#include "config.h"
#include "firmwareOTA.h"
#include "Inspector.h"

SemaphoreHandle_t xSemaphore;

master_data masterData;
master_data masterData_core1;
String core0_dateTime;
String core1_dateTime;
HardwareSerial SerialAT(1);
File file;
config_data configData;
Inspector inspector;
MPU9250 mpu;
ADXL314 adxl;
Datalogger logger;
MQTT mqtt;
Config config;
Status status;



void Core0(void * parameter) {
  init_timer0();
   for (;;) {
      if(iteration_1_ms){
        //Code for 1 ms

        //end of 1 ms
        // iteration_1_sec++;
        iteration_100_ms++;
        iteration_1000_ms++;
        iteration_1_ms = false;
      }

      if(iteration_100_ms >= 100){
        
      }

      if(iteration_1000_ms >= 1000){
        // Serial.println("masuk core1 1000 ms");
        if (xSemaphoreTake(xSemaphore, portMAX_DELAY)) {
          memcpy((void*)&masterData_core1, (const void*)&masterData, sizeof(master_data));
          core0_dateTime = core1_dateTime;

          xSemaphoreGive(xSemaphore);
        }

        if(!mqtt.publish(masterData_core1)){
          Serial.println("(MQTT) : Failed to publish data");
        }

        iteration_1000_ms = 0;
      }


    vTaskDelay(1);
    }
}

void Core1(void * parameter) {
  init_timer1();
  for (;;) {
    if(iteration_1_ms_core1){
        //Code for 1 ms

        //end of 1 ms
        // iteration_1_sec++;
        iteration_100_ms_core1++;
        iteration_1000_ms_core1++;
        iteration_1_ms_core1 = false;
    }

    if(iteration_100_ms_core1 >= 100){
      //Code for 10 ms

      mpu.read();
      adxl.read();
      //get gps data

      if (xSemaphoreTake(xSemaphore, portMAX_DELAY)) {
        //dummy data
        masterData.ax = adxl.accelX;
        masterData.ay = adxl.accelY;
        masterData.az = adxl.accelZ;
        masterData.gx = mpu.gyroX;
        masterData.gy = mpu.gyroY;
        masterData.gz = mpu.gyroZ;
        masterData.latitude = 7.8;
        masterData.longitude = 8.9;
        core1_dateTime = logger.dateTime;

        xSemaphoreGive(xSemaphore);
      }
      
      if(logger.SD_STATE){
        logger.checkFile();
        if(!logger.write(masterData)){
          //failed to write
          //(!) ERROR Code failde to save logger?
        }
      }
      

      iteration_100_ms = 0;
      //end of 10 ms
    }

    if(iteration_1000_ms_core1 >= 1000){
      
    }

    vTaskDelay(1);
  }
}

void setup() { 

  Serial.begin(115200);
  SerialAT.begin(115200, SERIAL_8N1, RX2, TX2, false);

   //init SPI SD Card
  if (!SD.begin(CS_PIN)) { 
    Serial.println("(SD CARD) : SD Card tidak terdeteksi");
  }
  else{
    //inspector.create_log();
    Serial.println("(SD CARD) : SD Card terdeteksi");
    status.SD = true;
    if(inspector.create_log()){
      inspector.log("INFO", "SD Card", "SD Card Initialized!");
      Serial.println("(SD CARD) : sytem_log created!");
    }
    else{
      Serial.println("(SD CARD) : sytem_log failed");
    }   
  }

  
  Wire.begin(); 
  Wire.setClock(400000);
  inspector.log("INFO", "I2C", "I2C initialized!");

  //init GPIO
  pinMode(mux_A1, OUTPUT);
  pinMode(mux_A0, OUTPUT);
  pinMode(SIM7670_K_PIN, OUTPUT);
  // pinMode(SIM7670_S_PIN, OUTPUT); //io2 not useable
  // pinMode(DECODER_A, OUTPUT);
  // pinMode(DECODER_B, OUTPUT); //io7 not useable
  // pinMode(DECODER_C, OUTPUT); //io8 not useable

  //testDecoder();

  //create semaphore
  xSemaphore = xSemaphoreCreateMutex();
  if (xSemaphore == NULL) {
      inspector.log("ERROR", "Semaphore", "Failed to create semaphore!");
      return;
  }

  // init config file
  if(!config.load("/config.txt", configData)){
    config.createDefault(configData);
    inspector.log("INFO", "Config", "config file not found, default config created!");
    Serial.println("(config file) : config.txt not found, default config created!");
  }
  else{
    inspector.log("INFO", "Config", "config file loaded!");
  }


  //start_internet();
  if(!SIM_init()){
    inspector.log("ERROR", "Internet", "SIM no connected, no internet connection!");
    if(!connectWiFi(configData.wifi_ssid, configData.wifi_password)){
        inspector.log("ERROR", "Internet", "wifi no connected, no internet connection!");
        //(!)Error Code wifi no connected, no internet connection
        //(!) Run FIFO
    }
    else{
      inspector.log("INFO", "Internet", "wifi connected!");
      status.WIFI = true;
    }
  }
  else{
    inspector.log("INFO", "Internet", "SIM connected!");
    status.SIM = true;
  }


  //checking firmware
  if((status.SIM || status.WIFI) && status.SD){
    if(!isFirmwareUpdate()){
      downloadFirmware();
      inspector.log("INFO", "Firmware", "Firmware is not update downloading new firmware!");
      //(!) update firmware
    }
    else{
      Serial.print("Firmware version : ");
      Serial.println(checkFirmwareVersion());
      inspector.log("INFO", "Firmware", "Firmware version : " + String(checkFirmwareVersion()));
    }
  }
  else{
    Serial.println("(Firmware) : No Internet Connection or SD Card not detected!");
  }
  

  // init_mpu9250();
  if(mpu.begin()){
    inspector.log("INFO", "MPU9250", "MPU9250 initialized!");
    Serial.println("(MPU) : MPU Initialized");
    status.MPU = true;
  }
  else{
    inspector.log("ERROR", "MPU9250", "MPU9250 not initialized!");
    Serial.println("(MPU) : MPU Failed, System Stop");
    while(1);
  }


  // init_adxl314();
  if(adxl.begin()){
    inspector.log("INFO", "ADXL314", "ADXL314 initialized!");
    Serial.println("(ADXL) : ADXL Initialized");
    status.ADXL = true;
  }
  else{
    inspector.log("ERROR", "ADXL314", "ADXL314 not initialized!");
    Serial.println("(ADXL) : ADXL Failed, System Stop");
    while(1);
  }

  if(mqtt.begin()){
    inspector.log("INFO", "MQTT", "MQTT initialized!");
    Serial.println("(MQTT) : MQTT Initialized");
    status.MQTT = true;
  }
  else{
    inspector.log("ERROR", "MQTT", "MQTT not initialized!");
    Serial.println("(MQTT) : MQTT Failed");
  }

  init_dualcore();


}


void loop() {
  // delay(1);
  vTaskDelay(1);
}