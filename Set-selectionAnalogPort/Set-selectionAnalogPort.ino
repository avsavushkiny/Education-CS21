/*
Week 000

Set - Selection analog port

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
    pinMode(A0, INPUT);

    int analogData = analogRead(A0);

    float voltageData = (5.0 / 1023) * analogData;
    Serial.println(voltageData);
}