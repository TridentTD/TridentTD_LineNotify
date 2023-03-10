#include <TridentTD_LineNotify.h>
#include <SoftwareSerial.h>

#define SSID              "-------------"
#define PASSWORD          "-------------"
#define MICROBIT_RX       D1   /* NodeMCU */
#define MICROBIT_TX       D2   /* NodeMCU */

SoftwareSerial microbit(MICROBIT_RX, MICROBIT_TX); // RX, TX

void setup() {
  Serial.begin(115200);
  microbit.begin(115200);

  Serial.println("[WiFi] connecting...");
  WiFi.begin(SSID, PASSWORD);
  while(!WiFi.isConnected()) delay(400);
  Serial.print("[WiFi] connected. IP : ");
  Serial.println(WiFi.localIP());
}

void loop() {
  if (microbit.available()) {
    String data = microbit.readStringUntil('\n');
    // Separate token and message
    int commaIndex = data.indexOf(',');
    if (commaIndex >= 0) {
      String token = data.substring(0, commaIndex);
      String message = data.substring(commaIndex + 1);
      Serial.print("Token: ");  Serial.println(token);
      Serial.print("Message: ");Serial.println(message);
      LINE.setToken(token);
      LINE.notify(message);
    }
  }
}

/****************************************************
 * micro:bit :
 *     P0 <---> D1  NodeMCU
 *     P1 <---> D2  NodeMCU
 *
 ****************************************************/
/* 

// [typescript]

serial.redirect(
    DigitalPin.P0,
    DigitalPin.P1,
    BaudRate.BaudRate115200
)

function LINE_Notify(token: string, message: string): void {
    let data = token + "," + message
    serial.writeLine(data)
}

// Call the function with updated token and message parameters
let token = "----------------------------"
let message = "Hello, LINE Notify!"
LINE_Notify(token, message)


*/
