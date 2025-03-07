#include <SPI.h>
#include <SD.h>
#include <ESP32Time.h>
#include "globalDef.h"


class Datalogger{
    private:
        File file;
        String currentDate, prevDate;
        ESP32Time rtc;
        char dataToSend[64];
        void init_internalRTC();
    public:
        Datalogger(){
            init_internalRTC();
        };
        String dateTime;
        bool SD_STATE;
        void checkFile();
        bool write(master_data data);
};