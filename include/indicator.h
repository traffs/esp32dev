#include <Adafruit_NeoPixel.h>
#include <AsyncTimer.h>

#define LEDPIN            15

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      1
AsyncTimer t;

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, LEDPIN, NEO_GRB + NEO_KHZ800);

int delayval = 250; // delay for half a second

void lightsetup() 
{
  pixels.begin(); // This initializes the NeoPixel library.
}

void lightloop() 
{
  // for(int i=0;i<NUMPIXELS;i++)
  // {
  //   // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
  //   pixels.setPixelColor(i, pixels.Color(1,0,0)); // Moderately bright green color.
  //   pixels.show(); // This sends the updated pixel color to the hardware.
  //   delay(delayval); // Delay for a period of time (in milliseconds).
  // }

  // for(int i=0;i<NUMPIXELS;i++)
  // {
  //   // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
  //   pixels.setPixelColor(i, pixels.Color(0,1,0)); // Moderately bright green color.
  //   pixels.show(); // This sends the updated pixel color to the hardware.
  //   delay(delayval); // Delay for a period of time (in milliseconds).
  // }

  // for(int i=0;i<NUMPIXELS;i++)
  // {
  //   // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
  //   pixels.setPixelColor(i, pixels.Color(0,0,1)); // Moderately bright green color.
  //   pixels.show(); // This sends the updated pixel color to the hardware.
  //   delay(delayval); // Delay for a period of time (in milliseconds).
  // }
}

void led5(int timeDelay ){
  long delayval =timeDelay;
  long initialTime =millis();
    pixels.setPixelColor(0, pixels.Color(1,0,0)); 
      pixels.show();
  // if(millis() - initialTime == delayval){
  //       pixels.setPixelColor(0, pixels.Color(0,0,0)); 
  //     pixels.show();
  // }
    t.setTimeout(
      []() {  pixels.setPixelColor(0, pixels.Color(0,0,0)); 
      pixels.show(); }, timeDelay);
}
// }