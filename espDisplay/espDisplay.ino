#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); 

// ==========================================
// ตัวแปรเก็บคะแนนของเกม
// ==========================================
int scoreCorrect = 0; // คะแนนตอบถูก
int scoreWrong = 0;   // คะแนนตอบผิด

// ฟังก์ชันสำหรับแสดงคะแนนที่จอ 6 และ 7 บรรทัดล่างสุด
void showScoreDisplay() {
  // สร้างข้อความ
  String sText = "SCORE: " + String(scoreCorrect);
  String wText = "WRONG: " + String(scoreWrong);

  // เติมช่องว่างด้านหลังให้ครบ 16 ตัวอักษร (เพื่อเคลียร์ข้อความเก่าทิ้งเวลาตัวเลขลดลง)
  while(sText.length() < 16) sText += " ";
  while(wText.length() < 16) wText += " ";

  // สั่งพิมพ์ลงบรรทัดที่ 2 (Row 1) ของจอซ้ายล่าง(Ch6) และขวาล่าง(Ch7)
  printToLCD(6, 0, 1, sText);
  printToLCD(7, 0, 1, wText);
}

// ฟังก์ชันเปิดประตู MUX
void enableMUX(uint8_t channel, uint8_t mux_address) {
  Wire.beginTransmission(mux_address);
  Wire.write(1 << channel);
  Wire.endTransmission();
}

// ฟังก์ชันปิดประตู MUX (ส่งเลข 0 = ปิดทุกบาน)
void disableMUX(uint8_t mux_address) {
  Wire.beginTransmission(mux_address);
  Wire.write(0); 
  Wire.endTransmission();
}

// ฟังก์ชันเคลียร์และเปิดไฟจอทั้ง 8 จอ
void initAllLCDs() {
  for(int i = 0; i < 8; i++) {
    enableMUX(i, 0x70);
    lcd.init();
    lcd.backlight();
    lcd.clear();
    disableMUX(0x70);
  }
}

// ฟังก์ชันช่วยส่งข้อความไปจอเป้าหมาย
void printToLCD(uint8_t channel, int col, int row, String text) {
  enableMUX(channel, 0x70);
  lcd.setCursor(col, row);
  lcd.print(text);
  disableMUX(0x70);
}

void drawhouse() {
  String r0 = "  ____||____  "; 
  String r1 = " ///////////\\ "; 
  String r2 = "///////////  \\"; 
  String r3 = "|    _    |  |"; 
  String r4 = "|[] | | []|[]|"; 
  String r5 = "|   | |   |  |"; 

  printToLCD(0, 9, 1, r0.substring(0, 7));
  printToLCD(1, 0, 1, r0.substring(7, 14));
  printToLCD(2, 9, 0, r1.substring(0, 7));
  printToLCD(3, 0, 0, r1.substring(7, 14));
  printToLCD(2, 9, 1, r2.substring(0, 7));
  printToLCD(3, 0, 1, r2.substring(7, 14));
  printToLCD(4, 9, 0, r3.substring(0, 7));
  printToLCD(5, 0, 0, r3.substring(7, 14));
  printToLCD(4, 9, 1, r4.substring(0, 7));
  printToLCD(5, 0, 1, r4.substring(7, 14));
  printToLCD(6, 9, 0, r5.substring(0, 7));
  printToLCD(7, 0, 0, r5.substring(7, 14));

  // แสดงคะแนนที่ 2 จอล่างสุด
  showScoreDisplay();
}

void drawDog() {
  String r0 = "    /^-^\\     "; 
  String r1 = "   / o o \\    "; 
  String r2 = "   V\\ Y /V    "; 
  String r3 = "    / - \\     "; 
  String r4 = "   /    |     "; 
  String r5 = "  V__)__)     "; 

  printToLCD(0, 9, 1, r0.substring(0, 7));  
  printToLCD(1, 0, 1, r0.substring(7, 14)); 
  printToLCD(2, 9, 0, r1.substring(0, 7));
  printToLCD(3, 0, 0, r1.substring(7, 14));
  printToLCD(2, 9, 1, r2.substring(0, 7));
  printToLCD(3, 0, 1, r2.substring(7, 14));
  printToLCD(4, 9, 0, r3.substring(0, 7));
  printToLCD(5, 0, 0, r3.substring(7, 14));
  printToLCD(4, 9, 1, r4.substring(0, 7));
  printToLCD(5, 0, 1, r4.substring(7, 14));
  printToLCD(6, 9, 0, r5.substring(0, 7));
  printToLCD(7, 0, 0, r5.substring(7, 14));

  // แสดงคะแนนที่ 2 จอล่างสุด
  showScoreDisplay();
}
// ==========================================

