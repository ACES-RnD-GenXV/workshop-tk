#ifndef ABSTRACTBLE_HPP
#define ABSTRACTBLE_HPP

#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <BLE2902.h>

extern BLEServer *defServer;
extern BLEService *defService;
extern BLECharacteristic *defCharacteristic;
extern BLEAdvertising *defAdvertising;

void initializeServerBLE(const char *deviceName, BLEServer *pServer = defServer);
void initializeService(const char *serviceUUID, BLEService *pService = defService, BLEServer *pServer = defServer);
void initializeCharacteristic(const char *characteristicUUID, BLECharacteristic *pCharacteristic = defCharacteristic, BLEService *pService = defService);
void advertiseBLE(const char *serviceUUID, BLEAdvertising *pAdvertising = defAdvertising);

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