 
#include <WiFi.h>
 
// #include "TD_Credentials.h"
 
byte bssid[] = {0x32, 0xC9, 0x29, 0xAB, 0x91, 0x4E}; // Repeater FeWo, 2.4 GHz
//byte bssid[] = {0x4E, 0x91, 0xAB, 0x29, 0xC9, 0x32}; // Repeater FeWo, 2.4 GHz
const char *ssid="VUMA FIBER";
const char* password ="tamarawanja";

void scanNetwork()
{
  Serial.println("scan start");
  // byte bssid[6];
  int n = WiFi.scanNetworks(); // WiFi.scanNetworks will return the number of networks found
  Serial.println("scan done");
  if (n == 0) {
    Serial.println("no networks found");
  } else {
    Serial.print(n);
    Serial.println(" networks found");
    for (int i = 0; i < n; ++i) {
      // Print SSID and RSSI for each network found
      Serial.print(i + 1);
      Serial.print(": ");
      Serial.print(WiFi.SSID(i));
      Serial.print(" (");
      Serial.print(WiFi.RSSI(i));
      Serial.print("dBm, ");
      Serial.print(constrain(2 * (WiFi.RSSI(i) + 100), 0, 100));
      Serial.print("%)      ");
 
      byte *bssid = WiFi.BSSID(i);
      Serial.print("BSSID: ");
      Serial.print(bssid[5], HEX);
      Serial.print(":");
      Serial.print(bssid[4], HEX);
      Serial.print(":");
      Serial.print(bssid[3], HEX);
      Serial.print(":");
      Serial.print(bssid[2], HEX);
      Serial.print(":");
      Serial.print(bssid[1], HEX);
      Serial.print(":");
      Serial.print(bssid[0], HEX);
      Serial.println((WiFi.encryptionType(i) == WIFI_AUTH_OPEN) ? " open" : " encrypted");
      delay(10);
    }
  }
  Serial.println("");
 
 
}
 
void setup()
{
 
  int i = 0;
  Serial.begin(115200);
  Serial.println("----------------- Start Setup --------------");
 
  scanNetwork();
 
  // WiFi.begin(ssid, password);
  WiFi.begin(ssid, password, 0, bssid); // was hoping to connect die an AP with defined BSSID - dies not work ...
 
  Serial.print("Connecting ");
  while ((WiFi.status() != WL_CONNECTED) && (i < 500)) {
    delay(500);
    Serial.print(".");
    i++;
  }
 
  Serial.println("!");
 
  Serial.println();
 
  Serial.print(WiFi.SSID());
  Serial.print(" (");
  Serial.print(WiFi.RSSI());
  Serial.print("dBm, ");
  Serial.print(constrain(2 * (WiFi.RSSI() + 100), 0, 100));
  Serial.print("%)      ");
  Serial.println();
 
  // shoud print the MAC address of the router you're attached to, does not work!!!!
  // byte bssid[6];
  byte *bssid = WiFi.BSSID();
  Serial.print("BSSID: ");
  Serial.print(bssid[5], HEX);
  Serial.print(":");
  Serial.print(bssid[4], HEX);
 Serial.print(":");
  Serial.print(bssid[3], HEX);
  Serial.print(":");
  Serial.print(bssid[2], HEX);
  Serial.print(":");
  Serial.print(bssid[1], HEX);
  Serial.print(":");
  Serial.println(bssid[0], HEX);
  Serial.println("----------------- End Setup --------------");
}
void loop () {}