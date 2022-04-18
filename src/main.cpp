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
#include <AsyncTimer.h>
#include "butt.h"
// #include "enabler.h"

unsigned long detectPress= 0;

// AsyncTimer t;

// struct Button
// {
//   const uint8_t PIN;
//   bool pressed;
// };

// Button button1 = {18, false};

// void IRAM_ATTR isr()
// {
//   button1.pressed = !button1.pressed;
//   //   redo();
//   Serial.println(button1.pressed);
// }

bool wifiConnected = false;
String indicator;
bool mani=true;
int duration =1000;

void setup()
{
  // pinMode(5, OUTPUT);
  Serial.begin(115200);
  // Serial.println(ESP.getFlashChipSize());
  bloopSt();
    // buttonsetup();
  connect2nearestAP();
  checkWiFi();
  OTAWebStart();
  initWebSocket();
  // bloopSt();
  //  startMpu();
  //  attachInterrupt(button1.PIN, isr, FALLING);
  //  setupSpiffs();
  // delay(5000);
  beginUdp();
  //  lightsetup();
  //  digitalmpsetup();
  // setupUDP();
  dmpsetup();
  esp_sleep_enable_ext0_wakeup(GPIO_NUM_4,0); 
}

void loop()
{
  if (wifiConnected == false)
  {
    if (WiFi.status() == WL_CONNECTED)
    {
      blink(0, 0, 0x77,90);
      Serial.println("WiFi is connected");
      Serial.println(WiFi.localIP());
      wifiConnected = true;
      Serial.println(WiFi.getMode());
    }
  }
  OTAWebServer();
  // buttonloop();
  t.handle();
  // broadcaster();

  rentol();
  // lightloop();
  // udpier();
  // vcc_init();
  //   redo();
  // loopWOM();
  // delay(1);
  // digitalmploop();
  // dmploop();
  // strips_loop();
  indicator =bloop();
  if (indicator.length() > 0){
    Serial.println(indicator);
    // Serial.println(WiFi.status());
    if (indicator == "single click" && WiFi.status() == WL_CONNECTED)
    {
      blink(0, 0, 0x77,75);
      return;
    }
    if (indicator == "single click" && WiFi.status() != WL_CONNECTED)
    {
      blink(0x77, 0, 0,75);
    }
    else if (indicator == "Double click LP" && WiFi.status() == WL_CONNECTED)
    {
      detectPress = millis();
      hold(0, 0, 0x77,mani);
      // mani =! mani;
      // while(millis() - detectPress <=duration){}
      WiFi.mode(WIFI_OFF);
    }
    else if (indicator == "Double click LP" && WiFi.status() != WL_CONNECTED)
    {
      hold(0x77, 0, 0,mani);
      // mani =! mani;
      connect2nearestAP();
    }
  }
}