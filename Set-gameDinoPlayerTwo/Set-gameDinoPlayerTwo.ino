/*
Week 000

Set - Pac Man mini

doc A. Savushkin
16.01.22
*/

#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void startGame();

byte ghostA[8] =
    {
        B00000,
        B00000,
        B01110,
        B10101,
        B11111,
        B11111,
        B10101,
        B00000};

byte ghostB[8] =
    {
        B00000,
        B00000,
        B01110,
        B11011,
        B10001,
        B11111,
        B10101,
        B00000};

byte pacman[8] =
    {
        B00000,
        B00000,
        B01110,
        B11011,
        B11100,
        B01110,
        B00000,
        B00000};

byte raspberry[8] =
    {
        B00000,
        B00100,
        B01110,
        B11011,
        B10101,
        B01010,
        B00100,
        B00000,
};

byte loss[8] =
    {
        B00000,
        B00000,
        B01010,
        B00000,
        B01110,
        B10001,
        B00000,
        B00000,
};

byte nullChar[8] =
    {
        B00000,
        B00000,
        B00000,
        B00000,
        B00000,
        B00000,
        B00000,
        B00000,
};

byte heart[8] =
    {
        B00000,
        B00000,
        B01010,
        B10101,
        B10001,
        B01010,
        B00100,
        B00000,
};

byte toEat[8] =
    {
        B00000,
        B00000,
        B01010,
        B00000,
        B10001,
        B01110,
        B00000,
        B00000,
};

#define pinButtonP1 8
#define pinButtonP2 9

bool butStateP1 = false;
bool butStateP2 = false;

bool onGame = false;
bool playState = false;

bool eat = false;
bool eatRasp = false;

bool ghostState = false;

int score = 0;
int scoreH = 0;

uint8_t speed = 150;
int8_t lifePacMan = 3;

void setup(void)
{
    lcd.begin(16, 2);
    lcd.clear();

    lcd.createChar(0, nullChar);

    lcd.createChar(1, pacman);

    lcd.createChar(2, ghostA);
    lcd.createChar(3, ghostB);

    lcd.createChar(4, raspberry);

    lcd.createChar(5, loss);

    lcd.createChar(6, heart);
    lcd.createChar(7, toEat);

    pinMode(pinButtonP1, INPUT);
    pinMode(pinButtonP2, INPUT);
}

void loop(void)
{
    butStateP1 = digitalRead(pinButtonP1);
    butStateP2 = digitalRead(pinButtonP2);

    if ((butStateP2 == true) || (butStateP1 == true))
    {
        playState = true;
    }

    if (playState == true)
    {
        startGame();
    }
    else
    {
        startPage();
    }
}

void startPage(void)
{
    int randomSprite;
    randomSprite = random(2, 5);

    for (int b = 15; b >= 8; b--)
    {
        //lcd.clear();

        //text
        lcd.setCursor(2, 0);
        lcd.print((String) "PacMan");

        if (b <= 15)
        {
            lcd.setCursor(2, 1);
            lcd.print("press key");
        }

        if (b <= 11)
        {
            lcd.setCursor(2, 1);
            lcd.print("to again  ");
        }

        //pacman

        lcd.setCursor(0, 0);
        lcd.write((byte)1);

        lcd.setCursor(b, 0);
        lcd.write((byte)randomSprite);

        lcd.setCursor(b + 1, 0);
        lcd.write((byte)0);
        lcd.setCursor(8, 0);
        lcd.write((byte)0);

        delay(150);
    }
}

