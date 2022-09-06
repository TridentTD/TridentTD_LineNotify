/************************************
 * ตัวอย่าง ตั้งเวลาส่ง LINE ทุกๆ 10 วินาที
 ************************************/

#include <TridentTD_LineNotify.h>
#include "src/BlynkGO_Duino.h"

#define SSID          "----------"
#define PASSWORD      "----------"
#define LINE_TOKEN    "----------"

GTimerDuino  timer;

void setup() {
  Serial.begin(115200); Serial.println();
  while(!WiFi.isConnected()) delay(400);
  Serial.println(WiFi.localIP());

  LINE.setToken(LINE_TOKEN);

  timer.setInterval(10000, [](){
    if(!WiFi.isConnected()) return;
    Serial.println("[LINE] notify...");
    LINE.notify("Hello LineNotify");
  });
}

void loop() {
  timer.loop();
}
