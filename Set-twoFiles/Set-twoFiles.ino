/*
Week 000

Set -Two files

Разделите код программы на два файла,
программа должна сложить два числа,
а результат вычислений вывести в монитор порта.

doc A. Savushkin
16.10.21
*/

//prototype add_fn
int add_fn(int x, int y);

void setup(void)
{
}

void loop(void)
{
  Serial.println(add_fn(9, 1));  //where is the function add_fn?
  delay(1000);
}