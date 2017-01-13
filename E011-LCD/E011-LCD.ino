

/*
        Title: 321Maker Experiment #011 - LCD
        Description: This program will monitior the humidity and temperature from the DHT11 sensor and display it in the serial monitor.
        Tutorial:  http://321maker.com/e/011-lcd
        Revision Date: October 12, 2016
        Licence: http://321maker.mit-license.org/
        Requirements:  Arduino with 321Maker Shield, 1602 Serial LCD 
        Serial LCD library: https://bitbucket.org/fmalpartida/new-liquidcrystal/downloads/NewliquidCrystal_1.3.4.zip
        
*/
//load libraries
#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>

//Define variables 

#define I2C_ADDR          0x3f        //Define I2C Address where the PCF8574A is
#define BACKLIGHT_PIN      3
#define En_pin             2
#define Rw_pin             1
#define Rs_pin             0
#define D4_pin             4
#define D5_pin             5
#define D6_pin             6
#define D7_pin             7

//Initialise the LCD
LiquidCrystal_I2C      lcd(I2C_ADDR, En_pin,Rw_pin,Rs_pin,D4_pin,D5_pin,D6_pin,D7_pin);

void setup()
 {
    //Define the LCD as 16 column by 2 rows 
    lcd.begin (16,2);
    
    //Switch on the backlight
    lcd.setBacklightPin(BACKLIGHT_PIN,POSITIVE);
    lcd.setBacklight(HIGH);
    
    for (int x = 0; x <15 ; x++){
    lcd.clear();
    //goto first column (column 0) and first line (Line 0)
    lcd.setCursor(x,0);
    
    //Print at cursor Location
    lcd.print("321");
    delay(750);
    }
    //goto first column (column 0) and second line (line 1)
    lcd.setCursor(0,1);
    lcd.print("Maker");
    
 }
 
 
void loop(){
  }
 
