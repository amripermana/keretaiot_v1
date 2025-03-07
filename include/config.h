#ifndef CONFIG_H
#define CONFIG_H   

#include <Arduino.h>
#include <SPI.h>
#include <SD.h>
#include "globalDef.h"

extern File file;
extern config_data configData;

bool load_config(const char* filename, config_data &configData);
void createDefaultConfig();

#endif