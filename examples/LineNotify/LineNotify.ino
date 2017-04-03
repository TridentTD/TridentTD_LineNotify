#include <TridentTD_LineNotify.h>

#define ssid         "----- SSID -----"
#define pass         "----- PASS -----"

#define LINE_TOKEN   "----- LINE TOKEN -----"

TridentTD_LineNotify myLINE(LINE_TOKEN);

void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.println(myLINE.getVersion());
  
  myLINE.wificonnect(ssid,pass);

  if( myLINE.notify("HELLO LINE") ) {
    Serial.println("[TridentTD LineNotify] Send OK");
  } else {
    Serial.println("[TridentTD LineNotify] Send Fail!");

  }
}

void loop() {
  // put your main code here, to run repeatedly:

}
