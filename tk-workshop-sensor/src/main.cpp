#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>

// BLE Service UUID
#define SERVICE_UUID "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
// Characteristic UUID for sensor data
#define CHAR_UUID_SENSOR_A "68a44f5d-5d78-4d08-86a8-4f8abf8e4c4b"
#define CHAR_UUID_SENSOR_B "094f0fce-dfff-4c6f-875c-c86e4aaff2cb"

BLEServer *pServer;
BLEService *pService;
BLECharacteristic *pCharacteristicA;
BLECharacteristic *pCharacteristicB;

const int trigPin1 = 23;           // Trigger pin for sensor 1
const int echoPin1 = 22;           // Echo pin for sensor 1
const int trigPin2 = 19;           // Trigger pin for sensor 2
const int echoPin2 = 18;           // Echo pin for sensor 2
const int detectionThreshold = 15; // Distance threshold for HIGH state (in cm)

// Function to read ultrasonic sensor and return true if object detected
int readSensor(int trigPin, int echoPin)
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

  // Return distance value (in cm)
  return (distance);
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

  pCharacteristicA = pService->createCharacteristic(
      CHAR_UUID_SENSOR_A,
      BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_NOTIFY);
  pCharacteristicB = pService->createCharacteristic(
      CHAR_UUID_SENSOR_B,
      BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_NOTIFY);

  pCharacteristicA->addDescriptor(new BLE2902());
  pCharacteristicB->addDescriptor(new BLE2902());

  // Start advertising
  pService->start();
  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(SERVICE_UUID);
  pAdvertising->setScanResponse(true);
  pAdvertising->setMinPreferred(0x06);
  pAdvertising->setMinPreferred(0x12);
  BLEDevice::startAdvertising();

  Serial.println("BLE Server started and advertising");
}

// void loop()
// {
//   // Read both sensors
//   bool sensor1State = readSensor(trigPin1, echoPin1);
//   bool sensor2State = readSensor(trigPin2, echoPin2);

//   // For debugging - print sensor states to serial
//   Serial.print("Sensor 1: ");
//   Serial.print(sensor1State ? "DETECTED" : "CLEAR");
//   Serial.print(" | Sensor 2: ");
//   Serial.println(sensor2State ? "DETECTED" : "CLEAR");

//   // Create a data structure to send both sensor states
//   uint8_t sensorData[2] = {sensor1State, sensor2State};

//   // Update BLE characteristic
//   pCharacteristic->setValue(sensorData, 2);
//   pCharacteristic->notify();

//   delay(100); // Adjust polling rate as needed
// }

void loop()
{
  // Simulate ultrasonic sensor readings
  int sensorValueA = readSensor(trigPin1, echoPin1);
  int sensorValueB = readSensor(trigPin2, echoPin2);

  // For debugging - print sensor states to serial
  Serial.print("Sensor 1: ");
  Serial.print(sensorValueA);
  Serial.print(" | Sensor 2: ");
  Serial.println(sensorValueB);

  // Send sensor values as strings (or binary if preferred)
  pCharacteristicA->setValue(String(sensorValueA).c_str());
  pCharacteristicA->notify();

  pCharacteristicB->setValue(String(sensorValueB).c_str());
  pCharacteristicB->notify();

  delay(1000); // 1 second update interval
}