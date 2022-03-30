#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>
#include <arduino.h>

AsyncWebServer wsserver(81);
AsyncWebSocket ws("/");

void handleWebSocketMessage(void *arg, uint8_t *data, size_t len) {
  AwsFrameInfo *info = (AwsFrameInfo*)arg;
  if (info->final && info->index == 0 && info->len == len && info->opcode == WS_TEXT) {
    data[len] = 0;
    // if (strcmp((char*)data, "toggle") == 0) {
    //   ledState = !ledState;
    //   notifyClients();
    // }
    Serial.println("data");
    DynamicJsonDocument doc(1024);
doc["time"]   = "23:11";
doc["batterylevel"] = 3.3;
String output;
// serializeJson(doc, Serial);
serializeJson(doc, output);
     ws.textAll(output);
  }
}

void onEvent(AsyncWebSocket *wsserver, AsyncWebSocketClient *client, AwsEventType type,
             void *arg, uint8_t *data, size_t len) {
  switch (type) {
    case WS_EVT_CONNECT:
      Serial.printf("WebSocket client #%u connected from %s\n", client->id(), client->remoteIP().toString().c_str());
      break;
    case WS_EVT_DISCONNECT:
      Serial.printf("WebSocket client #%u disconnected\n", client->id());
      break;
    case WS_EVT_DATA:
      handleWebSocketMessage(arg, data, len);
      break;
    case WS_EVT_PONG:
    case WS_EVT_ERROR:
      break;
  }
}

void initWebSocket() {
  ws.onEvent(onEvent);
  wsserver.addHandler(&ws);
  wsserver.begin();
  Serial.println("begun");
}

// String processor(const String& var){
//   Serial.println(var);
//   if(var == "STATE"){
//     if (ledState){
//       return "ON";
//     }
//     else{
//       return "OFF";
//     }
//   }
//   return String();
// }

// void setup(){
//   initWebSocket();

//   // Route for root / web page
//   server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
//     request->send_P(200, "text/html", index_html, processor);
//   });

//   // Start server
//   server.begin();
// }

// void loop() {
//   ws.cleanupClients();
// }