/*
Week 000

Set - Random

doc A. Savushkin
18.01.22
*/

int a;
int b = 4;

void setup(void)
{
}

void loop(void)
{
    do
    {
        a = random(2, 126);
    } while (a % b != 0);

    Serial.println(a);
    delay(1000);
}