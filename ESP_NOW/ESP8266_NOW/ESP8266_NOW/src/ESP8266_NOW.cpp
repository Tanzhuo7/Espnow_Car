// #include <Arduino.h>
// #include <ESP8266WiFi.h>
// #include <espnow.h>
// #include "Motor.h"
// #include <Servo.h>
// #include "ESP8266_NOW.h"

// Servo my_Servo;   //定义舵机的对象

// // 创建一个结构体接收数据
// typedef struct struct_message {
//   int Servo_data;
//   int Motor_data;
// } struct_message;

// // 创建一个结构体变量
// struct_message myData;

// // 回调函数,当收到消息时会调用该函数
// void OnDataRecv(uint8_t * mac, uint8_t *incomingData, uint8_t len) {
//   memcpy(&myData, incomingData, sizeof(myData));
//   Serial.print("收到的字节长度: ");
//   Serial.println(len);
//   Serial.print("Servo_data: ");
//   Serial.println(myData.Servo_data);
//   Serial.print("Motor_data: ");
//   Serial.println(myData.Motor_data);
// /************************************************************舵机***********************************/
//   int value_Servo = myData.Servo_data;
//   if((value_Servo >= 90) || (value_Servo <= 70))
//   {
//     my_Servo.write(value_Servo);
//   }
//   else{my_Servo.write(90);}
// /***********************************************************电机*********************************/
//   int Motor_Speed = myData.Motor_data;
//   int value_Motor; 
//   if(Motor_Speed > 0)
//   {
//     value_Motor = map(Motor_Speed, 0, 100, 0, 1024);

//     digitalWrite(AIN1, LOW);
//     digitalWrite(AIN2, HIGH);
//     digitalWrite(BIN1, LOW);
//     digitalWrite(BIN2, HIGH);

//     analogWrite(PWMA,value_Motor);
//     analogWrite(PWMB,value_Motor);
//   }
//   else if(Motor_Speed < 0)
//   {
//     value_Motor = map(-Motor_Speed, 0, 100, 0, 1024);

//     digitalWrite(AIN1, HIGH);
//     digitalWrite(AIN2, LOW);
//     digitalWrite(BIN1, HIGH);
//     digitalWrite(BIN2, LOW);

//     analogWrite(PWMA,value_Motor);
//     analogWrite(PWMB,value_Motor);
//   }
//   else if(myData.Motor_data == 0)
//   {
//     value_Motor = map(Motor_Speed, 0, 100, 0, 1024);

//     digitalWrite(AIN1, LOW);
//     digitalWrite(AIN2, LOW);
//     digitalWrite(BIN1, LOW);
//     digitalWrite(BIN2, LOW);

//     analogWrite(PWMA,value_Motor);
//     analogWrite(PWMB,value_Motor);
//     Serial.println("!!!!!!!!!!!");
//   }
// }

// void ESP8266_NOW_Init(void)
// {
//     // 设置wifi模式
//      WiFi.mode(WIFI_STA);

//     // 初始化esp-now
//     if (esp_now_init() != 0) {
//       Serial.println("ESP_NOW初始化失败");
//       return;
//     }

//     //注册接收信息的回调函数
//      esp_now_register_recv_cb(OnDataRecv);
// }

// void Servo_Init(void)
// {
//     pinMode(Servo1,OUTPUT);
//     my_Servo.attach(Servo1,500,2500,1500);       //连接舵机
//     my_Servo.write(90);                           //初始化舵机90度
// }