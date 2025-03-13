#ifndef INSPECTOR_H
#define INSPECTOR_H

#include <Arduino.h>
#include <SD.h>
#include <SPI.h>
#include "globalDef.h"

class Inspector {
    private:
        String log_path = "/system_log.txt";
        File file;
        
    public:
        Inspector(){
            
        }
        void log(String state, String func, String message);
        bool create_log();
};


#endif