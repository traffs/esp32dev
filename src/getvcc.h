#include <arduino.h>

const int Analog_channel_pin= 36;
int ADC_VALUE = 0;
float voltage_value = 0; 

void vcc_init(){
ADC_VALUE = analogRead(Analog_channel_pin);
voltage_value = (ADC_VALUE * 3.3 ) / (4095);
Serial.print(ADC_VALUE);
Serial.print(voltage_value);
Serial.println("volts");
// delay(1000);
}