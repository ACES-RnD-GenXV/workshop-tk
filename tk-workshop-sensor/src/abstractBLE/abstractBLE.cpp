#include "abstractBLE.hpp"

BLEServer *pServer;
BLEService *pService;
BLECharacteristic *pCharacteristic;
BLEAdvertising *pAdvertising;

void MyCallbacks::onWrite(BLECharacteristic *pCharacteristic)
{
    std::string value = pCharacteristic->getValue();
}

void MyServerCallbacks::onConnect(BLEServer *pServer)
{
    Serial.println("Client connected");
}

void MyServerCallbacks::onDisconnect(BLEServer *pServer)
{
    Serial.println("Client disconnected");
    BLEDevice::startAdvertising();
}

void initializeServerBLE(const char *deviceName)
{
    // Serial.println("hi");
    BLEDevice::init(deviceName);
    pServer = BLEDevice::createServer();
    pServer->setCallbacks(new MyServerCallbacks());
    // Serial.println("hi");
}

void initializeService(const char *serviceUUID)
{
    // Serial.println("service");
    pService = pServer->createService(serviceUUID);
    // Serial.println("service");
};

void initializeCharacteristic(const char *characteristicUUID)
{
    // Serial.println("char");
    pCharacteristic =
        pService->createCharacteristic(characteristicUUID, BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_WRITE | BLECharacteristic::PROPERTY_NOTIFY);
    pCharacteristic->setCallbacks(new MyCallbacks());
    pService->start();
    // Serial.println("char");
};

void advertiseBLE(const char *serviceUUID)
{
    // Serial.println("advertise");
    pAdvertising = BLEDevice::getAdvertising();
    pAdvertising->addServiceUUID(serviceUUID);
    pAdvertising->setScanResponse(true);
    pAdvertising->setMinPreferred(0x06); // functions that help with iPhone connections issue
    pAdvertising->setMinPreferred(0x12);
    BLEDevice::startAdvertising();
    // Serial.println("advertise");
};