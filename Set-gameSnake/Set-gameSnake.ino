#include <U8glib.h>

U8GLIB_ST7920_128X64_4X u8g(13, 11, 12); //e(SCK), r/w(MOSI), rs(CS)

//button positions and values
int left = 2, right = 3, down = 4, up = 5;
int leftV = 0, rightV = 0, downV = 0, upV = 0;

//snake direction:
//0: left
//1: right
//2: down
//3: up
int snakeDir = 1;

struct gameItem {
	int X; // x position
	int Y;  //y position
};

//diameter of the gameItemSize
int gameItemSize = 4;

//default snake size
unsigned int snakeSize = 5; //5

//array to store all snake body part positions
gameItem snake[100];

//snake food item
gameItem snakeFood;

enum gameState
{
	//gameStates
	setupGame,
	pausedGame,
	inGame,
	gameOver,
};

gameState state = setupGame;

int scoreV = 0;

void draw(void)
{	
	drawSnake();
	drawFood();
	drawScore();
}

void drawScore(void)
{
	//setup font
	u8g.setColorIndex(1);
	u8g.setFont(u8g_font_profont10);
	//add $
	u8g.setPrintPos(0, 8);
	u8g.print("$");
	//add score
	u8g.setPrintPos(6, 8);
	u8g.print(scoreV);
}

void drawGameOver(void)
{
	//create box
	u8g.setColorIndex(1);             //black
	u8g.drawBox(0, 0, 127, 63);       //x, y, w, h
	
	//create message
	u8g.setColorIndex(0);             //white
	u8g.setFont(u8g_font_6x12);		  //font
	u8g.drawStr(37, 35, "game over"); //x, y, message
}

void drawSnake(void)
{
	//head + body Snake
	for (int i = 0; i < snakeSize; i++) {
		u8g.drawFrame(snake[i].X, snake[i].Y, gameItemSize, gameItemSize);

      //head Snake black colour
      if (i == 0) {
      u8g.setColorIndex(1);
      u8g.drawBox(snake[i].X, snake[i].Y, gameItemSize, gameItemSize);
      }
	}
}

void drawFood(void)
{
	//create Food
	u8g.drawBox(snakeFood.X, snakeFood.Y, gameItemSize, gameItemSize);
}

void handleColisions(void)
{
	//snake eats food
	if (snake[0].X == snakeFood.X && snake[0].Y == snakeFood.Y)
	{
		//increase snakeSize
		snakeSize++;
		//score
		scoreV++;
		//regen food
		spawnSnakeFood();
	}

	//snake collides with itself
	else
	{
		for (int i = 1; i < snakeSize; i++) {
			if (snake[0].X == snake[i].X && snake[0].Y == snake[i].Y) {
				state = gameOver;
			}
		}
	}

	//wall collisions
	if ((snake[0].X < 1) || (snake[0].Y < 1) || (snake[0].X > 127) || (snake[0].Y > 63))
	{
		state = gameOver;
	}
}

void spawnSnakeFood(void)
{
	//generate snake Food position
	do {
		snakeFood.X = random(2, 126);
	} while (snakeFood.X % 4 != 0);
	do {
		snakeFood.Y = random(2, 62);
	} while (snakeFood.Y % 4 != 0);
}

void gameSetup(void)
{
	//Reset snake size
	//snake head + snake body
	snakeSize = 5;

	//snakeHead initial position
	int sHeadX;
	int sHeadY;
	
	do {
		sHeadX = random(2, 126);	
	} while (sHeadX % gameItemSize != 0);

	do {
		sHeadY = random(2, 62);
	} while (sHeadY % gameItemSize != 0);

	//set first part of the snake
	snake[0].X = sHeadX;
	snake[0].Y = sHeadY;
  
	//generate positions for the snake's body
	for (int i = 1; i < snakeSize; i++) {
  
		//add random direction to build snake
		//int dir = random(0, 3);

		//if (dir == 0)//means left
		//{
			snake[i].X = snake[i - 1].X - gameItemSize;
			snake[i].Y = snake[i - 1].Y;
		//}

		//else if (dir == 1)//means right
		//{
			snake[i].X = snake[i - 1].X + gameItemSize;
			snake[i].Y = snake[i - 1].Y;
		//}

		//else if (dir == 2)//means up
		//{
			snake[i].X = snake[i - 1].X;
			snake[i].Y = snake[i - 1].Y - gameItemSize;
		//}

		//else if (dir == 3)//means down
		//{
			snake[i].X = snake[i - 1].X;
			snake[i].Y = snake[i - 1].Y + gameItemSize;
		//}
	}

	//generate snake Food position
	spawnSnakeFood();

	//change state to inGame
	state = pausedGame;
}

