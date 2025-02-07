/*
Week 000

Set - Pac Man mini - LCD1602

doc A. Savushkin
16.01.22 - 23.01.22
*/

#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 7, 6, 5, 4);

void startGame();

byte ghostA[8] = //ghost state false
    {
        B00000,
        B00000,
        B01110,
        B10101,
        B11111,
        B11111,
        B10101,
        B00000};

byte ghostB[8] = //ghost state true
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
#define pinVibration A0

bool butStateP1 = false;
bool butStateP2 = false;

bool onGame = false;
bool playState = false;

bool eat = false;
bool eatRasp = false;

bool ghostState = false;
uint8_t ghostScore = 10;

int score = 0;
int scoreH = 0;

uint8_t speed = 150;
int8_t lifePacMan = 3;

bool vibration = false;

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
    stateGame();
}

void stateGame()
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
    lcd.clear();

    int randomSprite;
    randomSprite = random(2, 5);

    for (int b = 15; b >= 8; b--)
    {
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
    /*
    debug("rndDistHeart", rndDistHeart);
    debug("rndDistB", rndDistB);
    debug("rndDistRasp", rndDistRasp);
    debug(" ", 000);
    */
   
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

        //traffic + ghostState
        if (ghostState == false)
        {
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
        }
        else //if ghostState == true
        {
            //ghost 1
            lcd.setCursor(a, 1);
            lcd.write((byte)3);
            //lcd.setCursor(a + 1, 1);
            //lcd.write((byte)0);
            //ghost 2
            lcd.setCursor(a + rndDistB, 1);
            lcd.write((byte)3);
            //lcd.setCursor(a + rndDistB + 1, 1);
            //lcd.write((byte)0);
        }

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

        //to eat
        //score and to eat heart
        //player P1
        if ((butStateP1 == false) && (a + rndDistHeart == 1) && (eat == false))
        {
            lcd.setCursor(1, 1);
            lcd.write((byte)7); //draw toEat
            score = score + 1;
            eat = true;

            //debugLcd("h");

            delay(350);
        }
        //player P2
        if ((butStateP2 == false) && (a + rndDistHeart == 3) && (eat == false))
        {
            lcd.setCursor(3, 1);
            lcd.write((byte)7); //draw toEat
            score = score + 1;
            eat = true;

            //debugLcd("h");

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
            ghostState = true;

            //debugLcd("r");

            delay(350);
        }
        //player P2
        if ((butStateP2 == false) && (a + rndDistRasp == 3) && (eatRasp == false))
        {
            lcd.setCursor(3, 1);
            lcd.write((byte)7); //draw toEat
            score = score + 10;
            eatRasp = true;
            ghostState = true;

            //debugLcd("r");

            delay(350);
        }

        //ghost score
        if (ghostState == true)
        {
            ghostScore = ghostScore - 1;

            lcd.setCursor(6, 0);
            lcd.print(ghostScore);

            if (ghostScore == 0)
            {
                ghostState = false;
                ghostScore = 10;

                //break;
            }
        }

        //score
        lcd.setCursor(10, 0);
        lcd.print((String) "$" + score);

        //life PacMan and gameOver
        //player P1
        if ((butStateP1 == false) && ((a == 1) || (a + rndDistB == 1)) && (ghostState == false))
        {
            lifePacMan = lifePacMan - 1;

            vibCall();

            if (lifePacMan > 0)
            {
                lifePage();
                break; //out to cycle
            }

            if (lifePacMan == 0)
            {
                overPage();
                break; //out to cycle
            }
        }
        //player P2
        if ((butStateP2 == false) && ((a == 3) || (a + rndDistB == 3)) && (ghostState == false))
        {
            lifePacMan = lifePacMan - 1;

            vibCall();

            if (lifePacMan > 0)
            {
                lifePage();
                break; //out to cycle
            }

            if (lifePacMan == 0)
            {
                overPage();
                break; //out to cycle
            }
        }
        //draw life
        lcd.setCursor(9, 0);
        lcd.print(lifePacMan);

        //to eat ghostB
        //player P1
        if ((butStateP1 == false) && ((a == 1) || (a + rndDistB == 1)) && (ghostState == true))
        {
            //to eat ghostB
            lcd.setCursor(1, 1);
            lcd.write((byte)7);

            score = score + 100;
        }
        //player P2
        if ((butStateP2 == false) && ((a == 3) || (a + rndDistB == 3)) && (ghostState == true))
        {
            //to eat ghostB
            lcd.setCursor(3, 1);
            lcd.write((byte)7);

            score = score + 100;
        }

        //speed game
        delay(speed); //(speed)
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
    lcd.clear();

    lcd.setCursor(6, 0);
    lcd.print("game");
    lcd.setCursor(6, 1);
    lcd.print("over");

    score = 0;
    speed = 150;
    lifePacMan = 3;

    delay(3000);

    playState = false;
    stateGame();
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

void lifePage()
{
    lcd.clear();
    //draw sprite PacMan + text
    lcd.setCursor(5, 0);
    lcd.print("loooser");

    lcd.setCursor(6, 1);
    lcd.write((byte)1);
    lcd.setCursor(7, 1);
    lcd.print((String) " x " + lifePacMan);

    delay(3000);
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

//vibration motor
void vibCall()
{
    pinMode(pinVibration, OUTPUT);

    analogWrite(pinVibration, 255);
    delay(250);
    analogWrite(pinVibration, 0);
}