/*
Week 000

Set - Acey Ducey on LCD1602

doc A. Savushkin
2.01.22
*/

#include <LiquidCrystal.h>             //add library
LiquidCrystal lcd(12, 11, 5, 4, 3, 2); //rs, en, d4, d5, d6, d7

int buttonPin = 8;

String versionProgram = "v.1.0"; 

byte dino[8] //массив символа dino
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

void setup(void)
{
    lcd.begin(16, 2);
    lcd.clear();

    pinMode(8, INPUT);
}

void loop(void)
{
    infoPage();
}

void infoPage(void)
{
    for (int a = 6; a >= 0; a--)
    {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("ACEY DUCEY");

        if (a == 6)
        {
            lcd.setCursor(0, 1);
            lcd.print((String) "CARD GAME" + " " + versionProgram);
            delay(1000);
        }

        else if (a == 5)
        {
            lcd.setCursor(0, 1);
            lcd.print((String) "Creat.computing");
        }
        
        else if (a == 4)
        {
            lcd.setCursor(0, 1);
            lcd.print("Morristown, NJ");
        }

        else if (a == 3)
        {
            lcd.setCursor(0, 1);
            lcd.print("B.Palmby, P.View");    
        }

        else if (a == 2)
        {
            lcd.setCursor(0, 1);
            lcd.print("Ported by"); 
        }

        else if (a == 1)
        {
            lcd.setCursor(0, 1);
            lcd.print("GH: avsavushkiny");
        }

        else if (a == 0)
        {
            lcd.setCursor(0, 1);
            lcd.print("Open source, 2022");
        }

        delay(1000);
    }

    //delay(3000);
}

void startPage(void)
{
}

void gamePage(void)
{
}
