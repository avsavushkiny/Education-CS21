/*
Week 000

Set - 15 - Pattern Number

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
    patternNumber();

    Serial.print("\n");
    delay(500);
}

int patternNumber()
{
    for(int i = 1; i <= 5; i++)
    {
        for(int j = 1; j <= 5; j++)
        {
            Serial.print(i);
        }
        Serial.print("\n");
    }
    return 0;
}