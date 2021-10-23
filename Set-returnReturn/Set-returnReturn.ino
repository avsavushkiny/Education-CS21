/*
Week 000

Set - Return return

doc A. Savushkin
23.10.21
*/

void setup(void)
{
    //port speed
    Serial.begin(9600);
}

//function a + b
int add(int a, int b)
{
   return a + b;
}
 
//function c * d
int multiply(int c, int d)
{
   return c * d;
}

void loop(void)
{
    Serial.println(add(7, 8));
    Serial.println(multiply(4, 5));

    Serial.println(add(2 + 3, 4 * 5));

    int x = 4;
    Serial.println(add(x, x));

    Serial.println(add(1, multiply(2, 3)));
    Serial.println(add(1, add(2, 3)));
}