/*
Week 1

Set 2 - Variables

Вывести значения из result

a = 5;
b = 2;
a = a + 1;
result = a - b;

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
    //data
    int a = 5;
    int b = 2;
    a = a + 1;
    int result = a - b;
    
    //output data
    Serial.println((String) "Result value = " + result);
}