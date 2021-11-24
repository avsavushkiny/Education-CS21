/*
Week 000

Set - 18 - Random byte on LCD1602

doc A. Savushkin
24.11.21

\r	возврат каретки в начало строки
\n	новая строка
\t	горизонтальная табуляция

*/

#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

byte massiv[8][1];

void setup(void)
{
}

void loop(void)
{
    lcd.begin(16, 2);
    randomSeed(analogRead(0));

    for (int i = 0; i < 8; i++)
    {
        massiv[i][0] = random(255);
    }

    outputByte();

    delay(250);
}

int outputByte()
{
    lcd.clear();
    lcd.createChar(0, massiv[0]);
    lcd.setCursor(0, 0); //c, r
    lcd.write((byte)0);
}