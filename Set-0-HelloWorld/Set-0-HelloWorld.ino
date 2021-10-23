/*
Week 0

Set 0 - Hello World

Prints data to the serial port as human-readable ASCII text. 
This command can take many forms.
Numbers are printed using an ASCII character for each digit.

Serial.print(78) gives "78"
Serial.print(1.23456) gives "1.23"
Serial.print('N') gives "N"
Serial.print("Hello world.") gives "Hello world."

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
    //message
    Serial.print("Hello World");
}