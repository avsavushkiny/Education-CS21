/*
Week 000

Set - 16 - Pattern Snow Hill

doc A. Savushkin
23.11.21

\r	возврат каретки в начало строки
\n	новая строка
\t	горизонтальная табуляция

*/

void setup(void)
{

}

void loop(void)
{
    patternSnowHill();

    Serial.print("\n");
    delay(500);
}

int patternSnowHill()
{
    for(int i = 1; i <= 5; i++)
    {
        for(int j = 1; j <= i; j++)
        {
            Serial.print("*");
        }
        Serial.print("\n");
    }
    return 0;
}