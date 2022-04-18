#include <ArduinoOTA.h>
#include "butt.h"
// #include "enabler.h"

int i=0;
int j=255;
bool restart=true;
unsigned long start;
int count;
int ledtime=500;


void OTAstart(){
  // Port defaults to 8266
  // ArduinoOTA.setPort(8266);

  // Hostname defaults to esp8266-[ChipID]
  // ArduinoOTA.setHostname("myesp8266");

  // No authentication by default
  // ArduinoOTA.setPassword("admin");

  // Password can be set with it's md5 value as well
  // MD5(admin) = 21232f297a57a5a743894a0e4a801fc3
  // ArduinoOTA.setPasswordHash("21232f297a57a5a743894a0e4a801fc3");

  ArduinoOTA.onStart([]() {
    String type;
    if (ArduinoOTA.getCommand() == U_FLASH) {
      type = "sketch";
    } else { // U_FS
      type = "filesystem";
    }

    // NOTE: if updating FS this would be the place to unmount FS using FS.end()
    Serial.println("Start updating " + type);
  });
  ArduinoOTA.onEnd([]() {
    Serial.println("\nEnd");
     hold(200, 120, 0);
     delay(500);
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {

    // Serial.println(progress/total);
            //led progress indicator
    int max = 255;
    int val = progress / (total / 100);
  val = map(val, 0, 100, 0, max);
  if(val <= max/3)
  {
      int mapper = map(val, 0, max/3,0,max);
  i=mapper;
  j=255-mapper;
    hold(j, i, 0);
  }else if(val > max/3 && val <= max*2/3){
          int mapper = map(val,max/3,max*2/3,0,max);
  i=mapper;
  j=255-mapper;
    hold(0, j, i);

  }else if(val > max*2/3 && val <= max){
              int mapper = map(val,max*2/3,max,0,max);
  i=mapper;
  j=255-mapper;
    hold(i, i, 255);
  }

  //rainbow indicator

//   if(restart ==true){
//     start=millis();
//     restart = false;
//   }
//   if(millis()-start >= ledtime ){
//     count++;
//     if (count == 4){
//       count =0;
//     }
//     // count++;
//     Serial.println(count);
//     switch (count) {
//   case 1:
//     // hold(255, 0, 0);
//     hold(50, 140, 168);
//     restart = true;
//     break;
//   case 2:
//     // hold(0, 255, 0);
//     hold(168, 105, 50);
//     restart = true;
//     break;
//   case 3:
//     // hold(0,0,255);
//     hold(168, 50, 160);
//     restart = true;
//     break;
// }
//   }
    // hold(i, j, i);
//     i=i+2;
//     j=j-2;
//     // j=j-1;
// // Serial.println(i);
//     if(i>=255){
//       i=0;
//       j=255;
//       // p=0;
//     }
    // Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
  });
  ArduinoOTA.onError([](ota_error_t error) {
    blink(0x77, 0, 0,150);
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) {
      Serial.println("Auth Failed");
    } else if (error == OTA_BEGIN_ERROR) {
      Serial.println("Begin Failed");
    } else if (error == OTA_CONNECT_ERROR) {
      Serial.println("Connect Failed");
    } else if (error == OTA_RECEIVE_ERROR) {
      Serial.println("Receive Failed");
    } else if (error == OTA_END_ERROR) {
      Serial.println("End Failed");
    }
  });
  ArduinoOTA.begin();
  // Serial.println("Ready");
  // Serial.print("IP address: ");
  // Serial.println(WiFi.localIP());
//  break;
}

void OTAHandler(){
    ArduinoOTA.handle();
    if(Serial.available())
    {
         String data = Serial.readString();
         Serial.println(data);
     if(data == "R") 
         {
            // ArduinoOTA.handle();
            ESP.restart();
            Serial.println("OTA ENABLED");
            return; 
         }
    }

}