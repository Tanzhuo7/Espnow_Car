#ifndef __MOTOR_H
#define __MOTOR_H

#define PWMA    18
#define AIN1    12      //注意启动时为低电平
#define AIN2    14
#define PWMB    27
#define BIN1    26
#define BIN2    19

#define FREQ_Motor        10000    // 频率10KHZ 周期100us
#define CHANNEL_Motor     3        // 通道3
#define RESOLUTION_Motor  10       // 分辨率为10，占空比最大2^10=1024

extern int Motor_Speed;

void Motor_Init(void);
void Motor_Go(void);
void Motor_Up(void);
void Motor_Stop(void);
void Motor_NULL(void);

#endif