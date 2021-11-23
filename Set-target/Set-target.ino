char target[] = "hello";

void setup()
{
    Serial.begin(9600);
}

void loop()
{
    if (Serial.available() > 0)
    {
        if (Serial.find(target))
            Serial.println("found");
    }
}