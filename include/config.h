#ifndef CONFIG_H
#define CONFIG_H   

#include <Arduino.h>
#include <SPI.h>
#include <SD.h>
#include "globalDef.h"


class Config{
    private:
        File file;
    public:
        bool load(const char* filename, config_data &configData);
        void createDefault(config_data &config);

};

#endif