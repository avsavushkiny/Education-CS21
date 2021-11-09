/*
Week 000

Set - Game Pong v2

doc A. Savushkin
09.11.21
*/

#include <U8glib.h>

U8GLIB_ST7920_128X64_4X u8g(13, 11, 12); //e(SCK), r/w(MOSI), rs(CS)

//Define Pins
#define OLED_RESET 4
#define BEEPER 3
#define CONTROL_A A2
#define CONTROL_B A3

//Define Visuals
#define FONT_SIZE 2
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

int paddleLocationA = 0;
int paddleLocationB = 0;

float ballX = SCREEN_WIDTH / 2;
float ballY = SCREEN_HEIGHT / 2;
float ballSpeedX = 2;
float ballSpeedY = 1;

int lastPaddleLocationA = 0;
int lastPaddleLocationB = 0;

int scoreA = 0;
int scoreB = 0;

//Setup
void setup()
{
  splash();
}

//Splash Screen
void splash()
{
  u8g.firstPage();
  do {
  u8g.setColorIndex(1);
  u8g.setFont(u8g_font_profont10);
  u8g.drawStr(10, 35, "press start");
  u8g.drawStr(10, 45, "Move paddle to start!");
  } while (u8g.nextPage());
}

//Loop
void loop()
{
  int controlA = analogRead(CONTROL_A);
  int controlB = analogRead(CONTROL_B);

  /*while (abs(controlA - analogRead(CONTROL_A) + controlB - analogRead(CONTROL_B)) < 10)
  {
    // show as long as the total absolute change of
    // both potmeters is smaler than 5
  }*/

  calculateMovement();
  drawRender();
  delay(10);
}

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

void draw()
{
  //draw paddle A
  u8g.drawFrame(PADDLE_PADDING, paddleLocationA, PADDLE_WIDTH, PADDLE_HEIGHT);
  //draw paddle B
  u8g.drawFrame(SCREEN_WIDTH - PADDLE_WIDTH - PADDLE_PADDING, paddleLocationB, PADDLE_WIDTH, PADDLE_HEIGHT);
  //draw center line
  for (int i = 0; i < SCREEN_HEIGHT; i += 4)
  {
    u8g.drawVLine(SCREEN_WIDTH / 2, i, 2);
  }
  //draw ball
  u8g.drawFrame(ballX, ballY, BALL_SIZE, BALL_SIZE);
  //draw line
  u8g.drawHLine(0, 0, 127);
  u8g.drawHLine(0, 63, 127);
}

void addEffect(int paddleSpeed)
{
  float oldBallSpeedY = ballSpeedY;

  //add effect to ball when paddle is moving while bouncing.
  //for every pixel of paddle movement, add or substact EFFECT_SPEED to ballspeed.
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

void drawScore()
{
  //print scores
  u8g.setColorIndex(1);
	u8g.setFont(u8g_font_profont10);
  u8g.setPrintPos(10, 10);
  u8g.print(scoreA);
  u8g.setPrintPos(73, 10); //+1 because of dotted line.
  u8g.print(scoreB);
}

void drawRender()
{
  u8g.firstPage();
    do {
    draw();
    drawScore();
    } while (u8g.nextPage());
}