// web server handle manager function 

#ifndef _WEB_HANDLE_H
#define _WEB_HANDLE_H
#include "defines.h"
#include "web_root.h"
#include "web_js.h"
#include "web_css.h"
#include "ESP32_Servo.h"
#include "debug.h"
//extern WebServer g_server;
extern AutoConnect portal;
extern Servo g_servos[SERVO_COUNT];;
extern int   g_posGo[SERVO_COUNT];;
extern int   g_posAct[SERVO_COUNT];
extern  bool   g_IsMoving[SERVO_COUNT];
extern String g_msg_html;
extern  void  fncDoit_takeaway(int steep);
extern void fnctakeawayopen();
extern void fnctakeawayclose();
extern void fnctakeawayleft();
extern void fnctakeawayright();
extern void fnctakeawaycenter();
// =================================================
// void handleROOT()
// =================================================
void handleROOT() {
  // Serial.println("handleRoot");
  digitalWrite(PIN_LED_INT, 1);
  portal.host().send(200, "text/html", g_HTML_Web_root);
  //g_server.send(200, "text/html", g_HTML_Web_root);
  digitalWrite(PIN_LED_INT, 0);
}
// ======================================================
//
// ========================================================
void handleJS() {
  Serial.println("handleJS");
  digitalWrite(PIN_LED_INT, 1);
  portal.host().send(200, "application/javascript", g_HTML_Web_JS);

  digitalWrite(PIN_LED_INT, 0);
}
// ==============================================
void handleCSS() {
  Serial.println("handleCSS");
  digitalWrite(PIN_LED_INT, 1);
  portal.host().send(200, "text/css", g_HTML_Web_CSS);

  digitalWrite(PIN_LED_INT, 0);
}

// =================================================
// =================================================


// =============================================================

// =================================================
// =================================================
void handleNotFound() {
  digitalWrite(PIN_LED_INT, 1);
  WebServerClass& g_server = portal.host();
  String message = "<h1>OOPS</h1>File Not Found\n\n";
  message += "URI: ";
  message += g_server.uri();
  message += "\nMethod: ";
  message += (g_server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += g_server.args();
  message += "\n";







  for (uint8_t i = 0; i < g_server.args(); i++) {
    message += " " + g_server.argName(i) + ": " + g_server.arg(i) + "\n";
  }
  portal.host().send(404, "text/html", message);
  //g_server.send(404, "text/plain", message);
  digitalWrite(PIN_LED_INT, 0);
}
void handleGETPOSITION()
{
  digitalWrite(PIN_LED_INT, 1);
  Serial.println("handleGetPosition");
  String msg = "";
  int iPos = 0;
  for (int i = 0; i < SERVO_COUNT; i++) {
    iPos = g_servos[i].read();
    msg += String(iPos) + ",";
  }
  portal.host().send(200, "text/plain", msg);
  digitalWrite(PIN_LED_INT, 0);

}
void  handleGETSTATUS()
{
  digitalWrite(PIN_LED_INT, 1);
  Serial.println("handleGETSTATUS");
  String msg = "";
  int iPos = 0;
  for (int i = 0; i < SERVO_COUNT; i++) {

    iPos = g_servos[i].read();
    msg += +"</br>Motor " + String(i) + " Position: " + String(iPos);

  }
  portal.host().send(200, "text/html", msg);
  //g_server.send(200, "text/html", msg);
  digitalWrite(PIN_LED_INT, 0);

}
// =================================================================
// =================================================================
void handleRESET()
{
  digitalWrite(PIN_LED_INT, 1);
  Serial.println("handleRESET");
  String msg = "Reseting, please wait";

  portal.host().send(200, "text/html", msg);
  //g_server.send(200, "text/html", msg);

  delay(1000);
  digitalWrite(PIN_LED_INT, 0);
  ESP.restart();
}

void handleMOTORSET() {
  digitalWrite(PIN_LED_INT, 1);
  Serial.println("handleMOTORSET");
  String msg = "";
  int idMotor = -999;
  int iPosGo = -999;
  bool bOk = true;
  String message = "";


  WebServerClass& g_server = portal.host();
  for (int i = 0; i < g_server.args(); i++) {

    message += "Arg nº" + (String)i + " –- ";
    message += g_server.argName(i) + ": ";
    message += g_server.arg(i) + "\n";

  }
  Serial.println(message);
  if ( g_server.hasArg("m") ) {
    idMotor = g_server.arg("m").toInt();

  } else {
    bOk = false;
  }
  if ( g_server.hasArg("p") ) {
    iPosGo = g_server.arg("p").toInt();
    g_posGo[idMotor] = iPosGo;


  } else {
    bOk = false;
  }
  if (!bOk)
  {
    msg += "Oops: Move motor " +  g_server.arg("m") + " From pos=" + g_posAct[idMotor]  + " to pos=" + g_posGo[idMotor];
    Serial.println(msg);
    g_server.send(200, "text/html", msg);
    digitalWrite(PIN_LED_INT, 0);
    return;
  }


  g_posGo[idMotor] = iPosGo;
  msg += "Ok: Move motor " + g_server.arg("m") + " From pos=" + g_posAct[idMotor]  + " to pos=" + g_posGo[idMotor];
  Serial.println(msg);

  portal.host().send(200, "text/html", msg);

  digitalWrite(PIN_LED_INT, 0);
}



void handleTAKEAWAYLEFT()
{
  digitalWrite(PIN_LED_INT, 1);
  String msg = "LEFT";
  fnctakeawayleft();
  WebServerClass& g_server = portal.host();
  portal.host().send(200, "text/html", msg);
  digitalWrite(PIN_LED_INT, 0);
}

void handleTAKEAWAYRIGHT()
{
  digitalWrite(PIN_LED_INT, 1);
  String msg = "Open";
  fnctakeawayright();
  WebServerClass& g_server = portal.host();
  portal.host().send(200, "text/html", msg);
  digitalWrite(PIN_LED_INT, 0);
}

void handleTAKEAWAYCENTER()
{
  digitalWrite(PIN_LED_INT, 1);
  String msg = "Open";
  fnctakeawaycenter();
  WebServerClass& g_server = portal.host();
  portal.host().send(200, "text/html", msg);
  digitalWrite(PIN_LED_INT, 0);
}



void handleTAKEAWAYOPEN()
{
  digitalWrite(PIN_LED_INT, 1);
  String msg = "Open";
  fnctakeawayopen();
  WebServerClass& g_server = portal.host();
  portal.host().send(200, "text/html", msg);
  digitalWrite(PIN_LED_INT, 0);
}

void handleTAKEAWAYCLOSE()
{
  digitalWrite(PIN_LED_INT, 1);
  String msg = "Close";
  fnctakeawayclose();
  WebServerClass& g_server = portal.host();
  portal.host().send(200, "text/html", msg);
  digitalWrite(PIN_LED_INT, 0);
}


void handleTAKEAWAY()
{
  digitalWrite(PIN_LED_INT, 1);
  String msg = "";
  WebServerClass& g_server = portal.host();
  if ( g_server.hasArg("m") ) {

    int steep = g_server.arg("m").toInt();
    fncDoit_takeaway(steep);
    msg = "Doing takeaway num." + String(steep);
  } else {
    msg = "bad order";
  }


  portal.host().send(200, "text/html", msg);
  digitalWrite(PIN_LED_INT, 0);

}
void handleDEBUG()
{
  digitalWrite(PIN_LED_INT, 1);
  portal.host().send(200, "text/html", g_msg_html);
  digitalWrite(PIN_LED_INT, 0);
}

#endif _WEB_HANDLE_H
