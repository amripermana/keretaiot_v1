#include "Inspector.h"

bool Inspector::create_log(){
    if(SD.exists(log_path)){
        if(SD.remove(log_path)){
            file = SD.open(log_path, FILE_WRITE);
            log("INFO", "inspector", "system log created!");
            if(file){
                inspector_stat = true;
                return true;
            }
            else{
                inspector_stat = false;
                Serial.println("(inspector) : Failed to create system.log, check SD card!");
                return false;
            }
        }
        else{
            Serial.println("(inspector) : Failed to create system.log, check SD card!");
            inspector_stat = false;
            return false;
        }
    }
    else{
        file = SD.open(log_path, FILE_WRITE);
        log("INFO", "inspector", "system log created!");
        return file ? true : false;
    }
    
    
    file.close();
}

void Inspector::log(String status, String func, String message){
    if(inspector_stat){
        String time_stamp = String(millis()/1000);
        String msg = status + " (" + time_stamp + ") " + func + " : " + message;
        file = SD.open(log_path, FILE_APPEND);
        file.println(msg);
        file.close();
    }
}