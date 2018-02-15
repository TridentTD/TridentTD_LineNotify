#include <ESP8266WiFi.h>
#include <TridentTD_LineNotify.h>

#define ssid         "----- SSID -----"
#define pass         "----- PASS -----"

#define LINE_TOKEN   "----- LINE TOKEN -----"

TridentTD_LineNotify myLINE(LINE_TOKEN);

void setup() {
  Serial.begin(115200);
  Serial.println();
  
  WiFi.begin(ssid, pass);
  Serial.printf("WiFi connecting to %s\n", ssid);
  while(!WiFi.isConnected()) { delay(400); Serial.print(".");}
  Serial.printf("\nWiFi connected, IP : %s\n", WiFi.localIP().toString().c_str());


  /* ตัวอย่างการส่ง Line เข้ากลุ่ม*/
  myLINE.notify("HELLO LINE"); // ส่งข้อความ
  delay(2000);

  int val = 1023;
  myLINE.notify(val);           // ส่งตัวเลข

  delay(2000);
  float f_value = 10.34324469;
  myLINE.notify( f_value, 4);   // ส่งทศนิยม แสดงทศนิยม 4 ตำแหน่ง
}

void loop() {

}