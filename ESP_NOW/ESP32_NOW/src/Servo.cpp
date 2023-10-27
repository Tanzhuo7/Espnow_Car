#include <Arduino.h>
#include "PS2.h"
#include "Servo.h"

Servo my_servo;         // 定义 Servo 对象
int value_Servo;
//20ms 周期内，高电平持续时长 0.5-2.5 ms，对应 0-180 度舵机角度。
//对应 0.5ms（0.5ms/(20ms/256)）
// int min_width = 0.5 / 20 * pow(2, RESOLUTION);
// //对应 2.5ms（2.5ms/（20ms/256））
// int max_width = 2.5 / 20 * pow(2, RESOLUTION);

void Servo_Init(void)
{
    analogSetAttenuation(ADC_11db);       // 配置衰减器
    analogReadResolution(RESOLUTION);     // 设置 ADC 分辨率
    ledcSetup(CHANNEL, FREQ, RESOLUTION); // 用于设置 LEDC 通道的频率和分辨率
    ledcAttachPin(SERVO, CHANNEL);        // 将通道与对应的引脚连接

    ESP32PWM::allocateTimer(0);           // 分配硬件定时器
    my_servo.setPeriodHertz(FREQ);        // 设置频率
    my_servo.attach(SERVO, 500, 2500);    // 关联 servo 对象与  GPIO 引脚，设置脉宽范围
}

void Servo_Go(void)
{
    // // 将 ADC 的值映射到舵机的转动范围
    // value_Servo = map(analogRead(PS2_X), 0, pow(2, RESOLUTION), min_width, max_width);
    // ledcWrite(CHANNEL, value_Servo);

    value_Servo = map(analogRead(PS2_X), 0, pow(2, RESOLUTION), 0, 180);
    
    if((analogRead(PS2_X) >= 2200) || (analogRead(PS2_X) <= 1600))
    {
        my_servo.write(value_Servo);
    }
    else{my_servo.write(90);}
}