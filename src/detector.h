#include <WiFiUDP.h>
#include <ArduinoJson.h>

const char *udpAddress = "192.168.100.255";
const int udpPort = 4210;
String jsonner ="ESP32";
uint8_t buffer[50] = "ESP v2C";
char incomingPacket[255];
DynamicJsonDocument doc(1024);
char jsonChar[100];
// String jsonner ="ESP32";
uint8_t replyPacket[]="alaa";
// uint8_t replyPack=778899;

WiFiUDP finder;

String comp = "marco";

// size_t write(const char *str) {
//             if(str == NULL)
//                 return 0;
//             return write((const uint8_t *) str, strlen_P(str));
//         }

void beginUdp(){
    doc["name"] = "gps";
    doc["data"] = 3.545646;
    serializeJson(doc,jsonChar);
    // doc.printTo(jsonChar);
    Serial.println(jsonChar);
//     uint8_t dataArray[jsonner.length()];
// jsonner.getBytes(dataArray, jsonner.length());
    // uint8_t buffer[50] = {jsonChar};

    finder.begin(udpPort);
}

void rentol()
{
    int packetSize = finder.parsePacket();
  if (packetSize){
      Serial.printf("Received %d bytes from %s, port %d\n", packetSize, finder.remoteIP().toString().c_str(), finder.remotePort());
      int len  = finder.read(incomingPacket, 255);
      if(len>0){
          incomingPacket[len]='\0';
          Serial.printf("UDP packet contents: %s\n",incomingPacket);
          String comp = "marco";
          String s = String(incomingPacket);
          // Serial.println(s.length()); // length before trimming
          Serial.println(s);
          s.trim();
          if(String(incomingPacket) == comp){
            Serial.println("poa");
            // Serial.println(String((uint32_t)ESP.getEfuseMac(), HEX) );
           finder.beginPacket(finder.remoteIP(),finder.remotePort());
           String ppl= "hello world";
           uint8_t dataArray[jsonner.length()];
           jsonner.getBytes(dataArray, jsonner.length());
           Serial.println(sizeof(dataArray));
        //    finder.write(dataArray,sizeof(dataArray));
           finder.write(buffer, 7);
        //    finder.write(buffer, sizeof(ppl)-1);
           finder.endPacket();            
          }
      }
  }


    // uint8_t buffer[50] = "hello world";
    // memset(buffer, 0, 50);
    // // processing incoming packet, must be called before reading the buffer
    // finder.parsePacket();
    // // receive response from server, it will be HELLO WORLD
    // if (finder.read(buffer, 50) > 0)
    // {
    //     Serial.print("Server to client: ");
    //     Serial.println((char *)buffer);
    //     if(String((char *)buffer) == comp){
    //         // Serial.println("poa");
    //         // Serial.println(finder.remoteIP() + finder.remotePort());
    //                 finder.beginPacket(finder.remoteIP(), finder.remotePort());
    // finder.write(buffer, 11);
    // finder.endPacket();
    //         }
    // //     finder.beginPacket(finder.remoteIP(), finder.remotePort());
    // // finder.write(buffer, 11);
    // // finder.endPacket();
    // }
    // // Wait for 1 second
    delay(1000);
}