#include "connection.h"

const char apn[]      = "internet";  
const char user[]     = "";           
const char pass[]     = ""; 


TinyGsm modem(SerialAT);
TinyGsmClient gsmClient(modem);

void connectWiFi(char* ssid, char* password) {
    Serial.print("Connecting to WiFi");
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\nWiFi connected");
}

void SIM_init() {
    digitalWrite(mux_EN, HIGH);
    digitalWrite(mux_A1, HIGH);
    digitalWrite(mux_A0, LOW);
  
    Serial.println("Menginisialisasi modem...");
    if (!modem.restart()) {
        Serial.println("Gagal memulai modem!");
        while (true);
    }
    
    Serial.println("Menghubungkan ke jaringan...");
    modem.gprsConnect(apn, user, pass);
    
    if (modem.isGprsConnected()) {
        Serial.println("Terhubung ke jaringan!");
    } else {
        Serial.println("Gagal menghubungkan ke jaringan!");
        while (true);
    }
}

