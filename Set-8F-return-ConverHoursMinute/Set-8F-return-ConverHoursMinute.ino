/*
Week 6

Set 8F return - ConvertHoursMinute

Напишите программу через функции,
которая выдает запрос на ввод значения часов
и возвращает значение в минутах

doc A. Savushkin
19.10.21
*/

void setup()
{
}

void loop()
{
    Serial.println("Enter the number");
    Serial.println(hoursMinute());
    delay(1000);
}

int getValue()
{
    if (Serial.available() > 0)
    {
        return Serial.parseInt();
    }
}

String hoursMinute()
{
    Serial.println((String) "Minute: " + (getValue() * 60));
    return "ok";
}