/*
Week 000

Issue - Pong

doc A. Savushkin
23.04.22
*/

#include <Arduino.h>
#include <U8g2lib.h>
#include <SPI.h>

U8G2_ST7920_128X64_1_HW_SPI u8g2(U8G2_R0, A5, 8); // 23
//U8GLIB_ST7920_128X64_4X u8g(A5);

int ballX = 128 / 2;
int ballY =  64 / 2;

int ballSpeedX = 2;
int ballSpeedY = 1;

void setup(void)
{
    u8g2.begin();
}

void loop(void)
{
    renderGraphics();
}

// рендер графики
void renderGraphics(void)
{
    u8g2.firstPage();
    do
    {
        debugSerial(ballX, "n");
        drawField();
        debugSerial(ballX, "drawfield");
        drawBall();
        debugSerial(ballX, "drawball");
        drawRacket();
        debugSerial(ballX, "drawracket");
    } while (u8g2.nextPage());
}

// рисуем поле
void drawField(void)
{
    u8g2.drawHLine(0, 0, 128);
    u8g2.drawHLine(0, 63, 128);

    int8_t distGrid = 2;

    for (int8_t a = 0; a < 8; a++)
    {
        u8g2.drawFrame(63, distGrid, 1, 4); // x y w h
        distGrid += 8;
    }

    //drawDebug(10, "field");
}

// рисуем ракетки
void drawRacket(void)
{
    int dataPlayer1 = analogRead(A0); // 18
    int dataPlayer2 = analogRead(A1); // 19

    int dataCalcPlayer1 = dataPlayer1 * (46.0/1023.0);
    int dataCalcPlayer2 = dataPlayer2 * (46.0/1023.0);

    u8g2.drawFrame(0, round(dataCalcPlayer1), 3, 18);
    u8g2.drawFrame(125, round(dataCalcPlayer2), 3, 18);

    //drawDebug(20, "racket");
}

// рисуем мячик
void drawBall(void)
{
    u8g2.drawFrame(ballX, ballY, 2, 2);

    ballX += ballSpeedX;
    ballY += ballSpeedY;

    //drawDebug(30, (String)ballX);

    delay(2000);
}

// пишем дебаг на экране
void drawDebug(int8_t ddistY, String text)
{
    u8g2.setFont(u8g2_font_4x6_tf);
    u8g2.setCursor(10, ddistY);
    u8g2.print(text);
}

void debugSerial(int val, String text)
{
    Serial.println((String) val + text);
}