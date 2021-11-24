/*
Week 000

Set - 17 - Random Weather Day

doc A. Savushkin
24.11.21

\r	возврат каретки в начало строки
\n	новая строка
\t	горизонтальная табуляция

*/

double cel[360];

void setup(void)
{

}

void loop(void)
{
    rndWeatherDay();
    weatherDay();
    
    delay(1000);
}

int rndWeatherDay()
{
    for(int j = 0; j < 360; j++)
    {
        double rndCel;
        rndCel = random(-40.0, 40.0);
        cel[j] = rndCel;
    }
}

int weatherDay()
{
    for(int i = 0; i < 360; i++)
    {
        Serial.println((String) "Day " + i + " = " + cel[i]);
    }
    Serial.println("");
    return 0;
}