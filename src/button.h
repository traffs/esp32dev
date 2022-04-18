#include <ezButton.h>
#include "indicator.h"

unsigned long pressedTime  = 0;
unsigned long releasedTime = 0;

ezButton button(16);

unsigned long timePress = 0;
unsigned long timePressLimit = 0;
bool isPressing = false;
bool isLongDetected = false;
int clicks = 0;
int bufferer = 500;
int LongClickTime=700;

void buttonsetup() {

  // Serial.begin(115200);
  Serial.println("Start");
  button.setDebounceTime(50);
}

void buttonloop() {
  button.loop();

  if (button.isPressed()) {
    timePress = millis();

    if (clicks == 0) {
      timePress = millis();
      timePressLimit = timePress + bufferer;
      clicks = 1;
    } else if (clicks == 1 && millis() < timePressLimit) {
      timePress = millis();
      timePressLimit = timePress + bufferer;
      clicks = 2;
    } else if (clicks == 2 && millis() < timePressLimit) {
      timePress = millis();
      timePressLimit = timePress + bufferer;
      clicks = 3;
    }
    isPressing = true;
    isLongDetected = false;
  }

  if (button.isReleased()) {
    isPressing = false;
    releasedTime = millis();

    long pressDuration = releasedTime - timePress;
  }

  if (isPressing == true && isLongDetected == false) {
    long pressDuration = millis() - timePress;

    if ( pressDuration > LongClickTime ) {
      isLongDetected = true;
      return;
    }

  }

  if (clicks == 1 && timePressLimit != 0 && millis() > timePressLimit && isPressing == false) {
    Serial.println("Single click");
    led5(4000);
    timePress = 0;
    timePressLimit = 0;
    clicks = 0;

  }
  else if (clicks == 1 && timePressLimit != 0 && millis() > timePressLimit && isLongDetected == true) {
    Serial.println("Single click long press");
    timePress = 0;
    timePressLimit = 0;
    clicks = 0;
  }

  if (clicks == 2 && timePressLimit != 0 && millis() > timePressLimit && isPressing == false) {
    Serial.println("Double click");
    timePress = 0;
    timePressLimit = 0;
    clicks = 0;
  }
    else if (clicks == 2 && timePressLimit != 0 && millis() > timePressLimit && isLongDetected == true) {
    Serial.println("Double click long press");
    timePress = 0;
    timePressLimit = 0;
    clicks = 0;
  }

  if (clicks == 3 && timePressLimit != 0 && millis() > timePressLimit && isPressing == false) {
      Serial.println("tripple click");
    timePress = 0;
    timePressLimit = 0;
    clicks = 0;
  }
    else if (clicks == 3 && timePressLimit != 0 && millis() > timePressLimit && isLongDetected == true) {
    Serial.println("Triple click long press");
    timePress = 0;
    timePressLimit = 0;
    clicks = 0;
  }
}

// /*
//  * This ESP32 code is created by esp32io.com
//  *
//  * This ESP32 code is released in the public domain
//  *
//  * For more detail (instruction and wiring diagram), visit https://esp32io.com/tutorials/esp32-button-long-press-short-press
//  */

// #include <ezButton.h>
// #include "indicator.h"
// #define SHORT_PRESS_TIME 1000 // 1000 milliseconds
// #define LONG_PRESS_TIME  1000 // 1000 milliseconds

// ezButton button(16); // create ezButton object that attach to pin GIOP21

// unsigned long currentTime = 0;
// unsigned long prevTime = 0;

// unsigned long pressedTime  = 0;
// unsigned long releasedTime = 0;
// bool isPressing = false;
// bool isLongDetected = false;

// void buttonsetup() {
//   button.setDebounceTime(50); // set debounce time to 50 milliseconds
// }

// void buttonloop() {
//   button.loop(); // MUST call the loop() function first

//   if (button.isPressed()) {
//     pressedTime = millis();
//     isPressing = true;
//     isLongDetected = false;
//   }

//   if (button.isReleased()) {
//     isPressing = false;
//     releasedTime = millis();

//     long pressDuration = releasedTime - pressedTime;

//     if ( pressDuration < SHORT_PRESS_TIME && isLongDetected == false )
//     {
//         Serial.println("A short press is detected");
//       pixels.setPixelColor(0, pixels.Color(1,0,0)); 
//       pixels.show();
//     }
//   }

//   if (isPressing == true && isLongDetected == false) {
//     long pressDuration = millis() - pressedTime;

//     if ( pressDuration > LONG_PRESS_TIME ) {
//       Serial.println("A long press is detected");
//       pixels.setPixelColor(0, pixels.Color(0,1,0)); 
//       pixels.show();
//       isLongDetected = true;
//     }
//   }
//   currentTime = millis();
//   pixels.setPixelColor(0, pixels.Color(0,0,0));
//   if(currentTime - prevTime >= 2000 && isLongDetected == false){
//       pixels.show();
//     //   String delay = String(currentTime - prevTime);
//     //   Serial.println("delay"+ delay);
//       prevTime = currentTime;
      
//   }
// }
