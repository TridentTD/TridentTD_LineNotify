/************************************
 * ตัวอย่าง กดปุ่มแล้วส่ง LINE 
 *   โดยไม่เกิดการส่ง LINE รัวๆ
 ************************************/

#include <TridentTD_LineNotify.h>
#include "src/BlynkGO_Duino.h"

#define SSID          "----------"
#define PASSWORD      "----------"
#define LINE_TOKEN    "----------"

HWButton button = 5;

void setup() {
  Serial.begin(115200); Serial.println();
  while(!WiFi.isConnected()) delay(400);
  Serial.println(WiFi.localIP());

  LINE.setToken(LINE_TOKEN);

  button.onPressed([](HWButton*btn){
    if(!WiFi.isConnected()) return;
    Serial.println("[LINE] notify...");
    LINE.notify("Hello LineNotify");
  });
}

void loop() {
  button.loop();
}
