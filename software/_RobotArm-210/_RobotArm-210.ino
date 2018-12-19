
#include <WiFi.h>
#include <WebServer.h>
#include "web_root.h"
#include "web_js.h"
#include "web_css.h"
#include "web_handle.h"
#include <ESP32_Servo.h>
#include "defines.h"
#include "debug.h"

#include "AutoConnect.h"
#include <ESPmDNS.h>

//================================================
// GLOBAL OBJECTS
//================================================
AutoConnect portal;
char g_NetHostName[8] = "robot";
// SERVO futaba s3003 Pulse Width: 500-3000 µs
//const int g_Servo_minUs = 500;
//const int g_Servo_maxUs = 3000;
//futaba mc90s https://servodatabase.com/servo/towerpro/mg90
const int  g_Servo_minUs = 400;
const int  g_Servo_maxUs = 2400;
// 3 tenaza
Servo g_servos[4];// create 4 servo object to control a servoS
int g_PIN[] = {PIN_SERVO_0,    PIN_SERVO_1,  PIN_SERVO_2, PIN_SERVO_3} ;
int g_posMin[] = {0,    70,  70, 48} ;
int g_posMax[] = {180, 170, 170, 70};
int g_posIni[] = {90,   100,  100, 50};
int g_Steep[] =  {1, 1, 1, 1}; // grados a girar en cada movimiento.
int   g_posGo[SERVO_COUNT];
int   g_posAct[SERVO_COUNT];
bool  g_IsMoving[SERVO_COUNT];
String g_msg_html = "";
//timer
bool  g_TimeLapseDoIt = false;
volatile int interruptCounter;
int InterruptCounterTotal;
hw_timer_t * timer = NULL;
portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;
//==============================
// FUNCTION DOIT
//=============================
// secuencia de manibra
void fncDoit_takeaway(int steep)
{
  // Maniobra ir a posicion inicial

  if (steep == 1) {
    int  iMotor_01[] = {0,  1,   2 } ;
    int iPosic_01[] = {88, 86, 93};
    fncDoit_takeaway_do(iMotor_01, iPosic_01);
    fnctakeawayopen();
  }


  // Maniobra ir a posicion coger

  if (steep == 2) {
    fnctakeawayopen();
    int  iMotor_02[] = {1,   2  } ;
    int iPosic_02[] = {163, 117};
    fncDoit_takeaway_do(iMotor_02, iPosic_02);
    fnctakeawayclose();
  }

  // Maniobra subir
  if (steep == 3) {
    int  iMotor_03[] = {1,  2,   0} ;
    int iPosic_03[] = {86, 93, 180};
    fncDoit_takeaway_do(iMotor_03, iPosic_03);
  }

  // bajar
  if (steep == 4) {
    int  iMotor_04[] = {1,   2  } ;
    int iPosic_04[] = {163, 117};
    fncDoit_takeaway_do(iMotor_04, iPosic_04);
    
  }

}

void fnctakeawayopen()
{
  fncServoMoveTo(3, 50);
  delay(100);
}
void fnctakeawayclose()
{
  fncServoMoveTo(3, 68);
  delay(100);
}

void fnctakeawaycenter()
{
 
    int  iMotor[] = {1,  2,   0} ;
    int iPosic[] = {86, 93, 90};
    fncDoit_takeaway_do(iMotor, iPosic);
 
  delay(100);
}
void fnctakeawayleft()
{
    int  iMotor[] = {1,  2,   0} ;
    int iPosic[] = {86, 93, 0};
    fncDoit_takeaway_do(iMotor, iPosic);
 
}
void fnctakeawayright()
{
   int  iMotor[] = {1,  2,   0} ;
    int iPosic[] = {86, 93, 180};
    fncDoit_takeaway_do(iMotor, iPosic);
 
}

// realiza secuencia de maniobra
void fncDoit_takeaway_do(int iMotor[], int iPosic[])
{
  int iPasos = sizeof(iMotor);
  for (int i = 0; i < iPasos; i++) {
    fncServoMoveTo(iMotor[i], iPosic[i]);
    delay(500);
  }
  delay(1000);
}


