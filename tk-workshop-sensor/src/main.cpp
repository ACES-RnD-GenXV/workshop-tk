#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>

// BLE Service UUID
#define SERVICE_UUID "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
// Characteristic UUID for sensor data
#define CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"

BLEServer *pServer;
BLEService *pService;
BLECharacteristic *pCharacteristic;

const int trigPin1 = 23;           // Trigger pin for sensor 1
const int echoPin1 = 22;           // Echo pin for sensor 1
const int trigPin2 = 19;           // Trigger pin for sensor 2
const int echoPin2 = 18;           // Echo pin for sensor 2
const int detectionThreshold = 15; // Distance threshold for HIGH state (in cm)

// Function to read ultrasonic sensor and return true if object detected
bool readSensor(int trigPin, int echoPin)
{
  // Clear the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // Set the trigPin HIGH for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read the echoPin, returns the sound wave travel time in microseconds
  long duration = pulseIn(echoPin, HIGH);

  // Calculate the distance (in cm)
  float distance = (duration * 0.034) / 2;

  // Return true if object is within detection threshold
  return (distance <= detectionThreshold && distance > 0);
}

void setup()
{
  // Initialize serial for debugging
  Serial.begin(9600);

  // Initialize sensor pins
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);

  // Initialize BLE
  BLEDevice::init("ESP32_WS_Input"); // Name of the device
  pServer = BLEDevice::createServer();
  pService = pServer->createService(SERVICE_UUID);

  pCharacteristic = pService->createCharacteristic(
      CHARACTERISTIC_UUID,
      BLECharacteristic::PROPERTY_READ |
          BLECharacteristic::PROPERTY_NOTIFY);

  pCharacteristic->addDescriptor(new BLE2902());
  pService->start();

  // Start advertising
  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(SERVICE_UUID);
  pAdvertising->setScanResponse(true);
  pAdvertising->setMinPreferred(0x06);
  pAdvertising->setMinPreferred(0x12);
  BLEDevice::startAdvertising();

  Serial.println("BLE Server started and advertising");
}

void loop()
{
  // Read both sensors
  bool sensor1State = readSensor(trigPin1, echoPin1);
  bool sensor2State = readSensor(trigPin2, echoPin2);

  // For debugging - print sensor states to serial
  Serial.print("Sensor 1: ");
  Serial.print(sensor1State ? "DETECTED" : "CLEAR");
  Serial.print(" | Sensor 2: ");
  Serial.println(sensor2State ? "DETECTED" : "CLEAR");

  // Create a data structure to send both sensor states
  uint8_t sensorData[2] = {sensor1State, sensor2State};

  // Update BLE characteristic
  pCharacteristic->setValue(sensorData, 2);
  pCharacteristic->notify();

  delay(100); // Adjust polling rate as needed
}