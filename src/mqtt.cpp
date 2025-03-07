#include "mqtt.h"
//#include "connection.h"



// const char* mqttHost = "keretaiot-mqtt.doelengineering.cloud";
// const int mqttPort = 8080; // WebSocket port
//const char* topic = "v1/devices/me/telemetry";

// WebSocketsClient wsClient;
// MQTTPubSubClient mqttClient;

// void setupMQTTClient() {
//     wsClient.begin(configData.mqttHost, configData.mqttPort, "/mqtt");
//     wsClient.setReconnectInterval(2000); // Reconnect interval
//     mqttClient.begin(wsClient);

//     mqttClient.connect("ESP32", "NGrP3Uy5k42FUXkgCqFL", "");
//     delay(500);
//     // Serial.print("MQTT connected for device ");
//     // Serial.println("ckDasiat4E0bQ2DuD2wr");
// }

// void pubMasterData() {
//     mqttClient.update();

//        // Create JSON payload
//     String payload = "{";
//     // payload += "\"datetime\":" + core1_datetime + ",";
//     // payload += "\"datetime\":" + String("2022-01-01 00:00:00") + ",";
//     payload += "\"latitude\":" + String(masterData_core1.latitude) + ",";
//     payload += "\"longitude\":" + String(masterData_core1.longitude) + ",";
//     payload += "\"gyro_x\":" + String(masterData_core1.gx) + ",";
//     payload += "\"gyro_y\":" + String(masterData_core1.gy) + ",";
//     payload += "\"gyro_z\":" + String(masterData_core1.gz) + ",";
//     payload += "\"accel_x\":" + String(masterData_core1.ax) + ",";
//     payload += "\"accel_y\":" + String(masterData_core1.ay) + ",";
//     payload += "\"accel_z\":" + String(masterData_core1.az) + "}";

//     // Serial.println(payload);
    
//     // Publish telemetry data
//     if (mqttClient.publish(topic, payload)) {
//         Serial.print("Data published for device ");
//         Serial.println("ckDasiat4E0bQ2DuD2wr");
//     } else {
//         Serial.print("Failed to publish data for device ");
//         Serial.println("ckDasiat4E0bQ2DuD2wr");
//     }
// }

bool MQTT::begin() {
    wsClient.begin(configData.mqttHost, configData.mqttPort, "/mqtt");
    wsClient.setReconnectInterval(2000); // Reconnect interval
    mqttClient.begin(wsClient);

    mqttClient.connect(id, username, "");
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

    // Serial.println(payload);
    
    // Publish telemetry data
    if (mqttClient.publish(topic, payload)) {
        // Serial.print("Data published for device ");
        // Serial.println("ckDasiat4E0bQ2DuD2wr");
        return true;
    } else {
        // Serial.print("Failed to publish data for device ");
        // Serial.println("ckDasiat4E0bQ2DuD2wr");
        return false;
    }
}



