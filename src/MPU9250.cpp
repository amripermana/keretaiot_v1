#include "MPU9250.h"
#include "globalDef.h"

uint8_t buffer[14]; 
// int16_t accelX ;
// int16_t accelY ;
// int16_t accelZ ;
int16_t gyroX ;
int16_t gyroY ;
int16_t gyroZ ;


// Fungsi untuk menulis ke register
void writeRegister(uint8_t reg, uint8_t value) {
  Wire.beginTransmission(MPU9250_ADDR);
  Wire.write(reg);
  Wire.write(value);
  Wire.endTransmission();
}

// Fungsi untuk membaca data dari register
uint8_t readRegister(uint8_t reg) {
  Wire.beginTransmission(MPU9250_ADDR);
  Wire.write(reg);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU9250_ADDR, (uint8_t)1);
  return Wire.read();
}

// Fungsi untuk membaca beberapa byte secara burst
void readBurst(uint8_t reg, uint8_t* buffer, uint8_t length) {
  Wire.beginTransmission(MPU9250_ADDR);
  Wire.write(reg);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU9250_ADDR, length);
  for (uint8_t i = 0; i < length; i++) {
    buffer[i] = Wire.read();
  }
}

// Fungsi untuk membaca data 16-bit (2 byte)
int16_t combineBytes(uint8_t high, uint8_t low) {
  return (int16_t)((high << 8) | low);
}

void init_mpu9250() {

  // Bangunkan MPU9250
  writeRegister(PWR_MGMT_1, 0x00); // Matikan mode sleep
  delay(100);
  // Konfigurasi DLPF untuk gyroscope dan accelerometer
  writeRegister(CONFIG, 0x01); // DLPF_CFG = 1 (BW = 184 Hz untuk gyro, 188 Hz untuk accel)

  // Konfigurasi sampling rate (10 Hz)
  writeRegister(SMPLRT_DIV, 799); // SMPLRT_DIV = 799 untuk 10 Hz

  // Konfigurasi full-scale range accelerometer (±2g)
  writeRegister(ACCEL_CONFIG, 0x00);

  // Konfigurasi full-scale range gyroscope (±250°/s)
  writeRegister(GYRO_CONFIG, 0x00);

  // Aktifkan interrupt untuk data ready
  writeRegister(INT_ENABLE, 0x01); // INT_ENABLE = 1 (data ready interrupt)

  writeRegister(INT_PIN_CFG, 0x10);

     // Verifikasi WHO_AM_I register
  uint8_t whoAmI = readRegister(0x75);
  if (whoAmI == 0x70) {
    Serial.println("MPU9250 initialized successfully!");
  } else {
    Serial.print("Failed to initialize MPU9250. WHO_AM_I = 0x");
    Serial.println(whoAmI, HEX);
    while (1);
  }


}

void readMpuData(){
  readBurst(ACCEL_XOUT_H, buffer, 14);
  // accelX = combineBytes(buffer[0], buffer[1]);
  // accelY = combineBytes(buffer[2], buffer[3]);
  // accelZ = combineBytes(buffer[4], buffer[5]);
  gyroX = combineBytes(buffer[8], buffer[9]);
  gyroY = combineBytes(buffer[10], buffer[11]);
  gyroZ = combineBytes(buffer[12], buffer[13]);
}