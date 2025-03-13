#ifndef mqtt_H
#define mqtt_H

#include <WiFi.h>
#include <WebSocketsClient.h>
#include <MQTTPubSubClient.h>
#include "globalDef.h"

class MQTT{
    private:
        WebSocketsClient wsClient;
        MQTTPubSubClient mqttClient;
        char payload[256];

    public:
        MQTT(){
    
        }
        bool begin();
        bool publish(master_data &data);
};

#endif