// ==========================================
// ฟังก์ชันถมดำทุกช่องด้วยสี่เหลี่ยมทึบ (■)
// ==========================================
void fillAllBlocks() {
  // 1. สร้างข้อความที่เป็นสี่เหลี่ยมทึบยาว 16 ตัวอักษร
  String solidLine = "";
  for (int i = 0; i < 16; i++) {
    solidLine += (char)255; // รหัส 255 คือสี่เหลี่ยมทึบเต็มช่องของจอ LCD
  }

  // 2. วนลูปสั่งพิมพ์ลงไปที่บรรทัด 0 และบรรทัด 1 ของจอทั้ง 8 จอ
  for (int ch = 0; ch < 8; ch++) {
    printToLCD(ch, 0, 0, solidLine); // ถมบรรทัดบน
    printToLCD(ch, 0, 1, solidLine); // ถมบรรทัดล่าง
  }
}
// ==========================================

// ==========================================
// ฟังก์ชันถมทุกช่องบนจอ 8 จอ ด้วยตัวอักษรที่กำหนด
// ==========================================
void fillAllWithChar(char c) {
  // 1. นำตัวอักษร 1 ตัวที่รับมา สร้างเป็นข้อความยาว 16 ตัวอักษร
  String fillText = "";
  for (int i = 0; i < 16; i++) {
    fillText += c; 
  }

  // 2. วนลูปส่งข้อความนี้ไปถมทั้งบรรทัดบนและล่าง ของจอทั้ง 8 จอ
  for (int ch = 0; ch < 8; ch++) {
    printToLCD(ch, 0, 0, fillText); // ถมบรรทัดบน (Row 0)
    printToLCD(ch, 0, 1, fillText); // ถมบรรทัดล่าง (Row 1)
  }
}
// ==========================================

void setup() {
  Serial.begin(115200);
  Wire.begin(21, 22); // ปรับขาตามที่คุณใช้จริง
  disableMUX(0x70);
  disableMUX(0x71);

  initAllLCDs();

  Serial.println("Draw house function executed!");
}



void loop() {
  // 1. ตรวจสอบว่ามีข้อมูลส่งมาจากบอร์ด Main หรือไม่
  if (Serial2.available()) {
    // อ่านข้อความจนจบประโยค (เจอ \n)
    String receivedData = Serial2.readStringUntil('\n');
    receivedData.trim(); // ตัดช่องว่างขยะทิ้ง
    
    // 2. หาตำแหน่งของเครื่องหมายลูกน้ำ ','
    int commaIndex = receivedData.indexOf(',');
    
    // ถ้าเจอเครื่องหมายลูกน้ำ แปลว่าข้อมูลมาถูกฟอร์แมต
    if (commaIndex > 0) {
      // หั่นข้อความท่อนแรก (ตั้งแต่ตัวที่ 0 ถึงก่อนลูกน้ำ) -> คะแนนถูก
      String correctStr = receivedData.substring(0, commaIndex);
      // หั่นข้อความท่อนหลัง (ตั้งแต่หลังลูกน้ำไปจนจบ) -> คะแนนผิด
      String wrongStr = receivedData.substring(commaIndex + 1);
      
      // 3. แปลงข้อความเป็นตัวเลข (Integer) ไปเก็บในตัวแปรหลัก
      scoreCorrect = correctStr.toInt();
      scoreWrong = wrongStr.toInt();
      
      // 4. สั่งอัปเดตเฉพาะบรรทัดคะแนนบนจอ! (จอจะไม่กระพริบ)
      showScoreDisplay();
      
      // (Option) แจ้งเตือนผ่าน Serial Monitor ของคอมเพื่อเช็คความถูกต้อง
      Serial.print("อัปเดตคะแนนใหม่ -> ถูก: ");
      Serial.print(scoreCorrect);
      Serial.print(" | ผิด: ");
      Serial.println(scoreWrong);
    }
  }
}

