#include "connection.h"

const char apn[]      = "internet";  
const char user[]     = "";           
const char pass[]     = ""; 


TinyGsm modem(SerialAT);
TinyGsmClient gsmClient(modem);
unsigned long wifi_timeout = 0;

bool connectWiFi(String ssid, String password) {
    bool result = false;
    Serial.print("(Wifi) : Connecting to WiFi ");
    Serial.println(ssid);
    WiFi.begin(ssid.c_str(), password.c_str());
    wifi_timeout = millis();
    while (millis() - wifi_timeout < 5000) {
        if(WiFi.status() == WL_CONNECTED){
            Serial.println("(Wifi) : Connected to WiFi");
            result = true;
            break;
        }
    }
    if(WiFi.status() != WL_CONNECTED){
        Serial.println("(Wifi) : Failed to connect to WiFi");
        result = false;
    }

    return result;    
}

bool SIM_init() {

    setMux(mux_SIM7670);
    
    //wake up sim7670
    digitalWrite(SIM7670_K_PIN, LOW);
    delay(100);
    digitalWrite(SIM7670_K_PIN, HIGH);
  
    Serial.println("(SIM7060) : Inisialisasi SIM7060");
    if (!modem.restart()) {
        Serial.println("(SIM7060) : Gagal menginisialisasi SIM7060");
        return false;
    }
    
    Serial.println("(SIM7060) : Menghubungkan SIM7060 ke jaringan");
    modem.gprsConnect(apn, user, pass);
    
    if (modem.isGprsConnected()) {
        Serial.println("(SIM7060) : SIM7060 terhubung ke jaringan");
        return true;
    } else {
        Serial.println("(SIM7060) : Gagal menghubungkan SIM7060 ke jaringan");
        return false;
    }
}

void start_internet(){
    if(!SIM_init()){
        //if(!connectWiFi(configData.wifi_ssid, configData.wifi_password))
        if(!connectWiFi("ssid", "pass")){
            //(!)Error Code wifi no connected, no connection
            //(!) Run FIFO
        }
    }
}