//FUNCTIONS
//==============================
void IRAM_ATTR onTimer() {

  portENTER_CRITICAL_ISR(&timerMux);
  interruptCounter++;
  portEXIT_CRITICAL_ISR(&timerMux);
  g_TimeLapseDoIt = true;
  Serial.println("onTimer " + String(interruptCounter));
}

void sendRedirect(String uri) {
  WebServerClass& server = portal.host();
  server.sendHeader("Location", uri, true);
  server.send(302, "text/plain", "");
  server.client().stop();
}

bool atDetect(IPAddress softapIP) {
  Serial.println("Captive portal started, SoftAP IP:" + softapIP.toString());
  return true;
}
//========================================
// SERVO FUNCTIONS
//========================================




void fncServosActRead() {

  for (int i = 0; i < SERVO_COUNT; i++)
  {
    g_posAct[i] = g_servos[i].read();
  }
}
void fncServosActEqGo() {
  for (int i = 0; i < SERVO_COUNT; i++)  {
    g_posGo[i] = g_posAct[i];
  }
}
void fncServoMoveTo(int IdServo, int iMoveTo)
{
  g_msg_html = "";
  // si se le pide fuera de rango salir
  if ( iMoveTo > g_posMax[IdServo] || iMoveTo < g_posMin[IdServo])
  {
    g_msg_html = "IdServo=" + String(IdServo) + " Min=" + String(g_posMin[IdServo]) + " iMoveTo=" + String(iMoveTo) + " Max=" + String(g_posMax[IdServo]);
    Serial.println(g_msg_html);
    return;
  }
  // g_servos[IdServo].attach(g_PIN[IdServo], g_Servo_minUs, g_Servo_maxUs);
  g_posAct[IdServo] = g_servos[IdServo].read();
  g_posGo[IdServo] = iMoveTo;

  int iSteepGo = 0;

  int iSteepAdd = 1; // 1=turn right or -1= turn left, 0 no move

  if ( g_posAct[IdServo] > g_posGo[IdServo]) {
    iSteepAdd = -1;
  }
  while ( g_posAct[IdServo] != g_posGo[IdServo])
  {
    iSteepGo = g_posAct[IdServo] + iSteepAdd;
    g_servos[IdServo].write(iSteepGo);
    delay(15);
    g_posAct[IdServo] = iSteepGo;
  }
  //g_servos[IdServo].detach();

}

