#include "abstractBLE\abstractBLE.hpp"
#include "sensorLogic\sensorLogic.hpp"
#include "configBLE.hpp"

const int trigPin1 = 23; // Trigger pin for sensor 1
const int echoPin1 = 22; // Echo pin for sensor 1
const int trigPin2 = 19; // Trigger pin for sensor 2
const int echoPin2 = 18; // Echo pin for sensor 2
// const int detectionThreshold = 15; // Distance threshold for HIGH state (in cm)

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
  initializeServerBLE(NAME_OF_ESP_BLE, bleServer);
  initializeService(SERVICE_UUID, bleService, bleServer);
  initializeCharacteristic(CHAR_UUID_SENSOR_A, bleCharacteristicA, bleService);
  initializeCharacteristic(CHAR_UUID_SENSOR_B, bleCharacteristicB, bleService);
  advertiseBLE(SERVICE_UUID, bleAdvertising);

  // BLEDevice::init("ESP32_WS_Input"); // Name of the device
  // pServer = BLEDevice::createServer();
  // pServer->setCallbacks(new MyServerCallbacks());
  // pService = pServer->createService(SERVICE_UUID);

  // pCharacteristicA = pService->createCharacteristic(
  //     CHAR_UUID_SENSOR_A,
  //     BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_NOTIFY);
  // pCharacteristicB = pService->createCharacteristic(
  //     CHAR_UUID_SENSOR_B,
  //     BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_NOTIFY);

  // pCharacteristicA->addDescriptor(new BLE2902());
  // pCharacteristicB->addDescriptor(new BLE2902());

  // // Start advertising
  // pService->start();
  // BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  // pAdvertising->addServiceUUID(SERVICE_UUID);
  // pAdvertising->setScanResponse(true);
  // pAdvertising->setMinPreferred(0x06);
  // pAdvertising->setMinPreferred(0x12);
  // BLEDevice::startAdvertising();

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
  sendRequestTo(bleCharacteristicA, sensorValueA);
  sendRequestTo(bleCharacteristicB, sensorValueB);
  // pCharacteristicA->setValue(sensorValueA);
  // pCharacteristicA->notify();

  // pCharacteristicB->setValue(sensorValueB);
  // pCharacteristicB->notify();

  delay(1000); // 1 second update interval
}