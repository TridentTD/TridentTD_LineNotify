TridentTD_LineNotify
============
[TridentTD] Manabu's Esp8266 IoT Library
---------------------------------------------

TridentTD_LineNotify is a library for  
sending message to LINE app in the simplest method.

You can use functions like this

- TridentTD_LineNotify myLINE(LINE_TOKEN);

- myLine.wificonnect( ssid,password );

- myLine.notify( message );

- myLine.getVersion();



วิธีสร้าง Line Token
---------------------------------------------

ทำการ Log in ที่ https://notify-bot.line.me/en/

  ![](Linenotify.png)



จากนั้น เข้าไปที่ https://notify-bot.line.me/my/  เพื่อทำการ สร้าง Line Token ขึ้นมา
ให้กดปุ่ม **Generate token**

![CreateLineToken.png](CreateLineToken.png)


ตั้งชื่อ Token อะไรก็ได้
พร้อมทั้งเลือก กลุ่มใน Line ที่ต้องการให้มีการแจ้งเตือนไปยังกลุ่ม

![CreateNotifyNameSelectGroup.png](CreateNotifyNameSelectGroup.png)





Version
=====

1.0.0  TridentTD_LineNotify
