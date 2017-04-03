/*

 [TridentTD] : MANABU's Esp8266 IoT Library
 www.facebook.com/miniNodeMCU
 
 TridentTD_LineNotify.h - A simple client for UBIDOTS

 Version 1.0.0  03/04/2560 Buddism Era  (2017)
 

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
TridentTD_LineNotify::TridentTD_LineNotify(char* token){
  _token = token;

}

bool TridentTD_LineNotify::notify(String message){
  if(WiFi.status() != WL_CONNECTED){ return -1; }

  // String author = String("Bearer ") + _token;
  // DEBUG_PRINTLN(author);
  
  //------------ Line Notify API ----------------------------
  //POST https://notify-api.line.me/api/notify
  //Content-Type	application/x-www-form-urlencoded
  //           OR multipart/form-data
  //Authorization	Bearer <access_token>

  if (!_clientSecure.connect("notify-api.line.me", 443)) {
    Serial.println("connection LINE failed");
    return -1;   
  }

  String req = "";
  req += "POST /api/notify HTTP/1.1\r\n";
  req += "Host: notify-api.line.me\r\n";
  req += "Authorization: Bearer " + String(_token) + "\r\n";
  req += "Cache-Control: no-cache\r\n";
  req += "User-Agent: ESP8266\r\n";
  req += "Content-Type: application/x-www-form-urlencoded\r\n";
  req += "Content-Length: " + String(String("message=" + message).length()) + "\r\n";
  req += "\r\n";
  req += "message=" + message;

  _clientSecure.print(req);
  
  while(_clientSecure.connected()) {
    String line = _clientSecure.readStringUntil('\n');
    if (line == "\r") {
      return 1;
    }
    //Serial.println(line);
  }
  return 0;
}


bool TridentTD_LineNotify::wificonnect(char* ssid, char* pass){
  WiFi.begin(ssid, pass);

  Serial.println();
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("WiFi connected");
  Serial.print("IP address: "); Serial.println(WiFi.localIP());

}

String TridentTD_LineNotify::getVersion(){
  return _version;
}