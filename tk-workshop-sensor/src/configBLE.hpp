#define NAME_OF_ESP_BLE "ESP_WS_Input"
#define SERVICE_UUID "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define CHAR_UUID_SENSOR_A "68a44f5d-5d78-4d08-86a8-4f8abf8e4c4b"
#define CHAR_UUID_SENSOR_B "094f0fce-dfff-4c6f-875c-c86e4aaff2cb"

BLEServer *bleServer;
BLEService *bleService;
BLECharacteristic *bleCharacteristicA;
BLECharacteristic *bleCharacteristicB;
BLEAdvertising *bleAdvertising;