/*
Week 000

Set - Hello World, LCD 1602

doc A. Savushkin
20.11.21
*/

#include <LiquidCrystal.h>  //add library

LiquidCrystal lcd(12, 11, 5, 4, 3, 2); //rs, en, d4, d5, d6, d7

void setup()
{
   lcd.begin(16, 2);    //initialization display c16-r2
   lcd.clear();         //clear display
}

void loop()
{
    lcd.setCursor(0, 0);        //place the cursor
    lcd.print("Hello World!");  //output message
}