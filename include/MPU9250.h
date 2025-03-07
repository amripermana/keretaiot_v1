#include <Arduino.h>
#include <Wire.h>
#include "globalDef.h"

#define MPU9250_ADDR 0x68 // Alamat I2C MPU9250
#define PWR_MGMT_1   0x6B // Register Power Management 1
#define CONFIG       0x1A // Register untuk mengatur DLPF
#define SMPLRT_DIV   0x19 // Register untuk mengatur sampling rate
#define ACCEL_CONFIG 0x1C // Register konfigurasi accelerometer
#define GYRO_CONFIG  0x1B // Register konfigurasi gyroscope
#define INT_ENABLE   0x38 // Register untuk mengaktifkan interrupt
#define INT_STATUS   0x3A // Register untuk memeriksa status interrupt
#define ACCEL_XOUT_H 0x3B // Register data pertama untuk accelerometer
#define INT_PIN      33   // GPIO ESP32 untuk menerima sinyal interrupt dari MPU9250
#define INT_PIN_CFG  0x37 // Register konfigurasi pin interrupt

// extern int16_t gyroX ;
// extern int16_t gyroY ;
// extern int16_t gyroZ ;
// extern uint8_t buffer[14]; 
// void init_mpu9250();
// void readMpuData();

class MPU9250{
    private:
        uint8_t buffer[14];
        void writeRegister(uint8_t reg, uint8_t value);
        uint8_t readRegister(uint8_t reg);
        void readBurst(uint8_t reg, uint8_t* buffer, uint8_t length);
        int16_t combineBytes(uint8_t high, uint8_t low);

    public:
        MPU9250(){

        }
        int16_t gyroX;
        int16_t gyroY;
        int16_t gyroZ;
        bool begin();
        void read();
};
