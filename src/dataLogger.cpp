#include "dataLogger.h"
ESP32Time rtc;
String dateTime;
File file;
String currentDate;
String prevDate;
bool sd_state = false;

void init_sdcard() {
    if (!SD.begin(CS_PIN)) { 
        Serial.println("SD Card tidak terdeteksi");
        sd_state = false;
        return;
    }
    else{
        sd_state = true;
        Serial.println("Inisialisasi SD Card Berhasil");
    }
}

void init_internalRTC(){
    rtc.setTime(50, 59, 23, 12, 2, 2025);
    dateTime = rtc.getTime("%Y-%m-%d %H:%M:%S");
    currentDate = rtc.getTime("%Y-%m-%d");
}


void update_fileLogger(){
    currentDate = rtc.getTime("%Y-%m-%d");
    // dateTime = rtc.getTime("%Y-%m-%d %H:%M:%S");
    if(!currentDate.equals(prevDate)){ //ganti, dia tidak terdeteksi
        prevDate = currentDate;
        file = SD.open("/" + currentDate + ".csv", FILE_WRITE);
        if (file) {
            file.println("dateTime,ax,ay,az,gx,gy,gz,latitude,longitude");
            file.close();
        } else {
            //failed to write
        }
    }
}

void writeCSV(String data){
    file = SD.open("/" + rtc.getTime("%Y-%m-%d") + ".csv", FILE_APPEND);
    if (file) {
        file.println(String(millis())+","+data);
        file.close();
    } else {
        //failed to write
    }
}
