TridentTD_LineNotify
============
[TridentTD] Manabu's Esp8266 IoT Library
---------------------------------------------
  
TridentTD_LineNotify เป็นไลบรารี่สำหรับส่งเตือนเข้า Line Notify
โดยสามารถใช้ได้กับ ESP8266 และ ESP32    
สามารถส่งได้ทั้ง ข้อความ สติ๊กเกอร์ และ รูปภาพด้วย URL ได้  
ความสามารถในการส่ง หากส่งไม่สำเร็จจะพยายามส่งให้ใหม่อัตโนมัติ 3 ครั้ง 

ตัวอย่างการส่ง  
--------------
 วิธีใช้จะค่อนข้างง่าย  
 หากส่งข้อความ ใช้คำสั่ง LINE.notify( .... );  
 หากส่งสติ๊กเกอร์ ใช้คำสั่ง LINE.notifySticker( .... );  
 โดยสามารถเลือกสติ๊กเกอร์ได้จาก https://devdocs.line.me/files/sticker_list.pdf  
 หากส่งรูปภาพด้วย URL ใช้คำสั่ง LINE.notifyPicture( .... );  
  
 โดยการส่งค่าไปยัง LINE สำเร็จฟังกชั่นจะคืนค่าเป็น true หากไม่สำเร็จจะคืนค่าเป็น false คืนกลับมาให้  

  ![Example_01.png](Example_01.png)

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
2.0    เพิ่มความสามารถส่ง ข้อความ สติ๊กเกอร์ และ รูปภาพได้  
2.1    ปรับโคดให้มีขนาดเล็กลง กระทัดรัดขึ้น
