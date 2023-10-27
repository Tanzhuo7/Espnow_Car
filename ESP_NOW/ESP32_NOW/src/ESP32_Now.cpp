#include <Arduino.h>
#include <esp_now.h>
#include <WiFi.h>
#include "ESP32_Now.h"
#include "ESP32_Now.h"
#include "Servo.h"
#include "Motor.h"

uint8_t broadcastAddress[] = {0xD8, 0xBF, 0xC0, 0x07, 0x18, 0x0F};//D8:BF:C0:07:18:0F  // 接收端的MAC地址

// 发送结构体类型
typedef struct struct_message {
  // char a[32];
  int Servo_data;
  int Motor_data;
  // float c;
  // bool d;
} struct_message;

// 创建一个结构体变量
struct_message myData;

//创建esp_now_peer_info_t类型变量存储有关peer方的信息
esp_now_peer_info_t peerInfo;

// 回调函数,函数将在发送消息时执行。此函数告诉我们信息是否成功发送;
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  // Serial.print("\r\n最后一次发送包状态:\t");
  // Serial.println(status == ESP_NOW_SEND_SUCCESS ? "###发送成功###" : "！！！发送失败！！！");//ESP_NOW_SEND_SUCCESS   0成功 1失败
}

void ESP32_Now_Init(void)
{
  // 设置WIFI模式为STA模式，即无线终端(1)
  WiFi.mode(WIFI_STA);

  //  初始化ESP-NOW(2)
  if (esp_now_init() != ESP_OK) {
    Serial.println("！！！！！！！！初始化ESP_NOW错误！！！！！！！");
    return;
  }

  //注册回调函数 OnDataSent
  esp_now_register_send_cb(OnDataSent);
  
  // 注册通信频道 等对体参数配置
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);//地址配置
  peerInfo.channel = 0;  //通道配置
  peerInfo.encrypt = false;//是否加密为False

  //添加peer       
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("！！！！！！！！添加对等体失败！！！！！！！！");
    return;
  }
}

void Send_myData(void) {
  //设置要发送的值
  //strcpy(myData.a, "Hello ESP_NOW");
  myData.Servo_data = value_Servo;
  myData.Motor_data = Motor_Speed;
  //myData.c = 1.2;
  //myData.d = false;
  
  //发送信息到指定ESP32上
  esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));
   
 //判断是否发送成功
  if (result == ESP_OK) {
    // Serial.println("＜（＾－＾）＞    ###发送成功###     ＜（＾－＾）＞");
    Serial.println(value_Servo);
    Serial.println(Motor_Speed);
  }
  else {
    Serial.println("！！！！###发送失败###！！！！");
  }
  delay(2);//毫秒级别响应
}