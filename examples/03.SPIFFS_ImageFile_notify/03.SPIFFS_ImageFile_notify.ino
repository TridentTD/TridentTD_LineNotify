/*
 * ตัวอย่างนี้ สำหรับ ESP8266 และ ESP32 
 * สำหรับส่ง รูปภาพที่เก็บอยู่บน SPIFFS
 */

#include <TridentTD_LineNotify.h>

#define SSID        "--------------------"
#define PASSWORD    "--------------------"
#define LINE_TOKEN  "--------------------"

void setup() {
  Serial.begin(115200); Serial.println();
  Serial.println(LINE.getVersion());

  if(!SPIFFS.begin()){
    Serial.println("[SPIFFS] error : SPIFFS Mount Failed");
    return;
  }
  
  WiFi.begin(SSID, PASSWORD);
  Serial.printf("WiFi connecting to %s\n",  SSID);
  while(WiFi.status() != WL_CONNECTED) { Serial.print("."); delay(400); }
  Serial.printf("\nWiFi connected\nIP : ");
  Serial.println(WiFi.localIP());

  LINE.setToken(LINE_TOKEN);

  // ส่งรูป tiger.jpg ที่อยู่บน SPIFFS ที่เตรียมไว้ ส่งไปยัง Line Notify
  LINE.notifyPicture("Hello My Tiger", SPIFFS, "/tiger.jpg");  // ใช้ได้ทั้ง ESP8266 และ ESP32
  
}

void loop() {
  // put your main code here, to run repeatedly:

}

