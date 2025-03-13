#include "firmwareOTA.h"

HTTPClient http;
const char* serverUrl = "http://keretaiot.com/test_ota/uploader.php";
int updatedFirmwareVersion = -1;
int currentFirmwareVersion = -1;

int checkFirmwareVersion(){
  int versi = -1;
  String v;
  File root = SD.open("/firmware");
  if (!root || !root.isDirectory()) {
      Serial.println("(check firmware version) : Failed to open directory");
  }

  File file = root.openNextFile();
  if (file) {
    //  Serial.print("FILE: ");
    //  Serial.println(file.name());
      v = file.name();
      sscanf(v.c_str(), "iotkai_%d.bin", &versi);
  }
  else{
    Serial.println("(check firmware version) : folder firmware kosong");
  }
  file.close();
  root.close();
  return versi;
}

bool isFirmwareUpdate(){
  bool isUpdate = true;
  http.begin(serverUrl);
  int httpCode = http.GET();
  if (httpCode > 0) {  // Jika berhasil
    String response = http.getString();  // Ambil respons dari server
    sscanf(response.c_str(), "iotkai_%d.bin", &updatedFirmwareVersion);
//    Serial.print("updated firmware ver: ");
//    Serial.println(updatedFirmwareVersion);
  } else {
    Serial.printf("(check firmware update): server or connection error");
  }
  http.end();

  currentFirmwareVersion = checkFirmwareVersion();
  
  if(updatedFirmwareVersion>currentFirmwareVersion){
    isUpdate = false;
  }
  else{
    isUpdate = true;
  }

  return isUpdate;
}

void downloadFirmware(){
  //delete all firmware on /firmware folder
  File dir = SD.open("/firmware");
  if (!dir || !dir.isDirectory()) {
    Serial.println("(download Firmware) : folder firmware tidak ditemukan");
  }
  File file = dir.openNextFile();
  while (file) {
    String filename = file.name();
    String path = "/firmware";
    file.close();
    if (SD.remove(path +"/"+ filename)) {
        Serial.println("(download Firmware) : Dihapus " + filename);
    } else {
        Serial.println("(download Firmware) : Gagal hapus " + filename);
    }
    file = dir.openNextFile();
  }
  //finish delete
  
  String ver = "/firmware/iotkai_"+String(updatedFirmwareVersion)+".bin";
  file = SD.open(ver, FILE_WRITE);
  if (!file) {
    Serial.println("(download Firmware) : initial write error");
  }
  HTTPClient http;
  http.begin(serverUrl);
  int httpCode = http.POST("device_id=1234");

  if(httpCode == HTTP_CODE_OK){
    WiFiClient *stream = http.getStreamPtr();
    uint8_t buffer[1024];
    int bytesRead;
    byte last_array[] = {0xB1, 0x8D, 0x08};
    bool first_index = true;
    while ((bytesRead = stream->readBytes(buffer, sizeof(buffer))) > 0) {
      file.write(buffer, bytesRead);
    }
    file.close();
    dir.close();
  }
  Serial.println("(download Firmware) : firmware berhasil didownload");
  http.end();
}
