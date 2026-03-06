int mainScoreCorrect = 0;
int mainScoreWrong = 0;

void setup() {
  Serial.begin(115200);
  Serial2.begin(9600, SERIAL_8N1, 16, 17); // TX=17, RX=16
  Serial.println("ESP Main พร้อมส่งคะแนน...");
}

void loop() {
  // จำลองเหตุการณ์: มีคนตอบถูก (คุณสามารถเปลี่ยนเป็นการกดปุ่ม หรือทาบ RFID ได้ทีหลัง)
  mainScoreCorrect++;
  
  // สร้างแพ็กเกจข้อมูลรูปแบบ "ถูก,ผิด" เช่น "1,0"
  String dataPacket = String(mainScoreCorrect) + "," + String(mainScoreWrong);
  
  // ส่งออกไปหา ESP Display
  Serial2.println(dataPacket);
  Serial.print("ส่งคะแนนไปแล้ว: ");
  Serial.println(dataPacket);

  delay(3000); // รอ 3 วินาที

  // จำลองเหตุการณ์: มีคนตอบผิด
  mainScoreWrong++;
  dataPacket = String(mainScoreCorrect) + "," + String(mainScoreWrong);
  Serial2.println(dataPacket);
  Serial.print("ส่งคะแนนไปแล้ว: ");
  Serial.println(dataPacket);
  
  delay(3000); // รอ 3 วินาที
}