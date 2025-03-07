#include <Wire.h>
#include <Arduino.h>

#define I2C_ADDRESS 0x53  // Alamat default ADXL314
#define READ_X 0x32       // Register untuk membaca data X
#define READ_Y 0x34       // Register untuk membaca data Y
#define READ_Z 0x36       // Register untuk membaca data Z
#define DATA_FORMAT 0x31  // Register untuk mengatur format data

// extern float accelX ;
// extern float accelY ;
// extern float accelZ ;

// void init_adxl314();
// void readAccelData();
// float readAccelerometer(byte registerAddress);

class ADXL314 {
    private:
        float readAccelerometer(byte registerAddress);

    public:
        ADXL314(){};
        float accelX ;
        float accelY ;
        float accelZ ;
        bool begin();
        void read();
};

