#include <LiquidCrystal.h>
#include <A7585lib.h>

#include <Wire.h>
#include <stdio.h>
#include <stdlib.h>

#define DEV_ADDRESS 0x46

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);           // select the pins used on the LCD panel

int lcd_key     = 0;
int adc_key_in  = 0;

#define btnRIGHT  0
#define btnUP     1
#define btnDOWN   2
#define btnLEFT   3
#define btnSELECT 4
#define btnNONE   5
float vset=50;
  bool on_off=false;
  uint32_t  tdow;
  uint32_t tl=0;
  bool upd=false,dwd=false;
  float inc=0.01;


A7585 A7585_dev;
void InitNIPM(int device_address)
{
  A7585_dev.Init(device_address);
  A7585_dev.Set_Mode(0);
  A7585_dev.Set_MaxV(80);
  A7585_dev.Set_MaxI(10);
  A7585_dev.Set_RampVs(25);
  A7585_dev.Set_V(50);
}


int read_LCD_buttons(){               // read the buttons
    adc_key_in = analogRead(0);       // read the value from the sensor 

    // my buttons when read are centered at these valies: 0, 144, 329, 504, 741
    // we add approx 50 to those values and check to see if we are close
    // We make this the 1st option for speed reasons since it will be the most likely result

    if (adc_key_in > 1000) return btnNONE; 

    // For V1.1 us this threshold
    if (adc_key_in < 50)   return btnRIGHT;  
    if (adc_key_in < 250)  return btnUP; 
    if (adc_key_in < 450)  return btnDOWN; 
    if (adc_key_in < 650)  return btnLEFT; 
    if (adc_key_in < 850)  return btnSELECT;  

   // For V1.0 comment the other threshold and use the one below:
   /*
     if (adc_key_in < 50)   return btnRIGHT;  
     if (adc_key_in < 195)  return btnUP; 
     if (adc_key_in < 380)  return btnDOWN; 
     if (adc_key_in < 555)  return btnLEFT; 
     if (adc_key_in < 790)  return btnSELECT;   
   */

    return btnNONE;                // when all others fail, return this.
}


void setup() {
  lcd.begin(16, 2);               // start the library
  InitNIPM(DEV_ADDRESS);

  A7585_dev.Set_V(50);
  A7585_dev.Set_Enable(false);

  
}

void loop() {


  
  uint32_t delta;
  char tmp[16];
  float volt1, cur1;
  
   lcd.setCursor(0,0);             // set the LCD cursor   position 
   lcd.print("V-SET:");  		   // print a message on the LCD
   lcd.setCursor(6,0);             // set the LCD cursor   position 
   sprintf(tmp, "%d.%02d", (int)vset, (int)(vset*100)%100);
   lcd.print(tmp);  			   // print a message on the LCD
   lcd.setCursor(11,0);  
   lcd.print("V");  			   // print a message on the LCD

   delta=millis()-tdow;
   lcd.setCursor(15,0);  
   lcd.print(on_off?"*":"-"); 

   cur1 = A7585_dev.GetIout();
   volt1 = A7585_dev.GetVout();
   

   lcd.setCursor(8,1);             // set the LCD cursor   position 
   sprintf(tmp, "%2d.%03duA", (int)cur1,(int32_t) (cur1*1000)%1000);
   lcd.print(tmp);  			   // print a message on the LCD  

   lcd.setCursor(0,1);             // set the LCD cursor   position 
   sprintf(tmp, "%2d.%03dV ", (int)volt1,(int32_t) (volt1*1000)%1000);
   lcd.print(tmp);  				// print a message on the LCD


   
   lcd_key = read_LCD_buttons();   // read the buttons

   switch (lcd_key){               // depending on which button was pushed, we perform an action

       case btnRIGHT:{      				//ON/OFF       
            if (millis()-tl > inc)
            {
              on_off=!on_off;
              A7585_dev.Set_Enable(on_off);
              tl=millis();
            }
            break;
       }
       case btnLEFT:{
             break;
       }    
       case btnUP:{							//INCREASE VOLTAGE

            if (millis()-tl > inc)			//KEY DOWN MANAGE
            {
             if (vset<80)
              vset += 0.01;					//Add 10mV
              A7585_dev.Set_V(vset);		//Set Voltage
             tl=millis();
            }
             break;
       }
       case btnDOWN:{						//DECREASE VOLTAGE
            if (millis()-tl > inc)
            {
             if (vset>22)
              vset -= 0.01;
              A7585_dev.Set_V(vset);
              tl=millis();
            }
             break;
       }
       case btnSELECT:{
             
             
             break;
       }
       case btnNONE:{
             tdow = millis();
             tl=0;
             break;
       }
   }

   //Change increment speed
         if (delta<1000)	
         inc=500;
       if (delta>1000)
         inc=150;
       if (delta>2500)
         inc=0;


}
