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

//Функция add() принимает два целых числа в качестве
//параметров и возвращает их сумму
//Значения a и b определяет caller
int add(int a, int b)
{
    return (a + b);
}

//caller
void loop(void)
{
    //аргументы 7 и 8 передаются в функцию add()
    Serial.println(add(9, 1));
}