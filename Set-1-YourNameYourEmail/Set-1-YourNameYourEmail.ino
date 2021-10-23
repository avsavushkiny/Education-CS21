/*
Week 0

Set 1 - Your name, your e-mail

Вывести свою фамилию и свой адрес электронной почты
в монитор порта используя нижеприведенные конструкции

\t - символ горизонтальной табуляции
\n - символ новой строки
\r - возврат каретки в начало строки
Serial.print(F(“Hello World”)); - выводим текст из flash памяти

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
    Serial.print("Savushkin \t e-mail: avsavushkiny@courseselectrical.onmicrosoft.com ");
}
