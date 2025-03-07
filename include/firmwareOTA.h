#ifndef FIRMWAREOTA_H 
#define FIRMWAREOTA_H

#include <Arduino.h>
#include <HTTPClient.h>
#include "Update.h"
#include <SD.h>

int checkFirmwareVersion();
bool isFirmwareUpdate();
void downloadFirmware();


#endif
