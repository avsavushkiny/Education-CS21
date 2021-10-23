/*
Week 000

Set - Selection Number

doc A. Savushkin
23.10.21
*/

void setup(void)
{
    //port speed
    Serial.begin(9600);
}

void loop(void)
{
    int a;

    Serial.println("Enter the number");
    a = Serial.parseInt();

    if (a > 15)
    {
        Serial.print((String)a + " is greater than 15");
    }

    else
    {
        Serial.print((String)a + " is not greater than 15");
    }
}