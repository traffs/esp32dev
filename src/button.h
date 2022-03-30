/*
 * This ESP32 code is created by esp32io.com
 *
 * This ESP32 code is released in the public domain
 *
 * For more detail (instruction and wiring diagram), visit https://esp32io.com/tutorials/esp32-button-long-press-short-press
 */

#include <ezButton.h>
#include "indicator.h"
#define SHORT_PRESS_TIME 1000 // 1000 milliseconds
#define LONG_PRESS_TIME  1000 // 1000 milliseconds

ezButton button(16); // create ezButton object that attach to pin GIOP21

unsigned long currentTime = 0;
unsigned long prevTime = 0;

unsigned long pressedTime  = 0;
unsigned long releasedTime = 0;
bool isPressing = false;
bool isLongDetected = false;

void buttonsetup() {
  button.setDebounceTime(50); // set debounce time to 50 milliseconds
}

void buttonloop() {
  button.loop(); // MUST call the loop() function first

  if (button.isPressed()) {
    pressedTime = millis();
    isPressing = true;
    isLongDetected = false;
  }

  if (button.isReleased()) {
    isPressing = false;
    releasedTime = millis();

    long pressDuration = releasedTime - pressedTime;

    if ( pressDuration < SHORT_PRESS_TIME && isLongDetected == false )
    {
        Serial.println("A short press is detected");
      pixels.setPixelColor(0, pixels.Color(1,0,0)); 
      pixels.show();
    }
  }

  if (isPressing == true && isLongDetected == false) {
    long pressDuration = millis() - pressedTime;

    if ( pressDuration > LONG_PRESS_TIME ) {
      Serial.println("A long press is detected");
      pixels.setPixelColor(0, pixels.Color(0,1,0)); 
      pixels.show();
      isLongDetected = true;
    }
  }
  currentTime = millis();
  pixels.setPixelColor(0, pixels.Color(0,0,0));
  if(currentTime - prevTime >= 2000 && isLongDetected == false){
      pixels.show();
    //   String delay = String(currentTime - prevTime);
    //   Serial.println("delay"+ delay);
      prevTime = currentTime;
      
  }
}
