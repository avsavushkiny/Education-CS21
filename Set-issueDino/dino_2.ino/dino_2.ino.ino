#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 7, 6, 5, 4);

byte dino[8] =
{
  B00000, B00000, B00000, B00111,
  B10111, B11100, B11111, B01010
};

byte nullSprite[8] =
{
  B00000, B00000, B00000, B00000,
  B00000, B00000, B00000, B00000
};

byte cact[8] =
{
  B00000, B00000, B00100, B10100,
  B10110, B10110, B11110, B00110
};

bool dinoOnGround = true;

void setup() {
  lcd.begin(16, 2);
  lcd.createChar(0, dino);
  lcd.createChar(1, nullSprite);
  lcd.createChar(2, cact);
}

void loop() {
  int rnd_a{};
  rnd_a = random(2, 6);

  for (int b = 15; b > -10; b = b - 1)
  {
    //cact_1
    lcd.setCursor(b, 1);
    lcd.write((byte)2);
    lcd.setCursor(b + 1, 1);
    lcd.write((byte)1);
    delay(150);

    //cact_2
    lcd.setCursor(b + rnd_a, 1);
    lcd.write((byte)2);
    lcd.setCursor(b + rnd_a + 1, 1);
    lcd.write((byte)1);

    //key
    if (Serial.available() > 0)
    {
      char key = Serial.read();
      if (key == 'W')
      {
        dinoOnGround = false;
      }
      if (key == 'S')
      {
        dinoOnGround = true;
      }
    }

    //dino
    if (dinoOnGround == false)
    {
      lcd.setCursor(1, 0);
      lcd.write((byte)0);

      lcd.setCursor(1, 1);
      lcd.write((byte)1);
    }
    if (dinoOnGround == true)
    {
      lcd.setCursor(1, 1);
      lcd.write((byte)0);

      lcd.setCursor(1, 0);
      lcd.write((byte)1);
    }

    //game over
    //game over cact_1
    if (dinoOnGround == true && b == 1)
    {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("game over");
      delay(2000);
      lcd.clear();
      break;
    }
    //game over cact_2
    if (dinoOnGround == true && b + rnd_a == 1)
    {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("game over");
      delay(2000);
      lcd.clear();
      break;
    }
  }
}
