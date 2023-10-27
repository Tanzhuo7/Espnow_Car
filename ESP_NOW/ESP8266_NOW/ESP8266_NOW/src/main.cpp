#include <Arduino.h>
#include "Motor.h"
#include "ESP8266_NOW.h"

#define LED     14//(D5)
#define BUZZER  1//(D10 TX)


void setup() {
  Serial.begin(115200);  // 初始化串口波特率
  Motor_Init();
  // Servo_Init();
  // ESP8266_NOW_Init();
}

void loop() {

}
