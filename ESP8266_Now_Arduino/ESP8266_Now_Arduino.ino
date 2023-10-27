#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <espnow.h>
#include <Servo.h>

#define Servo1   4//定义舵机引脚(D2)
#define PWMA    12//(D6)
#define AIN1    2//(D4)
#define AIN2    0//(D3)
#define PWMB    15//(D8)
#define BIN1    5//(D1)
#define BIN2    13//(D7)
#define LED     14//(D5)
#define BUZZER  1//(D10 TX)

Servo my_Servo;   //定义舵机的对象

/********************************************ESP_NOW********************************************************************/
// 创建一个结构体接收数据
typedef struct struct_message {
  // char a[32];
  int Servo_data;
  int Motor_data;
  // float c;
  // bool d;
} struct_message;
// 创建一个结构体变量
struct_message myData;

// 回调函数,当收到消息时会调用该函数
void OnDataRecv(uint8_t * mac, uint8_t *incomingData, uint8_t len) {
  memcpy(&myData, incomingData, sizeof(myData));
  Serial.print("收到的字节长度: ");
  Serial.println(len);
  Serial.print("Servo_data: ");
  Serial.println(myData.Servo_data);
  Serial.print("Motor_data: ");
  Serial.println(myData.Motor_data);
/************************************************************舵机***********************************/
  int value_Servo = myData.Servo_data;
  if((value_Servo >= 90) || (value_Servo <= 70))
  {
    my_Servo.write(value_Servo);
  }
  else{my_Servo.write(90);}
/***********************************************************电机*********************************/
  int Motor_Speed = myData.Motor_data;
  int value_Motor; 
  if(Motor_Speed > 0)
  {
    value_Motor = map(Motor_Speed, 0, 100, 0, 1024);

    digitalWrite(AIN1, LOW);
    digitalWrite(AIN2, HIGH);
    digitalWrite(BIN1, LOW);
    digitalWrite(BIN2, HIGH);

    analogWrite(PWMA,value_Motor);
    analogWrite(PWMB,value_Motor);
  }
  else if(Motor_Speed < 0)
  {
    value_Motor = map(-Motor_Speed, 0, 100, 0, 1024);

    digitalWrite(AIN1, HIGH);
    digitalWrite(AIN2, LOW);
    digitalWrite(BIN1, HIGH);
    digitalWrite(BIN2, LOW);

    analogWrite(PWMA,value_Motor);
    analogWrite(PWMB,value_Motor);
  }
  else if(myData.Motor_data == 0)
  {
    value_Motor = map(Motor_Speed, 0, 100, 0, 1024);

    digitalWrite(AIN1, LOW);
    digitalWrite(AIN2, LOW);
    digitalWrite(BIN1, LOW);
    digitalWrite(BIN2, LOW);

    analogWrite(PWMA,value_Motor);
    analogWrite(PWMB,value_Motor);
    Serial.println("!!!!!!!!!!!");
  }
}

/******************************************Servo**********************************************************/

void setup() {
  Serial.begin(115200);  // 初始化串口波特率

  pinMode(Servo1,OUTPUT);
  my_Servo.attach(Servo1,500,2500,1500);       //连接舵机
  my_Servo.write(90);            //初始化舵机90度

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

  analogWriteRange(1024);//修改PWM分辨率
  analogWriteFreq(1000);//修改PWM频率

  // 设置wifi模式
  WiFi.mode(WIFI_STA);

  // 初始化esp-now
  if (esp_now_init() != 0) {
    Serial.println("ESP_NOW初始化失败");
    return;
  }

  //注册接收信息的回调函数
  esp_now_register_recv_cb(OnDataRecv);
}

void loop() {

}
