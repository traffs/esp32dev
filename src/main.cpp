#include <Arduino.h>
#include "wifiManager.h"
#include "otawebserver.h"
// #include "mpu.h"
// #include "filewrite.h"
// #include "getvcc.h"
#include "websocket.h"
#include "detector.h"
// #include "button.h"
// #include "digitalmp.h"
#include "i2cdevver.h"
// #include "indicator.h"
// #include "asynccudp.h"
#include "streamer.h"
 
struct Button
{
  const uint8_t PIN;
  bool pressed;
};

Button button1 = {18, false};

void IRAM_ATTR isr()
{
  button1.pressed = !button1.pressed;
  //   redo();
  Serial.println(button1.pressed);
}

bool wifiConnected = false;

void setup()
{
  // pinMode(5, OUTPUT);
  // buttonsetup();
  Serial.begin(115200);
  connect2nearestAP();
  checkWiFi();
  OTAWebStart();
  initWebSocket();
  //  startMpu();
  //  attachInterrupt(button1.PIN, isr, FALLING);
  //  setupSpiffs();
  delay(5000);
  beginUdp();
  //  lightsetup();
  //  digitalmpsetup();
  // setupUDP();
  // dmpsetup();
  camerasetup();
}

void loop()
{
  if (wifiConnected == false)
  {
    if (WiFi.status() == WL_CONNECTED)
    {
      Serial.println("WiFi is connected");
      Serial.println(WiFi.localIP());
      wifiConnected = true;
    }
  }
  OTAWebServer();
  // buttonloop();
  // broadcaster();
  // rentol();
  // lightloop();
  // udpier();
  // vcc_init();
  //   redo();
  // loopWOM();
  // delay(1);
  // digitalmploop();
  // dmploop();
}