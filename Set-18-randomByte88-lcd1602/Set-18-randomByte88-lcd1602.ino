/*
Week 000

Set - 18 - Random byte 8x8 on LCD1602

doc A. Savushkin
24.11.21

\r	возврат каретки в начало строки
\n	новая строка
\t	горизонтальная табуляция

*/

#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

byte massiv[8][8];

int a = 0;
int i = 0;

void setup(void)
{
}

void loop(void)
{
    lcd.begin(16, 2);
    randomSeed(analogRead(0));

    for (a = 0; a < 8; a++)
    {
        for (i = 0; i < 8; i++)
        {
            massiv[i][a] = random(255);
        }

        lcd.createChar(a, massiv[a]);
    }

    outputByte();

    delay(250);
}

int outputByte()
{
    lcd.clear();

    for(int j = 0; j < 8; j++)
    {
        lcd.setCursor(j, 0);  //c, r
        lcd.write((byte)j);
    }
}