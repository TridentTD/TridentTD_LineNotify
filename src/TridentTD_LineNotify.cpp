/*

 [TridentTD] : MANABU's Esp8266 IoT Library
 www.facebook.com/miniNodeMCU
 
 TridentTD_LineNotify.h - A simple client for UBIDOTS

 Version 1.0  03/04/2560 Buddism Era  (2017)
 Version 1.1  15/02/2561 Buddism Era  (2018)

Copyright (c) 2016 TridentTD

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "TridentTD_LineNotify.h"

/**
 * Constructor.
 */
TridentTD_LineNotify::TridentTD_LineNotify(){
}


TridentTD_LineNotify::TridentTD_LineNotify(String token){
  _token = token;
}

bool TridentTD_LineNotify::notify(String message){
  if(WiFi.status() != WL_CONNECTED) return false;
  if(_token == "") return false;
  
  //------------ Line Notify API ----------------------------
  //POST https://notify-api.line.me/api/notify
  //Content-Type	application/x-www-form-urlencoded
  //           OR multipart/form-data
  //Authorization	Bearer <access_token>

  WiFiClientSecure _clientSecure;

  if (!_clientSecure.connect("notify-api.line.me", 443)) {
    DEBUG_PRINT("connection LINE failed");
    return false;   
  }

  String body = "message=" + message;
  String req = "";
  req += "POST /api/notify HTTP/1.1\r\n";
  req += "Host: notify-api.line.me\r\n";
  req += "Authorization: Bearer " + _token + "\r\n";
  req += "Cache-Control: no-cache\r\n";
  req += "User-Agent: ESP8266\r\n";
  req += "Connection: close\r\n";
  req += "Content-Type: application/x-www-form-urlencoded\r\n";
  req += "Content-Length: " + String(body.length()) + "\r\n";
  req += "\r\n";
  req += body;

  bool Success_h = false;
  uint8_t line_try=3;  //เพิ่มหากส่งไม่สำเร็จ จะให้ลงใหม่ 3 หน
  while(!Success_h && line_try-- >0) {
    _clientSecure.print(req);
      
    while(_clientSecure.connected() && Success_h == false) {
      String line = _clientSecure.readStringUntil('\n');
      if (line == "\r") Success_h = true;
      DEBUG_PRINTLN(line);
    }
    delay(10);
  }
  _clientSecure.peek();
  _clientSecure.stop();

  // Serial.printf("[LineNotify] %s : \"%s\"\n", Success_h? "SENT OK":"SENT FAIL", message.c_str());

  return Success_h;
}

bool TridentTD_LineNotify::notify(const char* message){
  return notify(String(message));
}

bool TridentTD_LineNotify::notify(int number){
  return notify(String(number));
}

bool TridentTD_LineNotify::notify(float f, int decimal){
  return notify(String(f,decimal));
}

bool TridentTD_LineNotify::notify(String token, String message){
  if( token =="") return false;
  _token = token;
  return notify(message);
}


bool TridentTD_LineNotify::wificonnect(char* ssid, char* pass){
  WiFi.begin(ssid, pass);
  
  DEBUG_PRINTLN();
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    DEBUG_PRINT(".");
  }
  DEBUG_PRINTLN();
  DEBUG_PRINTLN("WiFi connected");
  DEBUG_PRINT("IP address: ");
  DEBUG_PRINTLN(WiFi.localIP());

}

String TridentTD_LineNotify::getVersion(){
  return (String)("[TridentTD_LineNotify] Version ") + String(_version);
}

TridentTD_LineNotify LINE;
