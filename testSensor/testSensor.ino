// กำหนดขา Analog ที่ต่อกับ FSR ทั้ง 5 ตัว
const int fsrPins[5] = {32, 33, 34, 35, 36}; 
int fsrValues[5]; // ตัวแปรสำหรับเก็บค่าที่อ่านได้


void setup() {
  Serial.begin(9600);
  Serial.println("--- เริ่มการทดสอบเซนเซอร์ FSR402 ทั้ง 5 ตัว ---");
  
  // ไม่ต้องใช้ pinMode สำหรับการอ่านค่า Analog (analogRead) บน ESP32
}

void loop() {
  Serial.print("ค่าแรงกด: ");
  
  // วนลูปอ่านค่าและแสดงผลทีละตัว
  for (int i = 0; i < 5; i++) {
    fsrValues[i] = analogRead(fsrPins[i]);
    Serial.print("FSR PIN ");
    Serial.print(fsrPins[i]);
    Serial.print(" : ");
    Serial.print(fsrValues[i]);
    Serial.print(" | ");
    // จัดรูปแบบให้ตัวเลขดูสวยงาม อ่านง่าย
  }

  Serial.println(); // ขึ้นบรรทัดใหม่
  delay(200); // หน่วงเวลา 0.2 วินาทีให้พออ่านทัน
}