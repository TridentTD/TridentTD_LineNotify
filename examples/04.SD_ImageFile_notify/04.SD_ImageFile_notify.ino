/*
 * ตัวอย่างนี้ สำหรับ ESP32 เท่านั้น
 * สำหรับส่ง รูปที่อยู่บน SD
 * 
 * SD Card | ESP32
 *    D2       -
 *    D3       SS
 *    CMD      MOSI
 *    VSS      GND
 *    VDD      3.3V
 *    CLK      SCK
 *    VSS      GND
 *    D0       MISO
 *    D1       -
 */

#include <TridentTD_LineNotify.h>
#include <SD.h>

#define SSID        "--------------------"
#define PASSWORD    "--------------------"
#define LINE_TOKEN  "--------------------"

void setup() {
  Serial.begin(115200); Serial.println();
  Serial.println(LINE.getVersion());

  if(!SD.begin()){
    Serial.println("[SD] error : SD Card Mount Failed");
    return;
  }
  
  WiFi.begin(SSID, PASSWORD);
  Serial.printf("WiFi connecting to %s\n",  SSID);
  while(WiFi.status() != WL_CONNECTED) { Serial.print("."); delay(400); }
  Serial.printf("\nWiFi connected\nIP : ");
  Serial.println(WiFi.localIP());  

  LINE.setToken(LINE_TOKEN);

  // ส่งรูป tiger.jpg ที่อยู่บน SD ที่เตรียมไว้ ส่งไปยัง Line Notify
  LINE.notifyPicture("Hello My Tiger", SD, "/tiger.jpg");   // สำหรับ ESP32 เท่านั้น
  
}

void loop() {

}

