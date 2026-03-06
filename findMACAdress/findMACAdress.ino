#include "WiFi.h"

void setup(){
  Serial.begin(115200);
  delay(1000); // รอให้ระบบเข้าที่ 1 วินาที

  // บังคับให้เริ่มโหมด WiFi Station
  WiFi.mode(WIFI_STA);
  delay(500); 

  Serial.println();
  Serial.print("ESP32 Board MAC Address: ");
  
  // พิมพ์ค่า MAC Address
  Serial.println(WiFi.macAddress());
}

void loop(){
}