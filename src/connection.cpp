#include "connection.h"

const char apn[]      = "internet";  
const char user[]     = "";           
const char pass[]     = ""; 


TinyGsm modem(SerialAT);
TinyGsmClient gsmClient(modem);
unsigned long wifi_timeout = 0;

bool connectWiFi(String ssid, String password) {
    Serial.print("(Wifi) : Connecting to WiFi");
    WiFi.begin(ssid, password);
    wifi_timeout = millis();
    while (millis() - wifi_timeout < 5000) {
        if(WiFi.status() == WL_CONNECTED){
            Serial.println("(Wifi) : Connected to WiFi");
            return true;
        }
    }
    if(WiFi.status() != WL_CONNECTED){
        Serial.println("(Wifi) : Failed to connect to WiFi");
        return false;
    }
    
}

bool SIM_init() {

    //(!)buatkan fungsi khusus untuk mux(!)
    digitalWrite(mux_EN, HIGH);
    digitalWrite(mux_A1, HIGH);
    digitalWrite(mux_A0, LOW);
  
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
        if(!connectWiFi(configData.wifi_ssid, configData.wifi_password)){
            //(!)Error Code wifi no connected, no connection
            //(!) Run FIFO
        }
    }
}

