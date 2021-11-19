/*
Week 000

Set - Array

doc A. Savushkin
20.11.21
*/


// Выделяем 30 целочисленных переменных (каждая с разным именем)
int testResultStudent1;
int testResultStudent2;
int testResultStudent3;
// ...
int testResultStudent30;

int testResult[30];

void setup(void)
{
    Serial.begin(9600);
}

void loop(void)
{
    arrayFn();
    arrayFloat();
}

int arrayFn()
{
    int array[5];       // массив из пяти чисел
        array[0] = 3;   // индекс первого элемента - 0 (нулевой элемент)
        array[1] = 2;
        array[2] = 4;
        array[3] = 8;
        array[4] = 12;  // индекс последнего элемента - 4 
 
    Serial.println((String) "The array element with the smallest index has the value " + array[0]);
    Serial.println((String) "The sum of the first 5 numbers is " + (array[0] + array[1] + array[2] + array[3] + array[4]));
    
    delay(500); 
    return 0;
}

int arrayFloat()
{
    double array[3]; // выделяем 3 переменные типа double
           array[0] = 3.5;
           array[1] = 2.4;
           array[2] = 3.4;
 
    Serial.println((String) "The average is " + ((array[0] + array[1] + array[2]) / 3));
 
    return 0;
}