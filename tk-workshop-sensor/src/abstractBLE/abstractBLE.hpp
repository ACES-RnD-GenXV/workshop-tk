#ifndef ABSTRACTBLE_HPP
#define ABSTRACTBLE_HPP

#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <BLE2902.h>

void initializeServerBLE(const char *deviceName, BLEServer *&pServer);
void initializeService(const char *serviceUUID, BLEService *&pService, BLEServer *&pServer);
void initializeCharacteristic(const char *characteristicUUID, BLECharacteristic *&pCharacteristic, BLEService *&pService);
void advertiseBLE(const char *serviceUUID, BLEAdvertising *&pAdvertising);

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