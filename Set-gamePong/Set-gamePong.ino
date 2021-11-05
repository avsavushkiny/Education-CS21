/*
Week 000

Set - Game Pong

doc A. Savushkin
23.10.21
*/

#include <U8glib.h>

U8GLIB_ST7920_128X64_4X u8g(13, 11, 12); //e(SCK), r/w(MOSI), rs(CS)

// Define the PINS you're goint to use on your Arduino Nano
int controller1 = 2; // ANALOG 2
int controller2 = 3; // ANALOG 3
int ledPin = 13;     // DIGITAL 13
int btnPin = 5;      // DIGITAL 5 - on Start game

// Define variables
int buttonState = 0; // HIGH = Pressed
int gameState = 0;   // 0 = Home, 1 = Game, 2 = End

int controllerValue1 = 0; // variable to store the value coming from the potentiometer
int controllerValue2 = 0; // variable to store the value coming from the potentiometer

int paddlePositionPlayer1 = 0;
int paddlePositionPlayer2 = 0;

int scorePlayer1 = 0;
int scorePlayer2 = 0;

int ballX = 128 / 2;
int ballY = 64 / 2;
int ballSpeedX = 2;
int ballSpeedY = 1;

const uint8_t pongLogo[] PROGMEM={ //-- width: 70, height: 20
  0x00, 0x00, 0x00, 0x06, 0x00, 0x60, 0x00, 0x00, 0x00, 0xFE, 0x03, 0xE0, 
  0x7F, 0x00, 0xFC, 0x03, 0xE0, 0x1F, 0xFE, 0x0F, 0xF0, 0xFF, 0x01, 0xFE, 
  0x07, 0xF0, 0x1F, 0xFE, 0x0F, 0xF8, 0xFF, 0x03, 0xFF, 0x0F, 0xFC, 0x1F, 
  0x1E, 0x1E, 0x7C, 0xE0, 0x03, 0x0F, 0x0F, 0xFC, 0x19, 0x1E, 0x1E, 0x3E, 
  0xC0, 0x87, 0x07, 0x1E, 0x3E, 0x00, 0x1E, 0x1C, 0x1E, 0x80, 0x8F, 0x07, 
  0x1E, 0x1F, 0x00, 0x1E, 0x1E, 0x0F, 0x00, 0x8F, 0x07, 0x1E, 0x0F, 0x00, 
  0x1E, 0x1F, 0x0F, 0x00, 0x8F, 0x07, 0x1E, 0x0F, 0x00, 0xFE, 0x0F, 0x0F, 
  0x00, 0x8F, 0x07, 0x1E, 0x0F, 0x00, 0xFE, 0x07, 0x0F, 0x00, 0x8F, 0x07, 
  0x1E, 0x8F, 0x1F, 0xFE, 0x03, 0x0F, 0x00, 0x8F, 0x07, 0x1E, 0x8F, 0x1F, 
  0x1E, 0x00, 0x1E, 0x00, 0x8F, 0x07, 0x1E, 0x8F, 0x1F, 0x1E, 0x00, 0x1E, 
  0x80, 0x87, 0x07, 0x1E, 0x1F, 0x1E, 0x1E, 0x00, 0x7E, 0xC0, 0x87, 0x07, 
  0x1E, 0x3E, 0x1E, 0x1E, 0x00, 0xFC, 0xF9, 0x83, 0x07, 0x1E, 0x7C, 0x1E, 
  0x1E, 0x00, 0xF8, 0xFF, 0x81, 0x07, 0x1E, 0xFC, 0x1F, 0x1E, 0x00, 0xE0, 
  0xFF, 0x80, 0x07, 0x1E, 0xF0, 0x1F, 0x1E, 0x00, 0x80, 0x3F, 0x80, 0x07, 
  0x1E, 0xE0, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

void setup()
{
    pinMode(ledPin, OUTPUT);
    pinMode(btnPin, INPUT);

    digitalWrite(ledPin, HIGH);

    drawPongLogo();
}

void loop()
{
    // Read controller value and calculate paddle position
    controllerValue1 = analogRead(controller1);
    controllerValue2 = analogRead(controller2);

    paddlePositionPlayer1 = controllerValue1 * (46.0 / 1023.0);
    paddlePositionPlayer2 = controllerValue2 * (46.0 / 1023.0);

    // Set button state
    buttonState = digitalRead(btnPin);

    if (buttonState == HIGH && gameState == 0)
    {
        gameState = 1;
        delay(250);
    }

    else if (buttonState == HIGH && (gameState == 1 || gameState == 2))
    {
        gameState = 0;
        scorePlayer1 = 0;
        scorePlayer2 = 0;
        ballX = 128 / 2;
        ballY = 64 / 2;
        delay(250);
    }

    if (gameState == 0)
    {
        //output start message
        drawStartMessage(); //+
    }

    if (gameState == 1)
    {
        u8g.firstPage();
        do {
            drawField(scorePlayer1, scorePlayer2); //+
            collisionControl();
            drawBall();
        } while (u8g.nextPage());
    }

    if (gameState == 2)
    {
        u8g.firstPage();
        do {
        drawField(scorePlayer1, scorePlayer2);
        
        u8g.setColorIndex(1);
        u8g.setFont(u8g_font_6x12);

        if (scorePlayer1 == 10)
        {
            u8g.setPrintPos(15, 30);
        }
        else if (scorePlayer2 == 10)
        {
            u8g.setPrintPos(77, 30);
        }
        u8g.print("winner!");
        } while (u8g.nextPage());

        delay(2000);
        setup();
    }
}

void drawField(int score1, int score2) //+
{
        u8g.setColorIndex(1);
        u8g.drawFrame(0, round(paddlePositionPlayer1), 2, 18);   //x, y, w, h
        u8g.drawFrame(126, round(paddlePositionPlayer2), 2, 18); //x, y, w, h

	    u8g.setFont(u8g_font_profont10);
        u8g.setPrintPos(10, 8);
        u8g.print(score1);
        
        u8g.setPrintPos(73, 8);
        u8g.print(score2);

        uint8_t dist = 2;
        for (uint8_t a = 0; a < 8; a++)
        {
            u8g.drawFrame(63, dist, 1, 4);
            dist = dist + 8;
        }
        
        u8g.drawHLine(0, 0, 127);
        u8g.drawHLine(0, 63, 127);
}

void collisionControl() //+
{
    //bounce from top and bottom
    if (ballY >= 64 - 2 || ballY <= 0)
    {
        ballSpeedY *= -1;
    }

    //score points if ball hits wall behind player
    if (ballX >= 128 - 2 || ballX <= 0)
    {
        if (ballSpeedX > 0)
        {
            scorePlayer1++;
            ballX = 128 / 4;
        }
        if (ballSpeedX < 0)
        {
            scorePlayer2++;
            ballX = 128 / 4 * 3;
        }
        if (scorePlayer1 == 10 || scorePlayer2 == 10)
        {
            gameState = 2;
        }
    }

    //bounce from player1
    if (ballX >= 0 && ballX <= 2 && ballSpeedX < 0)
    {
        if (ballY > round(paddlePositionPlayer1) - 2 && ballY < round(paddlePositionPlayer1) + 18)
        {
            ballSpeedX *= -1;
        }
    }
    //bounce from player2
    if (ballX >= 128 - 2 - 2 && ballX <= 128 - 2 && ballSpeedX > 0)
    {
        if (ballY > round(paddlePositionPlayer2) - 2 && ballY < round(paddlePositionPlayer2) + 18)
        {
            ballSpeedX *= -1;
        }
    }
}

void drawBall()
{
    u8g.drawFrame(ballX, ballY, 2, 2);

    ballX += ballSpeedX;
    ballY += ballSpeedY;

    delay(50); //speed game
}

void drawStartMessage(void) //+
{
	u8g.firstPage();
    do {	
	    u8g.setColorIndex(1); 
	    u8g.setFont(u8g_font_profont10);
	    u8g.drawStr(37, 35, "press start");
        
		delay(50); 
	} while (u8g.nextPage());
}

void drawPongLogo() //+
{
    u8g.firstPage();
	do {	
	u8g.drawXBMP(29, 16, 70, 20, pongLogo); //x, y, w, h, xbmp

    u8g.setFont(u8g_font_profont10);
    u8g.setPrintPos(29, 43); //x, y
    u8g.print((String) "Atari. 1972");
    
    u8g.setPrintPos(29, 50); //x, y
    u8g.print((String) "Boy. 2021");

	} while (u8g.nextPage());
	delay(2000);
}