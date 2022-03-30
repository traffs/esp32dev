 
#include <WiFi.h>
 
// #include "TD_Credentials.h"
 
byte bssid[] = {0x32, 0xC9, 0x29, 0xAB, 0x91, 0x4E}; // Repeater FeWo, 2.4 GHz
//byte bssid[] = {0x4E, 0x91, 0xAB, 0x29, 0xC9, 0x32}; // Repeater FeWo, 2.4 GHz
const char *ssid="YOUR_SSID";
const char* password ="YOUR_PASSWORD";
const char* HostName = "test";

#define MaxSecWiFi 30       // max time in s for WiFi setup, function will return WiFiErrorCode if WiFi was not successful.
#define WiFiErrorCode 1000  // see above
#define SaveDisconnectTime 1000 // Time im ms for save disconnection, needed to avoid that WiFi works only evey secon boot: https://github.com/espressif/arduino-esp32/issues/2501
#define WiFiTime 10    // Max time in s for successful WiFi connection.
#define WiFiOK 0       // WiFi connected
#define WiFiTimedOut 1 // WiFi connection timed out
#define WiFiNoSSID 2   // The SSID was not found during network scan
#define WiFiRSSI -75   // Min. required signal strength for a good WiFi cennection. If lower, new scan is initiated in checkWiFi()

int connect2nearestAP()
{

  // this routine disconnects from WiFi, scans the network for the strongest AP at the defined SSID and tries to connect. returns WiFiOK, WiFiTimedOut, or WiFiNoSSID

  int n;
  int i = 0;

  // the following awkward code seems to work to avoid the following bug in ESP32 WiFi connection: https://github.com/espressif/arduino-esp32/issues/2501
  WiFi.disconnect(true); // delete old config
  WiFi.persistent(false); //Avoid to store Wifi configuration in Flash
  WiFi.mode(WIFI_OFF);
  WiFi.mode(WIFI_STA);
  WiFi.disconnect(true); // delete old config
  WiFi.setHostname(HostName);
  WiFi.begin();
  delay(SaveDisconnectTime); // 500ms seems to work in most cases, may depend on AP
  WiFi.disconnect(true); // delete old config

  Serial.println("scan start");
  n = WiFi.scanNetworks(); // WiFi.scanNetworks will return the number of networks found
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
      Serial.print("BSSID: ");
      Serial.print(WiFi.BSSIDstr(i));
      Serial.print("  ");
      Serial.print(WiFi.RSSI(i));
      Serial.print("dBm, ");
      Serial.print(constrain(2 * (WiFi.RSSI(i) + 100), 0, 100));
      Serial.print("% ");
      Serial.print((WiFi.encryptionType(i) == WIFI_AUTH_OPEN) ? "open       " : "encrypted  ");
      Serial.println(WiFi.SSID(i));
      delay(10);
    }
  }
  Serial.println();

  //  while ( !strcmp(ssid, &WiFi.SSID(i)) && (i < n)) {
  // while ( String(ssid) != String(WiFi.SSID(i)) && (i < n)) {
  //   i++;
  // }

  if (i == n) {
    Serial.print("No network with SSID ");
    Serial.print(String(ssid));
    Serial.print(" found!");
    return WiFiNoSSID;
  }

  Serial.print("SSID match found at: ");
  Serial.println(i + 1);

  WiFi.setHostname(HostName);
  WiFi.begin(ssid, password, 0, WiFi.BSSID(i));
  i = 0;
  Serial.print("Connecting ");
  if((WiFi.status() != WL_CONNECTED) && (i < WiFiTime * 100)) {
    Serial.println("still conncting");
  }
  // while ((WiFi.status() != WL_CONNECTED) && (i < WiFiTime * 100)) {
  //   delay(100);
  //   Serial.print(".");
  //   // && (i < WiFiTime * 10
  //   i++;
  // }

  Serial.println();

  // if (WiFi.status() != WL_CONNECTED) {
  //   Serial.print("Connection to ");
  //   Serial.print(ssid);
  //   Serial.println(" timed out! ");
  //   return WiFiTimedOut;
  // }


  Serial.print("Connected to BSSID: ");
  Serial.print(WiFi.BSSIDstr());
  Serial.print("  ");
  Serial.print(WiFi.RSSI());
  Serial.print("dBm, ");
  Serial.print(constrain(2 * (WiFi.RSSI() + 100), 0, 100));
  Serial.print("% ");
  Serial.print(WiFi.SSID());
  Serial.print(" IP: ");
  Serial.println(WiFi.localIP());

  return (WiFiOK);
}

void checkWiFi() { // Check the signal strength of the connection - if too low, reconnect to the strongest AP; good if the ESP is moving around and reconnection to the nearest AP makes sense
  int i = 1;
  if ((WiFi.status() == WL_CONNECTED) && (WiFi.RSSI() > WiFiRSSI) && (WiFi.RSSI() < -25)) { // good connection
    Serial.print("Connection good: ");
    Serial.print(WiFi.RSSI());
    Serial.print("dBm, ");
    Serial.print(constrain(2 * (WiFi.RSSI() + 100), 0, 100));
    Serial.print("% ");
    Serial.println(" ... keep going");
    return;
  }
  while (connect2nearestAP() != WiFiOK) {
    Serial.print("connect2nearestAP was called #");
    Serial.println(i);
    delay(1000);
    i++;
    if (i > 10) {
      Serial.println("Rebooting cause WiFi setup failes");
      ESP.restart();
    }
  }
}