#include <Arduino.h>
#include "PS2.h"

void PS2_Init(void)
{
  pinMode(PS2_X, INPUT);
  pinMode(PS2_Y, INPUT);
  pinMode(SW, INPUT_PULLUP);
}

/*  Serial.printf("x: %d, y: %d, z: %d\n", analogRead(PS2_X), analogRead(PS2_Y), digitalRead(SW));
  Serial.println("-------------------------------------------");

  delay(2000);*/