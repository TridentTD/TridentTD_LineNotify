/*
 [TridentTD] : TridentTD's Esp8266 IoT Library

 TridentTD_LineNotify.cpp - A simple way to send LINE NOTIFY

 Version 1.0  03/04/2560 Buddism Era  (2017)  by TridentTD
 Version 1.1  15/02/2561 Buddism Era  (2018)  by TridentTD
 Version 2.0  17/04/2561 Buddism Era  (2018)  add notifySticker()  and notifyPicure() by TridentTD
 Version 2.1  17/04/2561 Buddism Era  (2018)  clean up code for smaller code  by TridentTD
 Version 2.2  20/07/2561 Buddism Era  (2018)  add notify(number) by TridentTD
 Version 2.3  rename DEBUG_PRINT
 Version 2.4  06/01/2562 Buddism Era  (2019)  support 2.3.0, 2.4.0, 2.4.1, 2.4.2, 2.5.0-rc1, 2.5.0-rc2 ...  by TridentTD
 Version 3.0  10/01/2562 Buddhism Era  (2019)  support send by imageFile and imageData
 
Copyright (c) 2016-2019 TridentTD

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
// #include <FS.h>

#if defined(ESP8266)
#define USER_AGENT     "ESP8266"
#include <core_version.h>
#if !defined(ARDUINO_ESP8266_RELEASE_2_3_0) &&  !defined(ARDUINO_ESP8266_RELEASE_2_4_0) && !defined(ARDUINO_ESP8266_RELEASE_2_4_1)
#include <WiFiClientSecureAxTLS.h>
#endif
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


bool TridentTD_LineNotify::notify(float value, uint8_t decimal){
  return _notify(String(value, decimal));
}

bool TridentTD_LineNotify::notify(int value){
  return _notify(String(value));
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

bool TridentTD_LineNotify::notifyPicture(String message, fs::FS &fs, String path){
  return _notify(message, 0,0, "", fs, path);
}

bool TridentTD_LineNotify::notifyPicture(fs::FS &fs, String path){
  return _notify("", 0,0, "", fs, path);
}

bool TridentTD_LineNotify::notifyPicture(String message, uint8_t* image_data, size_t image_size) {
  return _notify(message, 0,0, "", SPIFFS, "", image_data, image_size);
}

bool TridentTD_LineNotify::notifyPicture(uint8_t* image_data, size_t image_size) {
  return _notify("", 0,0, "", SPIFFS, "", image_data, image_size);
}

bool TridentTD_LineNotify::_notify(String message, int StickerPackageID, int StickerID, String picture_url, fs::FS &fs, String path, uint8_t* image_data, size_t image_sz){
  if(WiFi.status() != WL_CONNECTED) return false;
  if(_token == "") return false;

#if defined(ESP8266)
#if !defined(ARDUINO_ESP8266_RELEASE_2_3_0) &&  !defined(ARDUINO_ESP8266_RELEASE_2_4_0) && !defined(ARDUINO_ESP8266_RELEASE_2_4_1)
  axTLS::WiFiClientSecure _clientSecure;
#else
  WiFiClientSecure _clientSecure;
#endif
#elif defined (ESP32)
  WiFiClientSecure _clientSecure;
#endif

  if (!_clientSecure.connect("notify-api.line.me", 443)) {
    TD_DEBUG_PRINT("connection LINE failed");
    return false;   
  }

  int httpCode = 404;
  size_t image_size = 0;
  File image_file;

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
      if( path != ""){
        if( fs.exists(path)) {
          image_file = fs.open(path, "r");
          if( image_file) {
            image_size = image_file.size();
            body += "--" + boundary + "\r\n";
            body += "Content-Disposition: form-data; name=\"imageFile\"; filename=\"image.jpg\"\r\n"; 
            body += "Content-Type: image/jpeg\r\n\r\n";
          }
        }
      }else
      if(image_data !=NULL && image_sz > 0 ){
        image_size = image_sz;
        body += "--" + boundary + "\r\n";
        body += "Content-Disposition: form-data; name=\"imageFile\"; filename=\"image.jpg\"\r\n"; 
        body += "Content-Type: image/jpeg\r\n\r\n";
      }

  String body_end = "--" + boundary + "--\r\n";
  size_t body_length = body.length() + image_size + body_end.length();

  String header = "POST /api/notify HTTP/1.1\r\n";
        header += "Host: notify-api.line.me\r\n";
        header += "Authorization: Bearer " + _token + "\r\n";
        header += "User-Agent: " + String(USER_AGENT) + "\r\n";
        header += "Connection: close\r\n";
        header += "Cache-Control: no-cache\r\n";
        header += "Content-Length: " + String(body_length) + "\r\n";
        header += "Content-Type: multipart/form-data; boundary=" + boundary + "\r\n\r\n";

  bool Success_h = false;
  uint8_t line_try=3;  //เพิ่มหากส่งไม่สำเร็จ จะให้ลงใหม่ 3 หน
  while(!Success_h && line_try-- > 0) {
    _clientSecure.print( header + body);
    
    if(image_size>0){
      size_t BUF_SIZE = 1024;
      if( image_file ) {
        uint8_t buf[BUF_SIZE];
        size_t sz = image_size;
        while(image_file.available() && sz){
          memset(buf,0,BUF_SIZE);
          if( sz>=BUF_SIZE){
            image_file.read(buf,BUF_SIZE);
            _clientSecure.write( buf, BUF_SIZE);
            sz -=BUF_SIZE;
          }else{
            image_file.read(buf,sz); 
            _clientSecure.write( buf, sz);
            sz = 0;
          }
        }
        image_file.close();
      }else
      if( image_data !=NULL) {
        uint8_t *p = image_data;
        size_t sz = image_size;
        while( p != NULL && sz){
          if( sz>=BUF_SIZE){
            _clientSecure.write( p, BUF_SIZE);
            p += BUF_SIZE; sz -=BUF_SIZE; 
          }else{
            _clientSecure.write( p, sz);
            p += sz; sz = 0; 
          }
        }
      }
    }
    _clientSecure.print("\r\n" +body_end);

    while( _clientSecure.connected() && !_clientSecure.available()) delay(10);
    if( _clientSecure.connected() && _clientSecure.available() ) {
      String resp = _clientSecure.readStringUntil('\n');
      httpCode    = resp.substring(resp.indexOf(" ")+1, resp.indexOf(" ", resp.indexOf(" ")+1)).toInt();
      Success_h   = (httpCode==200);
      TD_DEBUG_PRINTLN(resp);
    }
    delay(10);
  }
  _clientSecure.stop();

  return Success_h;
}

TridentTD_LineNotify LINE;
