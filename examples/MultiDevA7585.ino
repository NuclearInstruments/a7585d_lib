#include <A7585lib.h>


#include <Wire.h>
#include <stdio.h>
#include <stdlib.h>

#define DEV_ADDRESS_BASE 0x40

A7585 A7585_dev[16];


void setup() {
  int i;

  Serial.begin(115200);
  Wire.begin();
  Serial.println("Starting A7585 HV demo app. This app will ramp the HV");

  for (i=0;i<16;i++)
  {
    A7585_dev[i].Init(DEV_ADDRESS_BASE+i);
    A7585_dev[i].Set_Mode(0);
    A7585_dev[i].Set_MaxV(80);
    A7585_dev[i].Set_MaxI(10);
    A7585_dev[i].Set_RampVs(25);
    A7585_dev[i].Set_V(50);
  
    Serial.print("Device ID ");
    Serial.print(DEV_ADDRESS_BASE+i);
    if (A7585_dev[i].GetConnectionStatus())
      Serial.println(" connected");
    else
      Serial.println(" not connected");
    A7585_dev[i].Set_V(50);
    A7585_dev[i].Set_Enable(true);
  }
  
  
  
   
}

void loop() {
  
  int i;
  for (i=0;i<16;i++)
  {
   
    
    if (A7585_dev[i].GetConnectionStatus())
      {Serial.print( DEV_ADDRESS_BASE + i); Serial.print(' ');}
     else
      {Serial.print('-'); Serial.print(' ');}
  }
  Serial.println(' ');
  delay(1000);
}
