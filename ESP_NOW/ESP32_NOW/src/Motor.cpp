#include <Arduino.h>
#include <Ticker.h>
#include "Motor.h"
#include "PS2.h"
#include <ESP32Servo.h>
#include "Servo.h"

 /*
 *TB6612电机驱动模块     运行状态    AIN1    AIN2    BIN1     BIN2
 * 电机A                正转（调速） 0        1                
 * 电机A                反转（调速） 1        0            
 * A空转                            0        0
 * A刹车                            1        1
 * 电机B                正转（调速）                  0        1
 * 电机B                反转（调速）                  1        0
 * B空转                                             0        0
 * B刹车                                             1        1        
 */

int value_Motor;
int Motor_Speed;

void Motor_Init(void)
{
    pinMode(PWMA, OUTPUT);
    pinMode(AIN1, OUTPUT);
    pinMode(AIN2, OUTPUT);
    pinMode(PWMB, OUTPUT);
    pinMode(BIN1, OUTPUT);
    pinMode(BIN2, OUTPUT);

    digitalWrite(AIN1, LOW);
    digitalWrite(AIN2, LOW);
    digitalWrite(BIN1, LOW);
    digitalWrite(BIN2, LOW);

    ledcSetup(CHANNEL_Motor, FREQ_Motor, RESOLUTION_Motor); // 设置通道 
    ledcAttachPin(PWMA, CHANNEL_Motor);                     // 将通道与对应的引脚连接
    ledcAttachPin(PWMB, CHANNEL_Motor);                     // 将通道与对应的引脚连接

    ESP32PWM::allocateTimer(1);                             // 分配硬件定时器
    ledcWrite(CHANNEL_Motor,0);                             //通道1占空比设置为0
}

void Motor_Go(void)
{
    
    if((analogRead(PS2_Y) >= 2000))
    {
        digitalWrite(AIN1, LOW);
        digitalWrite(AIN2, HIGH);
        digitalWrite(BIN1, LOW);
        digitalWrite(BIN2, HIGH);

        Motor_Speed = map(analogRead(PS2_Y), 2000, pow(2, RESOLUTION), 0, 100);
        value_Motor = map(Motor_Speed, 0, 100, 0, pow(2, RESOLUTION_Motor));

        ledcWrite(CHANNEL_Motor,value_Motor);
    }
    else
    {
        Motor_NULL();
    }
}

void Motor_Up(void)
{
    //value_Motor = map(analogRead(PS2_Y), 0, pow(2, RESOLUTION_Motor), 0, 100);
    if((analogRead(PS2_Y) <= 1500))
    {
        digitalWrite(AIN1, HIGH);
        digitalWrite(AIN2, LOW);
        digitalWrite(BIN1, HIGH);
        digitalWrite(BIN2, LOW);

        Motor_Speed = -map(analogRead(PS2_Y), 1500, 0, 0, 100);
        value_Motor = map(-Motor_Speed, 0, 100, 0, pow(2, RESOLUTION_Motor));

        ledcWrite(CHANNEL_Motor,value_Motor);
    }
    else
    {
        Motor_NULL();
    }
}

void Motor_Stop(void)
{
    digitalWrite(AIN1, HIGH);
    digitalWrite(AIN2, HIGH);
    digitalWrite(BIN1, HIGH);
    digitalWrite(BIN2, HIGH);
}

void Motor_NULL(void)
{
    digitalWrite(AIN1, LOW);
    digitalWrite(AIN2, LOW);
    digitalWrite(BIN1, LOW);
    digitalWrite(BIN2, LOW);
    Motor_Speed = 0;
    ledcWrite(CHANNEL_Motor,0);
}

