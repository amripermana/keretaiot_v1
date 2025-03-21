#include "config.h"


bool Config::load(const char* filename, config_data &configData) {
    file = SD.open(filename, FILE_READ);
    if (file) {
        while (file.available()) {
            String line = file.readStringUntil('\n');
            line.trim();  // Hapus spasi dan karakter newline
    
            int separatorIndex = line.indexOf('=');
            if (separatorIndex == -1) continue;  // Lewati jika tidak ada "="
    
            String key = line.substring(0, separatorIndex);
            String value = line.substring(separatorIndex + 1);
    
            // Simpan ke struct berdasarkan key
            if (key == "ssid") configData.wifi_ssid = value;
            else if (key == "password") configData.wifi_password = value;
            else if (key == "mqtt_host") configData.mqttHost = value;
            else if (key == "mqtt_port") configData.mqttPort = value.toInt();
        }
        file.close();
        // Serial.println("(config file) : config.txt loaded");
        return true;

    }else{
        return false;
    }
}

void Config::createDefault(config_data &config) {
    file = SD.open("/config.txt", FILE_WRITE);
    if(file){
        file.println("ssid=your_wifi_ssid");
        file.println("password=your_wifi_password");
        file.println("mqtt_host=your_mqtt_host");
        file.println("mqtt_port=your_mqtt_port");
        file.close();
        Serial.println("(config file) : config.txt created using default values");
    }
    else{
        Serial.println("(config file) : Failed to create config.txt, check SD card");
        config.wifi_ssid = "hadehh";
        config.wifi_password = "12345678";
        config.mqttHost = "keretaiot-mqtt.doelengineering.cloud";
        config.mqttPort = 8080;
        config.mqttTopic = "v1/devices/me/telemetry";
        config.mqttUsername = "mnh7mid3h8oe3qze6fq6";
        config.deviceID = "20250307001";
    }
    
}