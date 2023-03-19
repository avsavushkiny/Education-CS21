/* Aliens Invaders Game on Arduino
   Display: 128x64
*/

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Player variables
int playerX = SCREEN_WIDTH / 2;
int playerY = SCREEN_HEIGHT - 10;
int playerWidth = 10;
int playerHeight = 10;

// Alien variables
int alienX = 10;
int alienY = 10;
int alienWidth = 10;
int alienHeight = 10;
int alienSpeed = 2;

// Projectile variables
int projectileX;
int projectileY;
int projectileWidth = 2;
int projectileHeight = 5;
int projectileSpeed = 5;
boolean projectileActive = false;

void setup()
{
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    display.clearDisplay();
    display.display();
}

void loop()
{
    // Clear the screen
    display.clearDisplay();

    // Draw the player
    drawPlayer();

    // Move the alien
    moveAlien();

    // Draw the alien
    drawAlien();

    // Move the projectile
    moveProjectile();

    // Draw the projectile
    drawProjectile();

    // Check for collision between projectile and alien
    if (projectileActive && checkCollision(projectileX, projectileY, projectileWidth, projectileHeight, alienX, alienY, alienWidth, alienHeight))
    {
        alienX = random(SCREEN_WIDTH - alienWidth);
        alienY = random(SCREEN_HEIGHT / 2 - alienHeight);
        projectileActive = false;
    }

    // Check for collision between player and alien
    if (checkCollision(playerX, playerY, playerWidth, playerHeight, alienX, alienY, alienWidth, alienHeight))
    {
        display.setCursor(10, 10);
        display.println("Game Over");
        display.display();
        while (true)
            ;
    }

    // Update the display
    display.display();
    delay(10);
}

void drawPlayer()
{
    display.fillRect(playerX - playerWidth / 2, playerY - playerHeight / 2, playerWidth, playerHeight, WHITE);
}

void moveAlien()
{
    alienX += alienSpeed;
    if (alienX < 0 || alienX > SCREEN_WIDTH - alienWidth)
    {
        alienSpeed = -alienSpeed;
    }
}

void drawAlien()
{
    display.fillRect(alienX, alienY, alienWidth, alienHeight, WHITE);
}

void shoot()
{
    if (!projectileActive)
    {
        projectileX = playerX - projectileWidth / 2;
        projectileY = playerY - playerHeight / 2 - projectileHeight;
        projectileActive = true;
    }
}

void moveProjectile()
{
    if (projectileActive)
    {
        projectileY -= projectileSpeed;
        if (projectileY < 0)
        {
            projectileActive = false;
        }
    }
}

void drawProjectile()
{
    if (projectileActive)
    {
        display.fillRect(projectileX, projectileY, projectileWidth, projectileHeight, WHITE);
    }
}

boolean checkCollision(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2)
{
    if (x1 < x2 + w2 && x1 + w1 > x2 && y1 < y2 + h2 && y1 + h1 > y2)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void loop()
{
    // Check for player input
    if (digitalRead(2) == HIGH)
    { // Left button
        playerX -= 3;
        if (playerX < playerWidth / 2)
        {
            playerX = playerWidth / 2;
        }
    }
    if (digitalRead(3) == HIGH)
    { // Right button
        playerX += 3;
        if (playerX > SCREEN_WIDTH - playerWidth / 2)
        {
            playerX = SCREEN_WIDTH - playerWidth / 2;
        }
    }
    if (digitalRead(4) == HIGH)
    { // Fire button
        shoot();
    }
}