void fncServoMove()
{
  for (int IdServo = 0; IdServo < SERVO_COUNT; IdServo++)
  {
    if ( g_posAct[IdServo] != g_posGo[IdServo])
    {
      fncServoMoveTo(IdServo, g_posGo[IdServo]);
    }
  }
}
//==========================
// SETUPS
//==========================
void fncSetupSerial() {
  Serial.begin(115200);
  Serial.println("Setup");

}
//..................................
void fncSetupServos() {
  for (int i = 0; i < SERVO_COUNT; i++)
  {
    g_servos[i].attach(g_PIN[i], g_Servo_minUs, g_Servo_maxUs);  // attaches the servo on pin 18 to the servo object
    fncServoMoveTo(i, g_posIni[i]);
  }
  fncServosActRead();
  fncServosActEqGo();

  //g_servos[0].write(0);
  delay(100);

}
//...................................
void fncSetupTimer() {
  timer = timerBegin(0, 80, true);
  timerAttachInterrupt(timer, &onTimer, true);
  timerAlarmWrite(timer, TIMMER_INTERVAL, true);
  timerAlarmEnable(timer);
  // Create semaphore to inform us when the timer has fired

}
//...................................
void fncSetupNetWeb() {
  WebServerClass& server = portal.host();
server.on("/fnctakeawayleft", handleTAKEAWAYLEFT);
server.on("/fnctakeawayright", handleTAKEAWAYRIGHT);
server.on("/fnctakeawaycenter", handleTAKEAWAYCENTER);

  server.on("/fnctakeawayopen", handleTAKEAWAYOPEN);
  server.on("/fnctakeawayclose", handleTAKEAWAYCLOSE);
  server.on("/fnctakeaway", handleTAKEAWAY);
  server.on("/fncGetPosition", handleGETPOSITION);
  server.on("/fncGetStatus", handleGETSTATUS);
  server.on("/fncmotorset", handleMOTORSET);
  server.on("/", handleROOT);
  server.on("/js.js", handleJS);
  server.on("/css.css", handleCSS);

  server.on("/fncDebug", handleDEBUG);
  server.on("/fncReset", handleRESET);

  server.on("/", handleROOT);
  // server.on("/config", handleConfig);

  server.onNotFound(handleNotFound);

  fncDebugSetup();
}
//............................
void fncSetupNetMDNS() {

  Serial.println("fncSetupMDNS");
  if (!MDNS.begin(g_NetHostName)) {
    Serial.println("Error setting up MDNS responder!");
    while (1) {
      delay(1000);
    }
  }
  Serial.println("URI Host name =" + String(g_NetHostName));
  MDNS.addService("http", "tcp", 80);
}
//............................
void fncSetupNet()
{
  Serial.println("fncSetupNet");
  AutoConnectConfig  Config;

  char ssid[15]; //Create a Unique AP from MAC address
  uint64_t chipid = ESP.getEfuseMac(); //The chip ID is essentially its MAC address(length: 6 bytes).
  uint16_t chip = (uint16_t)(chipid >> 32);
  snprintf(ssid, 15, "Robot-%04X", chip);


  Serial.print("g_WifiAp_Ssid= ");
  Serial.println(ssid);

  //https://hieromon.github.io/AutoConnect/api/index.html#autoconnectconfig-api
#ifdef WS_STATIC_IP
  Serial.println("WS_STATIC_IP");

  Config.staip = IPAddress(192, 168, 1, 200);
  Config.staGateway = IPAddress(192, 168, 1, 1);
  Config.staNetmask = IPAddress(255, 255, 255, 0);
  Config.dns1 = IPAddress(192, 168, 1, 1);


#endif

  Config.apid = ssid;                 // Retrieve host name to SotAp identification
  Config.psk = "123456789";
  Config.apip = IPAddress(192, 168, 10, 1);   // Sets SoftAP IP address
  Config.gateway = IPAddress(192, 168, 1, 1);  // Sets WLAN router IP address
  Config.netmask = IPAddress(255, 255, 255, 0); // Sets WLAN scope
  /*
    Config.autoReconnect = true;                  // Enable auto-reconnect
    Config.autoSave = AC_SAVECREDENTIAL_NEVER;    // No save credential
    COnfig.boundaryOffet = 64;                    // Reserve 64 bytes for the user data in EEPROM.
    Config.homeUri = "/index.html"                // Sets home path of the sketch application
    Config.staip = IPAddress(192, 168, 1, 200);      // Sets static IP
    Config.staGateway = IPAddress((192, 168, 1, 1);  // Sets WiFi router address
    Config.staNetmask = IPAddress(255,255,255,0); // Sets WLAN scope
    Config.dns1 = IPAddress(192,168,10,1);        // Sets primary DNS address
    Portal.config(Config);                        // Configure AutoConnect
    Portal.begin();
  */

  portal.config(Config);

  //g_wifiWS_Ssid
  if (portal.begin()) {

    fncSetupNetMDNS();
    fncSetupNetWeb();



    Serial.println("Started, IP:" + WiFi.localIP().toString());
  }
  else {
    Serial.println("Connection failed.");
    while (true) {
      yield();
    }
  }


}
void setup() {
  pinMode(BUILTIN_LED, OUTPUT);
  digitalWrite(BUILTIN_LED, HIGH);
  delay(1000);

  fncSetupSerial();
  fncSetupNet();
  fncSetupServos();
  fncSetupTimer();
  fncDebugSetup();
  digitalWrite(BUILTIN_LED, LOW);
}

//==========================
// LOOP
//============================
void fncLoopTimer() {
  if ( g_TimeLapseDoIt == true)
  {
    fncServoMove();
    g_TimeLapseDoIt = false;
  }
}
void loop() {
  portal.handleClient();
  fncLoopTimer();
  if (WiFi.status() == WL_IDLE_STATUS) {
#if defined(ARDUINO_ARCH_ESP8266)
    ESP.reset();
#elif defined(ARDUINO_ARCH_ESP32)
    ESP.restart();
#endif

  }
}
