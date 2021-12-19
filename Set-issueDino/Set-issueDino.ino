/*
Week 000

Set - Issue Dino

doc A. Savushkin
3.12.21
*/

#include <LiquidCrystal.h>             //add library
LiquidCrystal lcd(12, 11, 5, 4, 3, 2); //rs, en, d4, d5, d6, d7

int buttonPin = 8;

byte dino [8]                 //массив символа dino
  {
    B00000,
    B00000,
    B00111,
    B00111,
    B10110,
    B11111,
    B01010,
    B01010,
  };

byte tree [8]                 //массив символа tree
  {
    B00000,
    B00000,
    B00000,
    B00100,
    B00101,
    B10111,
    B11100,
    B00100,
  };

void setup(void)
{
    lcd.begin(16, 2);
    lcd.createChar(7, dino);
    lcd.createChar(6, tree);

    pinMode(buttonPin, INPUT);
}

void loop(void)
{
    if (buttonPin == HIGH)
    {

    }
    else
    {

    }
}

int drawSprite()
{

}

int drawHello()
{
  lcd.setCursor(0, 0);
  lcd.print("Hello World");

  lcd.setCursor(0, 1);
  lcd.print("Alisa");
}