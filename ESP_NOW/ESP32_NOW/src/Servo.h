#include <Arduino.h>
#include <ESP32Servo.h>

#ifndef __SERVO_H
#define __SERVO_H

#define RESOLUTION  12  //分辨率
#define SERVO       13  //舵机引脚
#define CHANNEL     0   //舵机通道
#define FREQ        50  //频率

extern int value_Servo;

void Servo_Init(void);
void Servo_Go(void);

#endif
