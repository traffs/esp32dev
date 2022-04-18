#ifndef butt.h
#define butt.h
#include <ezButton.h>
// #include "indicator2.h"
#include "indi3.h"
#include <AsyncTimer.h>

AsyncTimer t;

unsigned long pressedTime = 0;
unsigned long releasedTime = 0;

ezButton button(4);

unsigned long timePress = 0;
unsigned long timePressLimit = 0;
bool isPressing = false;
bool isLongDetected = false;
int clicks = 0;
int buffered = 500;
int LongClickTime = 700;

// String text;
String empty;


void bloopSt()
{
        button.setDebounceTime(20);
        indisetup();
}

void canceler(String valid) {
        unsigned short intervald = (unsigned short) strtoul(valid.c_str(), NULL, 0);
        Serial.println(intervald);
                t.cancel(intervald);
        }

String bloop(String text="")
{
        // String text;
        button.loop();
        if (button.isPressed())
        {
                timePress = millis();
                if (clicks == 0)
                {
                        timePress = millis();
                        timePressLimit = timePress + buffered;
                        clicks = 1;
                }
                else if (clicks == 1 && millis() < timePressLimit)
                {
                        timePress = millis();
                        timePressLimit = timePress + buffered;
                        clicks = 2;
                }
                else if (clicks == 2 && millis() < timePressLimit)
                {
                        timePress = millis();
                        timePressLimit = timePress + buffered;
                        clicks = 3;
                }
                isPressing = true;
                isLongDetected = false;
        }

        if (button.isReleased())
        {
                isPressing = false;
                releasedTime = millis();

                // long pressDuration = releasedTime - timePress;
        }

        if (isPressing == true && isLongDetected == false)
        {
                long pressDuration = millis() - timePress;

                if (pressDuration > LongClickTime)
                {
                        isLongDetected = true;
                        // return;
                }
        }

        if (clicks == 1 && timePressLimit != 0 && millis() > timePressLimit && isPressing == false)
        {
                // Serial.println("Single click");
                // bool answer = false;
                // FadeOut(0xff, 0x77, 0x00);
                // unsigned short intervalId = t.setInterval([]() {
                //         // answer = FadeOut(0xff, 0x77, 0x00);
                //         if(FadeOut(0xff, 0x77, 0x00)== true){
                //                 // Serial.println("answer");
                //                 //     canceler("intervalId");
                //                 //     t.cancel(intervalId);
                // }
                // }, 2);
                // // if ( answer == true){
                // //         t.cancel(intervalId);
                // // }
                // // t.setTimeout([](intervalId) { t.cancel(intervalId), 10000);
                // FadeOut2(0xff, 0xff, 0xff);
                // blink(0xff, 0x77, 0x00);

                // t.setInterval([]()
                //               {
                //                       if(FadeOut(0xff, 0x77, 0x00)== true){
                //                 //     t.cancelAll();  
                //               }},
                //               1);

                        //       if(FadeOut(0xff, 0x77, 0x00)== true){
                        //             t.cancelAll();  
                        //       }

                // t.setInterval([]() {
                //   strips_loop();
                // //   Serial.println("baz");
                // }, 1);

                // t.setTimeout([]() {
                //   t.cancelAll();
                // }, 763);

                // t.setTimeout([]() {
                //   Serial.println("baz");
                // }, 7000);

                // After this call, nothing will be running inside AsyncTimer
                // t.cancelAll();
                // strips_loop();
                timePress = 0;
                timePressLimit = 0;
                clicks = 0;
                text="single click";
                return text;
        }
        else if (clicks == 1 && timePressLimit != 0 && millis() > timePressLimit && isLongDetected == true)
        {
                // Serial.println("Single click long press");
                timePress = 0;
                timePressLimit = 0;
                clicks = 0;
                text="single click LP";
                return "single click LP";
        }

        if (clicks == 2 && timePressLimit != 0 && millis() > timePressLimit && isPressing == false)
        {
                // Serial.println("Double click");
                FadeInOut(0x00, 0x00, 0xff);
                timePress = 0;
                timePressLimit = 0;
                clicks = 0;
                return "Double click";
        }
        else if (clicks == 2 && timePressLimit != 0 && millis() > timePressLimit && isLongDetected == true)
        {
                // Serial.println("Double click long press");
                timePress = 0;
                timePressLimit = 0;
                clicks = 0;
                return "Double click LP";
        }

        if (clicks == 3 && timePressLimit != 0 && millis() > timePressLimit && isPressing == false)
        {
                // Serial.println("tripple click");
                timePress = 0;
                timePressLimit = 0;
                clicks = 0;
                return "triple click";
        }
        else if (clicks == 3 && timePressLimit != 0 && millis() > timePressLimit && isLongDetected == true)
        {
                // Serial.println("Triple click long press");
                FadeOut2(0xff, 0x77, 0x00);
                Serial.println("going to sleep");
                esp_deep_sleep_start();
                timePress = 0;
                timePressLimit = 0;
                clicks = 0;
                return "triple click LP";
        }
         return text;
        // return "";
}
#endif