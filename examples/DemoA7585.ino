#include <A7585lib.h>


#include <Wire.h>
#include <stdio.h>
#include <stdlib.h>

#define DEV_ADDRESS 0x46

A7585 A7585_dev;
double current_voltage;
double add_step = 1;
void InitNIPM(int device_address)
{
  A7585_dev.Init(device_address);
  A7585_dev.Set_Mode(0);
  A7585_dev.Set_MaxV(80);
  A7585_dev.Set_MaxI(10);
  A7585_dev.Set_RampVs(25);
  A7585_dev.Set_V(50);
}
void setup() {
  Serial.begin(115200);
  Wire.begin();
  Serial.println("Starting A7585 HV demo app. This app will ramp the HV");
  
  InitNIPM(DEV_ADDRESS);
  if (A7585_dev.GetConnectionStatus())
    Serial.println("Probe connection successful");
  else
    Serial.println("Error connecting device ");

  A7585_dev.Set_V(50);
  current_voltage=25;
  A7585_dev.Set_Enable(true);

  
}

void loop() {
  float cvout, ciout;
  if (current_voltage>85) {add_step=-1;}
  if (current_voltage<25) {add_step=1;}
  current_voltage += add_step;
  
  A7585_dev.Set_V(current_voltage);
  cvout = A7585_dev.GetVout();
  ciout = A7585_dev.GetIout();

  Serial.print(" V: "); Serial.print(cvout); Serial.print(" I: "); Serial.println(ciout);
  delay(1000);
}
