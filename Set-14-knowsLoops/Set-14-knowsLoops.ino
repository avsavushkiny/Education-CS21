/*
Week 000

Set - 14 - Knows Loops

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
    knowsLoops();

    Serial.print("\n");
    delay(500);
}

int knowsLoops()
{
    for(int i = 0; i < 5; i++)
       Serial.print("C++ knows loops\n");
    Serial.print("C++ knows where to stop\n");
}