#include "mqtt.h"

bool MQTT::begin() {
    wsClient.begin(configData.mqttHost, configData.mqttPort, "/mqtt");
    wsClient.setReconnectInterval(2000); // Reconnect interval
    mqttClient.begin(wsClient);

    return mqttClient.connect(configData.deviceID, configData.mqttUsername, "")?true:false;
    delay(500);
}

bool MQTT::publish(master_data &data) {
    mqttClient.update();

    // Create JSON payload
    snprintf(payload, sizeof(payload),
    "{"
    "\"latitude\":%.6f,"
    "\"longitude\":%.6f,"
    "\"gyro_x\":%.6f,"
    "\"gyro_y\":%.6f,"
    "\"gyro_z\":%.6f,"
    "\"accel_x\":%.6f,"
    "\"accel_y\":%.6f,"
    "\"accel_z\":%.6f"
    "}",
    data.latitude,
    data.longitude,
    data.gx,
    data.gy,
    data.gz,
    data.ax,
    data.ay,
    data.az);

    return mqttClient.publish(configData.mqttTopic, payload)?true:false;
}



