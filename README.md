TridentTD_LineNotify
============
[TridentTD] Manabu's Esp8266 IoT Library
---------------------------------------------
  
TridentTD_LineNotify เป็นไลบรารี่สำหรับส่งเตือนเข้า Line Notify  
โดยตัวไลบรารี่จะมีระบบป้องกันหากส่งไม่ได้  
จะทำการส่งใหม่อัตโนมัติให้  

TridentTD_LineNotify is a library for  
sending message to LINE app in the simplest method.

You can use functions like this

- TridentTD_LineNotify myLINE(LINE_TOKEN);

- myLine.wificonnect( ssid,password );

- myLine.notify( message );

- myLine.getVersion();

ตัวอย่างการส่ง  
--------------
 วิธีใช้จะค่อนข้างง่าย อยากส่งอะไรส่งได้เลย  
 ไม่ว่าจะเป็นตัวแปรประเภท String, char array, int, float  
 เพียงใช้คำสั่งเดียวคือ myLINE.notify( .... );  

  ![Example01.png](Example01.png)

วิธีสร้าง Line Token
---------------------------------------------

ทำการ Log in ที่ https://notify-bot.line.me/en/

  ![Linenotify.png](Linenotify.png)



จากนั้น เข้าไปที่ https://notify-bot.line.me/my/  เพื่อทำการ สร้าง Line Token ขึ้นมา
ให้กดปุ่ม **Generate token**

![CreateLineToken.png](CreateLineToken.png)


ตั้งชื่อ Token อะไรก็ได้
พร้อมทั้งเลือก กลุ่มใน Line ที่ต้องการให้มีการแจ้งเตือนไปยังกลุ่ม

![CreateNotifyNameSelectGroup.png](CreateNotifyNameSelectGroup.png)





Version
=====

1.0.0  TridentTD_LineNotify  
1.1    เพิ่ม ให้ส่งซ้ำอัตโนมัติ หากส่งไม่ได้ 3 หน, สามารถส่งแบบตัวเลข หรือ ทศนิยมได้

