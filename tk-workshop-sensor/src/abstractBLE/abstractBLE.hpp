#ifndef ABSTRACTBLE_HPP
#define ABSTRACTBLE_HPP

#define SERVICE_UUID "4869e6e5-dec6-4a9d-a0a4-eda6b5448b97"
#define CHARACTERISTIC_UUID "05c4d03a-ac78-4627-8778-f23fab166ba8"

#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>

void initializeServerBLE(const char *deviceName);
void initializeService(const char *serviceUUID);
void initializeCharacteristic(const char *characteristicUUID);
void advertiseBLE(const char *serviceUUID);

class MyCallbacks : public BLECharacteristicCallbacks
{
public:
    void onWrite(BLECharacteristic *pCharacteristic);
};

class MyServerCallbacks : public BLEServerCallbacks
{
private:
    void onConnect(BLEServer *pServer);
    void onDisconnect(BLEServer *pServer);
};

#endif