void startGame(void)
{
    //lcd.clear();

    eat = false;
    eatRasp = false;

    //calculate random
    //random ghost B
    int8_t rndDistB;
    rndDistB = random(2, 10);

    //random heart
    int8_t rndDistHeart;
    rndDistHeart = random(2, 10);

    //random raspberry
    int8_t rndRasp;
    rndRasp = random(2, 10);
    int8_t rndDistRasp;
    rndDistRasp = random(2, 10);

    //fix bug

    debug("rndDistHeart", rndDistHeart);
    debug("rndDistB", rndDistB);
    debug("rndDistRasp", rndDistRasp);
    debug(" ", 000);

    //calculate game
    //main
    for (int a = 15; a >= -10; a--)
    {
        lcd.clear();

        //read button
        butStateP1 = digitalRead(pinButtonP1);
        butStateP2 = digitalRead(pinButtonP2);

        //condition Player 1
        if (butStateP1 == true)
        {
            P1y0();
        }
        else
        {
            P1y1();
        }

        //condition Player 2
        if (butStateP2 == true)
        {
            P2y0();
        }
        else
        {
            P2y1();
        }

        //traffic
        //ghost 1
        lcd.setCursor(a, 1);
        lcd.write((byte)2);
        //lcd.setCursor(a + 1, 1);
        //lcd.write((byte)0);
        //ghost 2
        lcd.setCursor(a + rndDistB, 1);
        lcd.write((byte)2);
        //lcd.setCursor(a + rndDistB + 1, 1);
        //lcd.write((byte)0);
        //heart
        if (eat == false)
        {
            //!eat to
            lcd.setCursor(a + rndDistHeart, 1);
            lcd.write((byte)6);
            //lcd.setCursor(a + rndDistHeart + 1, 1);
            //lcd.write((byte)0);
        }
        else
        {
            eat = true;
            lcd.setCursor(a + rndDistHeart, 1);
            lcd.write((byte)0);
        }

        //raspberry
        if (eatRasp == false)
        {
            lcd.setCursor(a + rndDistRasp, 1);
            lcd.write((byte)4);
            //lcd.setCursor(a + rndDistRasp + 1, 1);
            //lcd.write((byte)0);
        }
        else
        {
            eatRasp = true;
            lcd.setCursor(a + rndDistRasp, 1);
            lcd.write((byte)0);
        }

        //raspberry 2
        /*
        if (rndRasp == 2)
        {
            //!eat to
            if (eatRasp == false)
            {
                lcd.setCursor(a + rndDistRasp, 1);
                lcd.write((byte)4);
                //lcd.setCursor(a + rndDistRasp + 1, 1);
                //lcd.write((byte)0);
            }
            else
            {
                eatRasp = true;
                lcd.setCursor(a + rndDistRasp, 1);
                lcd.write((byte)0);
            }
        }
        */

        //to eat
        //score and to eat heart
        //player P1
        if ((butStateP1 == false) && (a + rndDistHeart == 1) && (eat == false))
        {
            lcd.setCursor(1, 1);
            lcd.write((byte)7); //draw toEat
            score = score + 1;
            eat = true;

            debugLcd("h");

            delay(350);
        }
        //player P2
        if ((butStateP2 == false) && (a + rndDistHeart == 3) && (eat == false))
        {
            lcd.setCursor(3, 1);
            lcd.write((byte)7); //draw toEat
            score = score + 1;
            eat = true;

            debugLcd("h");

            delay(350);
        }

        //to eat raspberry
        //score and to eat raspberry
        //player P1
        if ((butStateP1 == false) && (a + rndDistRasp == 1) && (eatRasp == false))
        {
            lcd.setCursor(1, 1);
            lcd.write((byte)7); //draw toEat
            score = score + 10;
            eatRasp = true;

            debugLcd("r");

            delay(350);
        }
        //player P2
        if ((butStateP2 == false) && (a + rndDistRasp == 3) && (eatRasp == false))
        {
            lcd.setCursor(3, 1);
            lcd.write((byte)7); //draw toEat
            score = score + 10;
            eatRasp = true;

            debugLcd("r");

            delay(350);
        }

        //score
        lcd.setCursor(12, 0);
        lcd.print((String) "$" + score);

        //life

        //speed game
        delay(250); //(speed)
    }

    //dynamic speed
    speed = speed - 2;

    debug("speed ", speed);

    if (speed == 50)
    {
        speed = 150;
    }
}

void overPage(void)
{
}

void P1y1(void)
{
    lcd.setCursor(1, 1);
    lcd.write((byte)1);
    lcd.setCursor(1, 0);
    lcd.write((byte)0);
}

void P1y0(void)
{
    lcd.setCursor(1, 0);
    lcd.write((byte)1);
    lcd.setCursor(1, 1);
    lcd.write((byte)0);
}

void P2y1(void)
{
    lcd.setCursor(3, 1);
    lcd.write((byte)1);
    lcd.setCursor(3, 0);
    lcd.write((byte)0);
}

void P2y0(void)
{
    lcd.setCursor(3, 0);
    lcd.write((byte)1);
    lcd.setCursor(3, 1);
    lcd.write((byte)0);
}

//debug /text, var
void debug(String text, int var)
{
    Serial.println((String)text + var);
}

void debugLcd(String text)
{
    lcd.setCursor(6, 0);
    lcd.print(text);
}