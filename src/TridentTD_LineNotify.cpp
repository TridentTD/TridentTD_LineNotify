/*
 [TridentTD] : TridentTD's Esp8266 IoT Library

 TridentTD_LineNotify.cpp - A simple way to send LINE NOTIFY

 Version 1.0  03/04/2560 Buddism Era  (2017)
 Version 1.1  15/02/2561 Buddism Era  (2018)
 Version 2.0  17/04/2561 Buddism Era  (2018)  add notifySticker()  and notifyPicure()
 Version 2.1  17/04/2561 Buddism Era  (2018)  clean up code for smaller code

Copyright (c) 2016-2018 TridentTD

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

#if defined(ESP8266)
#define USER_AGENT     "ESP8266"
#elif defined (ESP32)
#define USER_AGENT     "ESP32"
#endif

String TridentTD_LineNotify::getVersion(){
  return (String)("[TridentTD_LineNotify] Version ") + String(_version);
}

bool TridentTD_LineNotify::notify(String message){
  return _notify(message);
}

bool TridentTD_LineNotify::notify(const char* message){
  return _notify(String(message));
}

bool TridentTD_LineNotify::notifySticker(int StickerPackageID, int StickerID){
  if( StickerPackageID <=0 || StickerID <=0 ) return false;
  return _notify("", StickerPackageID, StickerID);
}

bool TridentTD_LineNotify::notifySticker(String message, int StickerPackageID, int StickerID) {
  if( StickerPackageID <=0 || StickerID <=0 ) return false;
  return _notify(message, StickerPackageID, StickerID);
}

bool TridentTD_LineNotify::notifyPicture(String picture_url) {
  if( picture_url == "") return false;
  return _notify("", 0,0, picture_url);
}

bool TridentTD_LineNotify::notifyPicture(String message, String picture_url) {
  if( picture_url == "") return false;
  return _notify(message, 0,0, picture_url);
}

bool TridentTD_LineNotify::_notify(String message, int StickerPackageID, int StickerID, String picture_url){
  if(WiFi.status() != WL_CONNECTED) return false;
  if(_token == "") return false;
  
  WiFiClientSecure _clientSecure;

  if (!_clientSecure.connect("notify-api.line.me", 443)) {
    DEBUG_PRINT("connection LINE failed");
    return false;   
  }

  int httpCode = 404;

  String boundary = "----TridentTD_LineNotify--";
  String body = "--" + boundary + "\r\n";
        body += "Content-Disposition: form-data; name=\"message\"\r\n\r\n" + message + " \r\n";
      if( StickerPackageID > 0 && StickerID > 0) {
        body += "--" + boundary + "\r\n";
        body += "Content-Disposition: form-data; name=\"stickerPackageId\"\r\n\r\n" + String(StickerPackageID) + "\r\n";
        body += "--" + boundary + "\r\n";
        body += "Content-Disposition: form-data; name=\"stickerId\"\r\n\r\n" + String(StickerID) + "\r\n";
      }
      if( picture_url != "") {
        body += "--" + boundary + "\r\n";
        body += "Content-Disposition: form-data; name=\"imageThumbnail\"\r\n\r\n" + picture_url + "\r\n";
        body += "--" + boundary + "\r\n";
        body += "Content-Disposition: form-data; name=\"imageFullsize\"\r\n\r\n" + picture_url + "\r\n";
      }
        body += "--" + boundary + "--";

  String req = "POST /api/notify HTTP/1.1\r\n";
        req += "Host: notify-api.line.me\r\n";
        req += "Authorization: Bearer " + _token + "\r\n";
        req += "User-Agent: " + String(USER_AGENT) + "\r\n";
        req += "Connection: close\r\n";
        req += "Cache-Control: no-cache\r\n";
        req += "Content-Length: " + String(body.length()) + "\r\n";
        req += "Content-Type: multipart/form-data; boundary=" + boundary + "\r\n\r\n";
        req += body;

  bool Success_h = false;
  uint8_t line_try=3;  //เพิ่มหากส่งไม่สำเร็จ จะให้ลงใหม่ 3 หน
  while(!Success_h && line_try-- > 0) {
    _clientSecure.print(req);
    while( _clientSecure.connected() && !_clientSecure.available()) delay(10);
    if( _clientSecure.connected() && _clientSecure.available() ) {
      String resp = _clientSecure.readStringUntil('\n');
      httpCode    = resp.substring(resp.indexOf(" ")+1, resp.indexOf(" ", resp.indexOf(" ")+1)).toInt();
      Success_h   = (httpCode==200);
      DEBUG_PRINTLN(resp);
    }
    delay(10);
  }
  _clientSecure.stop();

  return Success_h;
}

TridentTD_LineNotify LINE;
