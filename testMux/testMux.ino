#include <Wire.h>

void setup() {
  Serial.begin(115200);
  
  // ย้ายบ้านหนีไฟ 5V! เปลี่ยนมาใช้ขา 25 (SDA) และ 26 (SCL)
  Wire.begin(21, 22); 
  
  Serial.println("\n--- เริ่มสแกนหาอุปกรณ์ (ใช้ขา 25, 26) ---");
  byte error, address;
  int nDevices = 0;

  for(address = 1; address < 127; address++ ) {
    Wire.beginTransmission(address);
    error = Wire.endTransmission();

    if (error == 0) {
      Serial.print("เจออุปกรณ์ I2C ที่ Address: 0x");
      if (address < 16) Serial.print("0");
      Serial.print(address, HEX);
      Serial.println(" !");
      nDevices++;
    }
  }
  
  if (nDevices == 0) {
    Serial.println("เงียบกริบ! ไม่เจออะไรเลย...");
  } else {
    Serial.println("--- สแกนเสร็จสิ้น ---");
  }
}

void loop() {}