# robot-arm4-esp32  controled by wifi

![alt text](https://github.com/vniclos/robot-arm4-esp32/blob/master/img/robot-00.jpg "Robot ARM4X builded")

## Harrdware

- 1 ESP32 MCU
- 4 Servo FUTABA M490S
- 1 DIP
- 1 Power suply 5v 2a
- 1 Litle 

## Software
- Arduino IDE
- Libraries
- ESP32_Servo.h
- AutoConnect.h


This toy robot is build for learn to control by wifi one simple four arm robot, they has a web server
### You can set 
You can configure as Wifi access point or connet to your wifi, and save the configuration in EEPROM, 


## Management
  In the main root page you can move each motor steep by steep or move clomplex secuences saves 
  in to arrays of integer one  is id of servo the second has the position to move like this
  ```
  if (steep == 3) {
    int  iMotor_03[] = {1,  2,   0} ;
    int iPosic_03[] = {86, 93, 180};
    fncDoit_takeaway_do(iMotor_03, iPosic_03);
  }
```


