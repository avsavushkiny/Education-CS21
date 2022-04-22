#include "SPI.h"
#include "SD.h"

File myFile;

const int chipSelect = 4;

void setup()
{
    Serial.begin(9600);
    pinMode(SS, OUTPUT);

    // если карта не исправна - выводим сообщение
    while (!SD.begin(SPI_HALF_SPEED, chipSelect))
    {
        Serial.println("initialization failed");
    }

    // открываем файл, в котором будем сохранять информацию
    myFile = SD.open("test.txt", FILE_WRITE);
    // если файл открылся, сохраняем в нем строчку "testing 1, 2, 3"
    if (myFile)
    {
        Serial.println("Writing to test.txt");
        myFile.println("testing 1, 2, 3");
        myFile.close();
    }
    // иначе выводим ошибку об открытии файла
    else
    {
        Serial.println("error opening test.txt");
    }

    // снова открываем файл с sd карты для чтения
    myFile = SD.open("test.txt");
    // если файл открылся, выводим информацию с него на монитор порта
    if (myFile)
    {
        Serial.println("\ntest.txt:");
        while (myFile.available())
        {
            Serial.write(myFile.read());
        }
        myFile.close();
    }
    // иначе выводим ошибку об открытии файла
    else
    {
        Serial.println("error opening test.txt");
    }
}

void loop()
{
}