void handleInput(void)
{
	//read button
	leftV = digitalRead(left);
   rightV = digitalRead(right);
	  upV = digitalRead(up);
	downV = digitalRead(down);

	if (leftV != 0 && snakeDir != 1)
	{
		snakeDir = 0;
	}

	if (rightV != 0 && snakeDir != 0)
	{
		snakeDir = 1;
	}

	if (downV != 0 && snakeDir != 3)
	{
		snakeDir = 2;
	}

	if (upV != 0 && snakeDir != 2)
	{
		snakeDir = 3;
	}	
}

void updateValues(void)
{	
	//update all body parts of the snake excpet the head
	for (int i = snakeSize - 1; i > 0; i--) {
		snake[i] = snake[i - 1];
	}

	//Now update the head
	//move left
	if (snakeDir == 0) {

		snake[0].X -= gameItemSize;
	}
	//move right
	else if (snakeDir == 1) {

		snake[0].X += gameItemSize;
	}

	//move down
	else if (snakeDir == 2) {

		snake[0].Y += gameItemSize;
	}

	//move up
	else if (snakeDir == 3) {

		snake[0].Y -= gameItemSize;
	}
}

void playGame(void)    //rendering
{	
	//processing
	handleColisions();
	handleInput();
	updateValues();
	
	//rendering
	u8g.firstPage();
	do {	
		draw();
		delay(150);             //game speed
	} while (u8g.nextPage());
}

void gamePaused(void)
{
	//read button
	leftV = digitalRead(left);
   rightV = digitalRead(right);
	  upV = digitalRead(up);
	downV = digitalRead(down);

	if ((leftV !=0) || (rightV !=0) || (downV !=0) || (upV !=0))
	{
		state = inGame;
	}

	u8g.firstPage();
	do {
		draw();
	} while (u8g.nextPage());
}

void gameLost(void)
{
	//discharge score
	scoreV = 0;
	//rendering
	u8g.firstPage();
	do {
		drawGameOver();
	} while (u8g.nextPage());
	delay(2000);

	state = setupGame;
}

void boyLogo(void)
{
	//logo w32px h32px
	static const unsigned char game_boy[] = {
	0xff, 0xff, 0xff, 0xff, 0x01, 0x00, 0x00, 0x80, 0x01, 0x00, 0x00, 0x80,
	0x01, 0x00, 0x00, 0x80, 0x01, 0x00, 0x00, 0x80, 0x01, 0x00, 0x00, 0x80,
	0x01, 0x00, 0x00, 0x80, 0x01, 0x00, 0x00, 0x80, 0x01, 0x00, 0x00, 0x80,
	0x01, 0x00, 0x00, 0x80, 0xf9, 0xcf, 0xff, 0xf0, 0xf9, 0xff, 0xff, 0xf8,
	0xf9, 0xff, 0xff, 0xf9, 0x39, 0x7e, 0xf8, 0xbd, 0x3d, 0x3e, 0xf8, 0x9f,
	0xfd, 0x1f, 0xf8, 0x9f, 0xfd, 0x1f, 0xf8, 0x8f, 0xfd, 0x1f, 0xb8, 0x87,
	0x1d, 0x1e, 0x9c, 0x87, 0x1f, 0x3e, 0x9e, 0x83, 0xff, 0xff, 0xdf, 0x83,
	0xff, 0xff, 0xcf, 0x83, 0xff, 0xf3, 0xc3, 0x83, 0x01, 0x00, 0x00, 0x80,
	0x01, 0x00, 0x00, 0x80, 0x01, 0x00, 0x00, 0x80, 0x01, 0x00, 0x00, 0x80,
	0x01, 0x00, 0x00, 0x80, 0x01, 0x00, 0x00, 0x80, 0x01, 0x00, 0x00, 0x80,
	0x01, 0x00, 0x00, 0x80, 0xff, 0xff, 0xff, 0xff,
	};

	//rendering
	u8g.firstPage();
	do {	
	u8g.drawXBM(48, 16, 32, 32, game_boy); //x, y, w, h, xbm
	} while (u8g.nextPage());
	delay(2000);
}

void setup(void)
{
	//Set the pinmodes
	pinMode(left,  INPUT);
	pinMode(right, INPUT);
	pinMode(down,  INPUT);
	pinMode(up,    INPUT);

	// random seed for the random function
	randomSeed(analogRead(0));
	//rendering logo to start gameboard
	boyLogo();
}

void loop(void)
{
	
	//game states
    if (state == setupGame)
	{
		gameSetup();
	}

	if (state == pausedGame)
	{
		gamePaused();
	}

	if (state == inGame)
	{
		playGame();
	}

	if (state == gameOver)
	{
		gameLost();
	}
}