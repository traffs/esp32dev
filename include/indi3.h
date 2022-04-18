#include <Adafruit_NeoPixel.h>
#define PIN 15
#define NUM_LEDS 1
// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, PIN, NEO_GRB + NEO_KHZ800);
int k = 255;

// void loop() {
//   FadeOut(0xff, 0x77, 0x00);
// }

void showStrip()
{
#ifdef ADAFRUIT_NEOPIXEL_H
    // NeoPixel
    strip.show();
#endif
#ifndef ADAFRUIT_NEOPIXEL_H
    // FastLED
    FastLED.show();
#endif
}

void setPixel(int Pixel, byte red, byte green, byte blue)
{
#ifdef ADAFRUIT_NEOPIXEL_H
    // NeoPixel
    strip.setPixelColor(Pixel, strip.Color(red, green, blue));
#endif
#ifndef ADAFRUIT_NEOPIXEL_H
    // FastLED
    leds[Pixel].r = red;
    leds[Pixel].g = green;
    leds[Pixel].b = blue;
#endif
}

void setAll(byte red, byte green, byte blue)
{
    for (int i = 0; i < NUM_LEDS; i++)
    {
        setPixel(i, red, green, blue);
    }
    showStrip();
}
void FadeIn(byte red, byte green, byte blue)
{
    float r, g, b;

    for (int k = 0; k < 256; k = k + 1)
    {
        r = (k / 256.0) * red;
        g = (k / 256.0) * green;
        b = (k / 256.0) * blue;
        setAll(r, g, b);
        showStrip();
    }
}
bool FadeOut(byte red, byte green, byte blue)
{
    if (k == 0)
    {
        // Serial.println(millis());
        k = 255;
    }
    float r, g, b;
    r = (k / 256.0) * red;
    g = (k / 256.0) * green;
    b = (k / 256.0) * blue;
    setAll(r, g, b);
    showStrip();
    k = k - 1;
    if (k == 0)
    {
        // Serial.println(millis());
        return true;
    }
    else
    {
        return false;
    }
}

void FadeOut2(byte red, byte green, byte blue)
{
    float r, g, b;

    for (int k = 256; k >= 0; k = k - 2)
    {
        r = (k / 256.0) * red;
        g = (k / 256.0) * green;
        b = (k / 256.0) * blue;
        setAll(r, g, b);
        showStrip();
        delay(4);
    }
}

void FadeInOut(byte red, byte green, byte blue, int fadeInDuration = 10, int fadeOutDuration = 10)
{
    float r, g, b;

    for (int k = 0; k < 256; k = k + 1)
    {
        r = (k / 256.0) * red;
        g = (k / 256.0) * green;
        b = (k / 256.0) * blue;
        setAll(r, g, b);
        showStrip();
        delay(fadeInDuration);
    }

    for (int k = 255; k >= 0; k = k - 2)
    {
        r = (k / 256.0) * red;
        g = (k / 256.0) * green;
        b = (k / 256.0) * blue;
        setAll(r, g, b);
        showStrip();
        delay(fadeOutDuration);
    }
}

void blink(byte red, byte green, byte blue,int duration=40)
{
    float r, g, b;

    // black
    r = 0 * red;
    g = 0 * green;
    b = 0 * blue;
    setAll(r, g, b);
    showStrip();
    // color
    r = (k / 256.0) * red;
    g = (k / 256.0) * green;
    b = (k / 256.0) * blue;
    setAll(r, g, b);
    showStrip();
    delay(duration);
    // black
    r = 0 * red;
    g = 0 * green;
    b = 0 * blue;
    setAll(r, g, b);
    showStrip();
}
void hold(byte red, byte green, byte blue, bool hold = true){
        // color
        float r, g, b;
    if(hold == true){
    r = (k / 256.0) * red;
    g = (k / 256.0) * green;
    b = (k / 256.0) * blue;
    setAll(r, g, b);
    showStrip();
    }
    //unhold
    else if(hold == false){
    r = 0 * red;
    g = 0 * green;
    b = 0 * blue;
    setAll(r, g, b);
    showStrip();      
    }

}

// void hold(byte red, byte green, byte blue, bool hold = true){
//         // color
//         float r, g, b;
//     if(hold == true){
//     r = (k / 256.0) * red;
//     g = (k / 256.0) * green;
//     b = (k / 256.0) * blue;
//     setAll(r, g, b);
//     showStrip();
//     }
//     //unhold
//     else if(hold == false){
//     r = 0 * red;
//     g = 0 * green;
//     b = 0 * blue;
//     setAll(r, g, b);
//     showStrip();      
//     }

// }

void indisetup()
{
    strip.begin();
    FadeInOut(0x00, 0xff, 0x00,1,1);
    strip.show(); // Initialize all pixels to 'off'
}
