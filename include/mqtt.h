#ifndef mqtt_H
#define mqtt_H

#include <WiFi.h>
#include <WebSocketsClient.h>
#include <MQTTPubSubClient.h>
#include "globalDef.h"

// extern WebSocketsClient wsClient;
// extern MQTTPubSubClient mqttClient;

// void setupMQTTClient();
// void pubMasterData();

class MQTT{
    private:
        WebSocketsClient wsClient;
        MQTTPubSubClient mqttClient;
        const char* topic = "v1/devices/me/telemetry";
        const char* username = "NGrP3Uy5k42FUXkgCqFL";
        const char* id = "20250307001";
        char payload[256];

    public:
        MQTT(){
    
        }
        bool begin();
        bool publish(master_data &data);
};

#endif