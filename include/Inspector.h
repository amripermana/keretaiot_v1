#ifndef INSPECTOR_H
#define INSPECTOR_H

#include <Arduino.h>
#include <SD.h>
#include <SPI.h>

class Inspector {
    private:
        String log_path = "/system_log.txt";
        File file;
        
    public:
        bool inspector_stat;
        Inspector(){
            
        }
        void log(String status, String func, String message);
        bool create_log();
};


#endif