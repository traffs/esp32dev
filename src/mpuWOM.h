#include "Wire.h"
#include <Arduino.h>

#define MPU6050_ADDR              0x68 // Alternatively set AD0 to HIGH  --> Address = 0x69
#define MPU6050_ACCEL_CONFIG      0x1C // Accelerometer Configuration Register
#define MPU6050_PWR_MGT_1         0x6B // Power Management 1 Register
#define MPU6050_INT_PIN_CFG       0x37 // Interrupt Pin / Bypass Enable Configuration Register
#define MPU6050_INT_ENABLE        0x38 // Interrupt Enable Register
#define MPU6050_LATCH_INT_EN      0x05 // Latch Enable Bit for Interrupt 
#define MPU6050_ACTL              0x07 // Active-Low Enable Bit
#define MPU6050_WOM_EN            0x06 // Wake on Motion Enable bit
#define MPU6050_WOM_THR           0x1F // Wake on Motion Threshold Register
#define MPU6050_MOT_DUR           0x20 // Motion Detection Duration Register
#define MPU6050_ACCEL_INTEL_CTRL  0x69 // Accelaration Interrupt Control Register
#define MPU6050_SIGNAL_PATH_RESET 0x68 // Signal Path Reset Register

byte interruptPin=18;
byte ledPin=5;
volatile bool accEvent = false;

void writeRegister(uint16_t reg, byte value){
  Wire.beginTransmission(MPU6050_ADDR);
  Wire.write(reg);
  Wire.write(value);
  Wire.endTransmission();
}

void setInterrupt(byte threshold){
//writeRegister(MPU6050_SIGNAL_PATH_RESET, 0b00000111);  // not(?) needed
//writeRegister(MPU6050_INT_PIN_CFG, 1<<MPU6050_ACTL); // 1<<MPU6050_LATCH_INT_EN
  writeRegister(MPU6050_ACCEL_CONFIG, 0b00000001);
  writeRegister(MPU6050_WOM_THR, threshold);
  Serial.println(threshold);
  writeRegister(MPU6050_MOT_DUR, 0b00000001);  // set duration (LSB = 1 ms)
//writeRegister(MPU6050_ACCEL_INTEL_CTRL, 0x15);  // not needed (?)
  writeRegister(MPU6050_INT_ENABLE, 1<<MPU6050_WOM_EN);
}

void motion(){
  accEvent = true;
  detachInterrupt(2);
}

void setupWOM() {
  Wire.begin();
  writeRegister(MPU6050_PWR_MGT_1, 0);
  setInterrupt(1); // set Wake on Motion Interrupt / Sensitivity; 1(highest sensitivity) - 255
  pinMode(ledPin, OUTPUT);
  pinMode(interruptPin, INPUT);
  attachInterrupt(digitalPinToInterrupt(interruptPin), motion, RISING);
  digitalWrite(ledPin, HIGH);
}

void loopWOM() {
  //  if(accEvent){
  //   digitalWrite(ledPin, HIGH);
  //   delay(1000);
  //   digitalWrite(ledPin, LOW);
  //   accEvent = false;
  //   attachInterrupt(digitalPinToInterrupt(interruptPin), motion, RISING);   
  // }
}