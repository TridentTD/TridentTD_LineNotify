#include <TridentTD_LineNotify.h>

#define SSID          "--------------------"
#define PASSWORD      "--------------------"

#define LINE_TOKEN1   "--------------------"
#define LINE_TOKEN2   "--------------------"


void setup() {
  Serial.begin(115200);
  WiFi.begin( SSID, PASSWORD );
  while(!WiFi.isConnected()) delay(400);
  Serial.println( WiFi.localIP());

  String message = "Messeage to LINE";

  LINE.setToken(LINE_TOKEN1); LINE.notify(message);
  LINE.setToken(LINE_TOKEN2); LINE.notify(message);

}

void loop() {
}

