#ifndef SENSORLOGIC_HPP
#define SENSORLOGIC_HPP

#include <Arduino.h>
#include <BLECharacteristic.h>

void sendRequestTo(BLECharacteristic *pCharacteristic, int inputSensor);

#endif