/*
Week 5

Set 12F return - Astronomical calculator

Напишите программу, в которой функция loop вызывает функцию,
которая в качестве аргумента принимает расстояние в
световых годах и возвращает расстояние в астрономических
единицах:

Enter the number of light years: 4.2
4.2 light years = 265608 astronomical units

1 световой год = 63240 астрономических единиц

stu D. Kozin, doc A. Savushkin
23.10.21
*/

//prototype
float getValue();
void astroCalc(float x);

void setup()
{
    Serial.begin(9600);
}

//caller
void loop()
{
    float a = getValue(); //call function getValue
    astroCalc(a);         //call function astroCalc
    
    delay(200);
}

float getValue()
{
    Serial.println("Please enter the number of light years:"); //message
    
    if (Serial.available() > 0)
    {
        return (Serial.parseFloat());
    }
}

void astroCalc(float x)
{
    Serial.println((String) "Enter the number of light years: " + x);
    Serial.println((String)x + " light years = " + (x * 63240) + " astronomical units");
    Serial.println(" ");
}