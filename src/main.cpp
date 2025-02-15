#include <Arduino.h>
#include "globalDef.h"
#include "timer.h"
#include "MPU9250.h"
#include "connection.h"
#include "mqtt.h"
#include "dataLogger.h"
#include "adxl314.h"

SemaphoreHandle_t xSemaphore;

volatile master_data masterData;
master_data masterData_core1;
String core1_datetime;
HardwareSerial SerialAT(1);



void Core0(void * parameter) {
  init_timer0();
   for (;;) {
      if(iteration_1_ms){
        //Code for 1 ms

        //end of 1 ms
        // iteration_1_sec++;
        iteration_100_ms++;
        iteration_1_ms = false;
      }

      if(iteration_100_ms >= 100){
        //Code for 10 ms

        //get mpu data
        readMpuData();
        readAccelData();
        //get adxl data
        //get gps data
        if (xSemaphoreTake(xSemaphore, portMAX_DELAY)) {
          //dummy data
          masterData.ax = accelX;
          masterData.ay = accelY;
          masterData.az = accelZ;
          masterData.gx = gyroX;
          masterData.gy = gyroY;
          masterData.gz = gyroZ;
          masterData.latitude = 7.8;
          masterData.longitude = 8.9;
          dateTime = rtc.getTime("%Y-%m-%d-%H:%M:%S");

          xSemaphoreGive(xSemaphore);
        }
        
        if(sd_state){
          update_fileLogger();
          String dataToSend = String(masterData.ax) + "," + String(masterData.ay) + "," + String(masterData.az) + "," + String(masterData.gx) + "," + String(masterData.gy) + "," + String(masterData.gz) + "," + String(masterData.latitude) + "," + String(masterData.longitude);
          writeCSV(dataToSend);
        }
        

        iteration_100_ms = 0;
        //end of 10 ms
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
        iteration_1000_ms_core1++;
        iteration_1_ms_core1 = false;
    }

    if(iteration_1000_ms_core1 >= 1000){
      // Serial.println("masuk core1 1000 ms");
      if (xSemaphoreTake(xSemaphore, portMAX_DELAY)) {
        memcpy((void*)&masterData_core1, (const void*)&masterData, sizeof(master_data));
        core1_datetime = dateTime;

        xSemaphoreGive(xSemaphore);
      }

      pubMasterData();

      iteration_1000_ms_core1 = 0;
    }

    vTaskDelay(1);
  }
}

void setup() { 
  Serial.begin(115200);
  SerialAT.begin(115200, SERIAL_8N1, RX2, TX2, false);
  Wire.begin(); 
  Wire.setClock(400000);

  //init GPIO
  pinMode(mux_A1, OUTPUT);
  pinMode(mux_A0, OUTPUT);
  pinMode(mux_EN, OUTPUT);


  //create semaphore
  xSemaphore = xSemaphoreCreateMutex();
  if (xSemaphore == NULL) {
      Serial.println("Failed to create semaphore!");
      return;
  }

  //inisialisasi MPU9250
  init_sdcard();
  init_mpu9250();
  init_adxl314();
  // connectWiFi("tongfangcong", "shintaeyong");
  SIM_init();
  setupMQTTClient();
  init_dualcore();
  init_internalRTC();

}


void loop() {
  // delay(1);
  vTaskDelay(1);
}