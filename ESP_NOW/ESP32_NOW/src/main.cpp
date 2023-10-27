#include <Arduino.h>
#include "OLED.h"
#include "PS2.h"
#include "Servo.h"
#include "Motor.h"
#include "ESP32_Now.h"

void setup(void) {
  Serial.begin(115200);
  Servo_Init();
  OLED_Init();
  PS2_Init();
  Motor_Init();
  ESP32_Now_Init();
}

void loop(void) {
  Servo_Go();
  if((analogRead(PS2_Y) >= 2000))
  {
    Motor_Go();
  }
  else if((analogRead(PS2_Y) <= 1500))
  {
    Motor_Up();
  }
  else
  {
    Motor_NULL();
  }
  display_PS2();
  Send_myData();
}