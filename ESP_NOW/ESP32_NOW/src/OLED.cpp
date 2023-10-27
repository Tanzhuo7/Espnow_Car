#include <Arduino.h>
#include <U8g2lib.h>
#include "Wire.h"
#include "PS2.h"
#include "OLED.h"
#include "Servo.h"
#include "Motor.h"

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* clock=*/SCL, /* data=*/SDA, /* reset=*/U8X8_PIN_NONE);//构建OLED

void OLED_Init(void)
{
  u8g2.begin();
  u8g2.enableUTF8Print();//开启 Arduino 平台下支持输出 UTF8 字符集，我们的中文字符就是UTF8；
}

void display_PS2(void)
{
    u8g2.setFont(u8g2_font_unifont_t_chinese2); //设置字体
    u8g2.firstPage();
    do
    {
        u8g2.setCursor(0, 20);
        u8g2.printf("x: %d", analogRead(PS2_X));
        u8g2.setCursor(0, 40);
        u8g2.printf("y: %d", analogRead(PS2_Y));
        u8g2.setCursor(0, 60);
        u8g2.printf("z: %d", digitalRead(SW));
        u8g2.setCursor(60, 40);
        u8g2.printf("%d°", map(analogRead(PS2_X), 0, pow(2, RESOLUTION), 0, 180));
        u8g2.setCursor(90, 40);
        u8g2.printf("%d°", Motor_Speed);
        u8g2.setCursor(90, 20);
        u8g2.printf("%d°", ledcRead(CHANNEL_Motor));
        u8g2.setCursor(90, 60);
        u8g2.printf("%d°", ledcReadFreq(CHANNEL_Motor));
    } while (u8g2.nextPage());
    // delay(20);
}


void test(void)
{
  u8g2.setFont(u8g2_font_unifont_t_chinese2); //设置字体
  u8g2.firstPage();
  do
  {
    u8g2.setCursor(0, 20);
    u8g2.print("helloworld"); // Chinese "Hello World"
    u8g2.setCursor(0, 40);
    u8g2.print("你好世界"); // Chinese "Hello World"
  } while (u8g2.nextPage());
  delay(1000);
}
