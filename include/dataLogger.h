#include <SPI.h>
#include <SD.h>
#include <ESP32Time.h>
#include "globalDef.h"

#define CS_PIN 15

extern ESP32Time rtc;
extern String currentDate, prevDate;
extern File file;


void init_sdcard();
void init_internalRTC();
void update_fileLogger();
void writeCSV(String data);