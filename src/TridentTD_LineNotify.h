/*
 [TridentTD] : TridentTD's Esp8266 IoT Library

 TridentTD_LineNotify.h - A simple way to send LINE NOTIFY

 Version 1.0   03/04/2560 Buddhism Era  (2017)  by TridentTD
 Version 1.1   15/02/2561 Buddhism Era  (2018)  by TridentTD
 Version 2.0   17/04/2561 Buddhism Era  (2018)  add notifySticker()  and notifyPicure() by TridentTD
 Version 2.1   17/04/2561 Buddhism Era  (2018)  clean up code for smaller code  by TridentTD
 Version 2.2   20/07/2561 Buddhism Era  (2018)  add notify(number) by TridentTD
 Version 2.3   rename DEBUG_PRINT
 Version 2.4   06/01/2562 Buddhism Era  (2019)  support 2.3.0, 2.4.0, 2.4.1, 2.4.2, 2.5.0-rc1, 2.5.0-rc2 ...  by TridentTD
 Version 3.0   10/01/2562 Buddhism Era  (2019)  support send by imageFile and imageData
 Version 3.0.1 18/06/2562 Buddhism Era  (2019)  cleanup '\n' code message ending when sending message
 
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



#ifndef _TRIDENTTD_LINENOTIFY_H_
#define _TRIDENTTD_LINENOTIFY_H_

#include <Arduino.h>
#if defined(ESP8266)
  #include <ESP8266WiFi.h>
  #include <FS.h>
#elif defined (ESP32)
  #include <WiFi.h>
  #include <WiFiClientSecure.h>
  #include <FS.h>
  #include <SPIFFS.h>
#endif
//#define  LINENOTIFY_DEBUG_MODE

#ifdef LINENOTIFY_DEBUG_MODE
    #define TD_DEBUG_PRINTER Serial
    #define TD_DEBUG_PRINT(...) { DEBUG_PRINTER.print(__VA_ARGS__); }
    #define TD_DEBUG_PRINTLN(...) { DEBUG_PRINTER.println(__VA_ARGS__); }
#else
    #define TD_DEBUG_PRINT(...) { }
    #define TD_DEBUG_PRINTLN(...) { }
#endif

class TridentTD_LineNotify {
  public:
    TridentTD_LineNotify()              { }
    TridentTD_LineNotify(String token)  { _token = token; }

    String  getVersion();

    void    setToken(String token)      { _token = token; }
    void    setToken(const char* token) { _token = token; }

    // LINE notify ด้วย ข้อความ
    bool    notify(const char* message);
    bool    notify(String message);

    // LINE notify ด้วย ตัวเลข 
    bool    notify(float value, uint8_t decimal = 2);
    bool    notify(int value);

    // LINE notify ด้วย 
    bool    notifySticker(String message, int StickerPackageID, int StickerID);
    bool    notifySticker(int StickerPackageID, int StickerID);

    // ส่ง รูปขึ้น LINE ด้วย url บนรูปบน Internet
    bool    notifyPicture(String message, String picture_url);
    bool    notifyPicture(String picture_url);

    // ส่ง รูปขึ้น LINE ด้วย file รูปภาพ (jpg/png) ที่อยู่บน SD หรือ SPIFFS ของ ESP8266/ESP32
    bool    notifyPicture(String message, fs::FS &fs, String path);
    bool    notifyPicture(fs::FS &fs, String path);

    // ส่ง รูปขึ้น LINE ด้วย image data  ESP8266/ESP32
    bool    notifyPicture(String message, uint8_t* image_data, size_t image_size);
    bool    notifyPicture(uint8_t* image_data, size_t image_size);

  private:
    float   _version = 3.01;
    String  _token;
    // bool		_notify(String message, int StickerPackageID=0, int StickerID=0, String picture_url="");
    bool        _notify(String message, int StickerPackageID=0, int StickerID=0, String picture_url="", fs::FS &fs=SPIFFS , String path="", uint8_t* image_data=NULL, size_t image_size=0);
};

extern TridentTD_LineNotify LINE;

#endif 
/* _TRIDENTTD_LINENOTIFY_H_ */
