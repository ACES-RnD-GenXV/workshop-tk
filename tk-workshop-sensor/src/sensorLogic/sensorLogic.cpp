#include "sensorLogic.hpp"

void sendRequestTo(BLECharacteristic *pCharacteristic, int inputSensor)
{
    pCharacteristic->setValue(inputSensor);
    pCharacteristic->notify();
}