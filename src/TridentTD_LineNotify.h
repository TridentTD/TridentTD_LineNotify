/*
 [TridentTD] : TridentTD's Esp8266 IoT Library

 TridentTD_LineNotify.h - A simple way to send LINE NOTIFY

 Version 1.0  03/04/2560 Buddism Era  (2017)
 Version 1.1  15/02/2561 Buddism Era  (2018)
 Version 2.0  17/04/2561 Buddism Era  (2018)  add notifySticker()  and notifyPicure()

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



#ifndef _TRIDENTTD_LINENOTIFY_H_
#define _TRIDENTTD_LINENOTIFY_H_

#include <Arduino.h>
#if defined(ESP8266)
  #include <ESP8266WiFi.h>
#else if defined (ESP32)
  #include <WiFi.h>
  #include <WiFiClientSecure.h>
#endif

//#define  LINENOTIFY_DEBUG_MODE

#ifdef LINENOTIFY_DEBUG_MODE
    #define DEBUG_PRINTER Serial
    #define DEBUG_PRINT(...) { DEBUG_PRINTER.print(__VA_ARGS__); }
    #define DEBUG_PRINTLN(...) { DEBUG_PRINTER.println(__VA_ARGS__); }
#else
    #define DEBUG_PRINT(...) { }
    #define DEBUG_PRINTLN(...) { }
#endif

class TridentTD_LineNotify {
  public:
    TridentTD_LineNotify();
    TridentTD_LineNotify(String token);

    String  getVersion();

    void    setToken(String token)      { _token = token; }
    void    setToken(const char* token) { _token = token; }

    bool    notify(const char* message);
    bool    notify(String message); 
    bool	  notifySticker(String message, int StickerPackageID, int StickerID);
    bool    notifySticker(int StickerPackageID, int StickerID);
    bool    notifyPicture(String message, String picture_url);
    bool    notifyPicture(String picture_url);

  private:
    float   _version = 2.0;
    String  _token;    
};

extern TridentTD_LineNotify LINE;

#endif 
/* _TRIDENTTD_LINENOTIFY_H_ */
