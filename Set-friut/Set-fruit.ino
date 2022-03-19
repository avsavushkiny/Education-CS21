/*
    Set - fruit
    struct
*/

struct Fruit
{
    int number;
    int quantity;
    String names;
};

Fruit apple {25, 100, "Apple"};
Fruit pear {7, 101, "Pear"};
Fruit orange {12, 102, "Orange"};
Fruit strawberry {1, 5, "Strawberry"};

void setup()
{
}

void loop()
{
    product();
    delay(500);
}

void product()
{
    if (Serial.available() > 0)
    {

        int data = Serial.parseInt();

        if (data == 25)
        {
            Serial.println((String)apple.names + ", " + apple.quantity);           
        }
        else if (data == 7)
        {
            Serial.println((String) pear.names + ", " + pear.quantity);
        }
        else if (data == 12)
        {
            Serial.println((String) orange.names + ", " + orange.quantity);
        }
        else if (data == 1)
        {
            Serial.println((String) strawberry.names + ", " + strawberry.quantity);   
        }

        else
        {
            Serial.println("The product was not found.");    
        }
    }
}