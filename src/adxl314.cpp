#include "adxl314.h"

float accelX ;
float accelY ;
float accelZ ;

void init_adxl314() { 
    // Mengaktifkan mode pengukuran (bit 3 pada register 0x2D)
  Wire.beginTransmission(I2C_ADDRESS);
  Wire.write(0x2D);  // Register power control
  Wire.write(0x08);  // Mengaktifkan mode pengukuran
  byte result = Wire.endTransmission();
  
  // Mengatur format data pada register DATA_FORMAT (0x31) jika diperlukan
  Wire.beginTransmission(I2C_ADDRESS);
  Wire.write(DATA_FORMAT);  // Mengakses register DATA_FORMAT
  Wire.write(0x08);  // Set format 10-bit atau sesuai dengan kebutuhan sensor
  result = Wire.endTransmission();

  if (!result) {
    Serial.println("ADXL314 Initialized!");
  } else {
    Serial.println("Error initializing ADXL314");
    while (true); // Berhenti jika inisialisasi gagal
  }
}

float readAccelerometer(byte registerAddress) {
    Wire.beginTransmission(I2C_ADDRESS);
    Wire.write(registerAddress); // Mengakses register data (X, Y, atau Z)
    Wire.endTransmission();
  
    Wire.requestFrom(I2C_ADDRESS, 2); // Membaca dua byte data
    if (Wire.available() == 2) {
      byte lowByte = Wire.read();  // Membaca byte yang paling tidak signifikan
      byte highByte = Wire.read(); // Membaca byte yang paling signifikan
  
      // Menggabungkan highByte dan lowByte menjadi satu nilai 16-bit
      int value = (highByte << 8) | lowByte;
  
      // Jika nilai lebih dari 32767, berarti angka negatif dalam two's complement
      if (value > 32767) {
        value -= 65536;  // Mengkonversi nilai two's complement ke angka negatif
      }
  
      return value;  // Mengembalikan nilai akselerometer
    } else {
      Serial.println("Error reading I2C data.");
      return 0;
    }
  }

void readAccelData() {
    accelX = readAccelerometer(READ_X)*0.04883;
    accelY = readAccelerometer(READ_Y)*0.04883;
    accelZ = readAccelerometer(READ_Z)*0.04883;
}

