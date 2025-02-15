#include <WiFi.h>
#include <WebSocketsClient.h>
#include <MQTTPubSubClient.h>

extern WebSocketsClient wsClient;
extern MQTTPubSubClient mqttClient;

void setupMQTTClient();
void pubMasterData();
