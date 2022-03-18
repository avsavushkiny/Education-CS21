#include "Wire.h"
#include <MPU6050_light.h>

MPU6050 mpu(Wire);

void setup()
{
    Wire.begin();
    mpu.begin();
    mpu.calcOffsets();
}

void loop()
{
    mpu.update();

    float angle[3] =
    {
        mpu.getAngleX(),
        mpu.getAngleY(),
        mpu.getAngleZ()
    };


    Serial.println((String) angle[0] + " " + angle[1] + " " + angle[2]);
}