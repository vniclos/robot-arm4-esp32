#ifndef _DEBUG_H
#define _DEBUG_H
#include "defines.h"
#include "web_root.h"
#include "web_js.h"
#include "web_css.h"
#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include <Arduino.h>
#include "AutoConnect.h"
extern AutoConnect portal;

extern Servo g_servos[SERVO_COUNT];;
extern int  g_posGo[SERVO_COUNT];;
extern int g_posAct[SERVO_COUNT];
extern  bool   g_IsMoving[SERVO_COUNT];;


extern void fncMsg(String Title, long Value);
extern void fncMsg(String Title, String Value);

extern int g_wifimode ;
extern char g_wifiWS_Ssid[15] ;
extern const char *g_wifiWS_Pwd ;
extern  char g_HostName[15] ;
extern char  g_WifiAp_Ssid[15]; //Create a Unique AP from MAC address
extern const char *g_WifiAP_Pwd ;
extern const char *g_wifiWS_Pwd ;



//
// ================================================================
// fncDebugMove();
// ================================================================
void fncDebugMove()
{

Serial.println("--------------");

for (int i=0; i<SERVO_COUNT;i++)
{
  Serial.println("Pos Act Motor "+ String(i)+" ="+ String(g_posAct[4]));
  Serial.println("Pos go Motor "+ String(i)+" ="+ String(g_posGo[4]));
  }
}

// =================================================
// =================================================
void fncDebugSetup() {
   Serial.println("-----------------");
   Serial.println("-----  SETUP ----");
   Serial.println("-----------------");
   Serial.println("ChipId ");
   Serial.print("PIN_LED_INT:");
   Serial.println(PIN_LED_INT);
    fncDebugMove();
   Serial.println("-----------------");
   
}
#endif
