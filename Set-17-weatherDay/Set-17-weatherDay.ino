/*
Week 000

Set - 17 - Weather Day

doc A. Savushkin
24.11.21

\r	возврат каретки в начало строки
\n	новая строка
\t	горизонтальная табуляция

*/

void setup(void)
{

}

void loop(void)
{
    weatherDay();
    delay(1000);
}

int weatherDay()
{
    double cel[360] = {0.0};

    for(int i = 0; i < 360; i++)
    {
        Serial.println((String) "Day " + i + " = " + cel[i]);
    }

    Serial.println("");
    
    return 0;
}