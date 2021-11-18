#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2); //rs, en, d4, d5, d6, d7

void setup()
{
   lcd.begin(16,2);
   lcd.clear();
}

void loop()
{
    lcd.print("Hello World!");
}
