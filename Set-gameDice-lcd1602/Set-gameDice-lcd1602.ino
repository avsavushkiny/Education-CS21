/*
Week 000

Set - Dice

doc A. Savushkin
25.01.22
*/

#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2); //Se

int8_t rndDice[3] = {0};

void setup()
{
    lcd.begin(16, 2);
    lcd.clear();
}

void loop()
{
    startGame();
}

void startGame()
{
    for (int a = 0; a <= 3; a++)
    {
        rndDice[a] = random(1, 7);
        delay(150);
    }

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print((String) rndDice[0] + " " + rndDice[1] + " " + rndDice[2]);
}

void startPage()
{

}

void overPage()
{

}

void debug()
{
    Serial.print(" Game Dino was do");  
} 