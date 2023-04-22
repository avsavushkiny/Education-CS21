/*
Week 000

Set - Game Pong v2

- Arduino Leonardo
- ST7920_128X64

doc A. Savushkin
11.11.21
*/

#include <U8glib.h>

//U8GLIB_ST7920_128X64_4X u8g(13, 11, 12); //e(SCK), r/w(MOSI), rs(CS)
U8GLIB_ST7920_128X64_4X u8g(A5);

//def pins
#define CONTROL_A A0
#define CONTROL_B A1

//def visuals
#define SCREEN_OX 0
#define SCREEN_OY 0
#define SCREEN_WIDTH 127
#define SCREEN_HEIGHT 63
#define PADDLE_WIDTH 4
#define PADDLE_HEIGHT 10
#define PADDLE_PADDING 10
#define BALL_SIZE 3
#define SCORE_PADDING 10

#define EFFECT_SPEED 0.5
#define MIN_Y_SPEED 0.5
#define MAX_Y_SPEED 2

//def value
float ballX = SCREEN_WIDTH / 2;
float ballY = SCREEN_HEIGHT / 2;
float ballSpeedX = 2;
float ballSpeedY = 1;

int paddleLocationA = 0;
int paddleLocationB = 0;
int lastPaddleLocationA = 0;
int lastPaddleLocationB = 0;

int scoreA = 0;
int scoreB = 0;

//pong_log.XBM
const uint8_t pongLogo[] PROGMEM={
  //w 70px, h 20px
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

//setup
void setup()
{
  renderStartMessage();  //draw logo, set font, set print pos, print, delay
}

//rendering start on message
void renderStartMessage()
{
  u8g.firstPage();
	do {	
	  u8g.drawXBMP(29, 16, 70, 20, pongLogo); //x, y, w, h, xbmp

    u8g.setFont(u8g_font_profont10);
    u8g.setPrintPos(30, 43); //x, y
    u8g.print((String) "Atari. 1972");
    
    u8g.setPrintPos(30, 50); //x, y
    u8g.print((String) "Game for two");

	} while (u8g.nextPage());
	delay(2000);
}

//loop
void loop()
{
  calculateMovement();  //paddle location, paddle speed, ball, bouce, score
  renderGraphics();     //function draw and drawScore
  delay(10);            //speed game
}

//calculate
void calculateMovement()
{
  int controlA = analogRead(CONTROL_A);
  int controlB = analogRead(CONTROL_B);

  paddleLocationA = map(controlA, 0, 1023, 0, SCREEN_HEIGHT - PADDLE_HEIGHT);
  paddleLocationB = map(controlB, 0, 1023, 0, SCREEN_HEIGHT - PADDLE_HEIGHT);

  int paddleSpeedA = paddleLocationA - lastPaddleLocationA;
  int paddleSpeedB = paddleLocationB - lastPaddleLocationB;

  ballX += ballSpeedX;
  ballY += ballSpeedY;

  //bounce from top and bottom
  if (ballY >= SCREEN_HEIGHT - BALL_SIZE || ballY <= 0)
  {
    ballSpeedY *= -1;
  }

  //bounce from paddle A
  if (ballX >= PADDLE_PADDING && ballX <= PADDLE_PADDING + BALL_SIZE && ballSpeedX < 0)
  {
    if (ballY > paddleLocationA - BALL_SIZE && ballY < paddleLocationA + PADDLE_HEIGHT)
    {
      ballSpeedX *= -1;

      addEffect(paddleSpeedA);
    }
  }

  //bounce from paddle B
  if (ballX >= SCREEN_WIDTH - PADDLE_WIDTH - PADDLE_PADDING - BALL_SIZE && ballX <= SCREEN_WIDTH - PADDLE_PADDING - BALL_SIZE && ballSpeedX > 0)
  {
    if (ballY > paddleLocationB - BALL_SIZE && ballY < paddleLocationB + PADDLE_HEIGHT)
    {
      ballSpeedX *= -1;

      addEffect(paddleSpeedB);
    }
  }

  //score points if ball hits wall behind paddle
  if (ballX >= SCREEN_WIDTH - BALL_SIZE || ballX <= 0)
  {
    if (ballSpeedX > 0)
    {
      scoreA++;
      ballX = SCREEN_WIDTH / 4;
    }
    if (ballSpeedX < 0)
    {
      scoreB++;
      ballX = SCREEN_WIDTH / 4 * 3;
    }
  }

  //set last paddle locations
  lastPaddleLocationA = paddleLocationA;
  lastPaddleLocationB = paddleLocationB;
}

//draw paddle, center line, ball, field line
void draw()
{
  //draw paddle A
  u8g.drawFrame(PADDLE_PADDING, paddleLocationA, PADDLE_WIDTH, PADDLE_HEIGHT);  //x, y, w, h
  //draw paddle B
  u8g.drawFrame(SCREEN_WIDTH - PADDLE_WIDTH - PADDLE_PADDING, paddleLocationB, PADDLE_WIDTH, PADDLE_HEIGHT);  //x, y, w, h
  //draw center line
  for (int i = 1; i < SCREEN_HEIGHT; i += 4)
  {
    u8g.drawVLine(SCREEN_WIDTH / 2, i, 2);   //x, y, length
  }
  //draw ball
  u8g.drawFrame(ballX, ballY, BALL_SIZE, BALL_SIZE);     //x, y, w, h
  //draw field line
  u8g.drawHLine(SCREEN_OX, SCREEN_OY, SCREEN_WIDTH);     //x, y, length
  u8g.drawHLine(SCREEN_OX, SCREEN_HEIGHT, SCREEN_WIDTH); //x, y, length
}

//effect
void addEffect(int paddleSpeed)
{
  float oldBallSpeedY = ballSpeedY;

  //add effect to ball when paddle is moving while bouncing
  //for every pixel of paddle movement, add or substact EFFECT_SPEED to ballspeed
  for (int effect = 0; effect < abs(paddleSpeed); effect++)
  {
    if (paddleSpeed > 0)
    {
      ballSpeedY += EFFECT_SPEED;
    }
    else
    {
      ballSpeedY -= EFFECT_SPEED;
    }
  }

  //limit to minimum speed
  if (ballSpeedY < MIN_Y_SPEED && ballSpeedY > -MIN_Y_SPEED)
  {
    if (ballSpeedY > 0)
      ballSpeedY = MIN_Y_SPEED;
    if (ballSpeedY < 0)
      ballSpeedY = -MIN_Y_SPEED;
    if (ballSpeedY == 0)
      ballSpeedY = oldBallSpeedY;
  }

  //limit to maximum speed
  if (ballSpeedY > MAX_Y_SPEED)
    ballSpeedY = MAX_Y_SPEED;
  if (ballSpeedY < -MAX_Y_SPEED)
    ballSpeedY = -MAX_Y_SPEED;
}

//draw value score
void drawScore()
{
  //print scores
  u8g.setColorIndex(1);             //black
	u8g.setFont(u8g_font_profont10);  //w 5px, h 9px, use https://github.com/olikraus/u8glib/wiki/fontgroup
  u8g.setPrintPos(15, 10);          //x, y
  u8g.print(scoreA);                //var scoreA
  u8g.setPrintPos(78, 10);          //x, y
  u8g.print(scoreB);                //var scoreB
}

//render graphics
void renderGraphics()
{
  u8g.firstPage();
    do {
    draw();        //paddle, center line, ball, field line 
    drawScore();   //color index, set font, set print pos, print val
    } while (u8g.nextPage());
}