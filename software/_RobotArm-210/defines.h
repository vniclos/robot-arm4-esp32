#ifndef _DEFINES_H
#define _DEFINES_H
// ================================================================
// DEFINES
// ================================================================
#define WS_STATIC_IP   // WS_STATIC_IP definir para pruebas ip statica
#define PIN_LED_INT  2 //LED_BUILTIN
#define BUILTIN_LED  2  // backward compatibility

#define PIN_BUZER 12

// Recommended PWM GPIO pins on the ESP32 include 2,4,12-19,21-23,25-27,32-33
#define SERVO_COUNT  4
#define PIN_SERVO_0  18 //23     // chekeado ok
#define PIN_SERVO_1  19 //22     // IN1 on the ULN2003 driver 1  23 22 19 18
#define PIN_SERVO_2  22 //19     // IN1 on the ULN2003 driver 1
#define PIN_SERVO_3  23 //18    // IN1 on the ULN2003 driver 1

#define TIMMER_INTERVAL  1000000
//#define MOTOR_INTERVAL 1000000 // un segundo timmer  
//#define MOTOR_INTERVAL 10000000 // diez segundos
//#define MOTOR_INTERVAL 20000000 // diez segundos
//#define MOTOR_INTERVAL 60000000 // MINUTO

#define WIFIMODE_WS 1 // 1 workstation, 2= accesspoint
#define WIFIMODE_AP 2 // 1 workstation, 2= accesspoint

#endif
