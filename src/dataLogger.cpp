#include "Datalogger.h"


void Datalogger::init_internalRTC(){
    rtc.setTime(50, 59, 23, 12, 2, 2025);
    dateTime = rtc.getTime("%Y-%m-%d %H:%M:%S");
    currentDate = rtc.getTime("%Y-%m-%d");
}


void Datalogger::checkFile(){
    currentDate = rtc.getTime("%Y-%m-%d");
    dateTime = rtc.getTime("%Y-%m-%d %H:%M:%S");
    if(!currentDate.equals(prevDate)){ //ganti, dia tidak terdeteksi
        prevDate = currentDate;
        file = SD.open("/" + currentDate + ".csv", FILE_WRITE);
        if (file) {
            file.println("dateTime,ax,ay,az,gx,gy,gz,latitude,longitude");
            file.close();
            SD_STATE = true;
        } else {
            //failed to write
            SD_STATE = false;
        }
    }
}

bool Datalogger::write(master_data data){
    snprintf(dataToSend, sizeof(dataToSend), "%.2f,%.2f,%.2f,%.2f,%.2f,%.2f,%.6f,%.6f",
         data.ax, data.ay, data.az, data.gx, data.gy, data.gz, data.latitude, data.longitude);

    file = SD.open("/" + rtc.getTime("%Y-%m-%d") + ".csv", FILE_APPEND);
    if (file) {
        file.println(String(millis())+","+dataToSend);
        file.close();
        return true;
    } else {
        //failed to write
        return false;
    }
}



