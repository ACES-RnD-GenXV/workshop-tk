# TK-Workshop Sensor Input Device

*Simple BLE enabled device for embedded systems and mobile pervasive computing workshops.*

####  📌 What's This?
This is a basic embedded systems device that reads data from two sensors, and broadcasts it through Bluetooth Low Energy (BLE) to a mobile device or computer. This device and its ecosystem is made as part of the Universitas Multimedia Nusantara (UMN)'s Association of Computer Engineering Students (ACES) program to introduce the fundamentals of embedded systems and mobile pervasive computing to high school students.

------------


#### 🛠 Hardware Setup
- **MCU**: ESP32

- **Sensor**: Two HC-SR04 Ultrasonic Sensor
- **Wiring**
	- `MCU` -> `MicroUSB / TypeC`
	
	- `Sensor VCC` -> `5V`
	
	- `Sensor GND` -> `GND`
	
	- `Sensor 1 TRIG` -> `GPIO 23`
	
	- `Sensor 1 ECHO` -> `GPIO 22`
	
	- `Sensor 2 TRIG` -> `GPIO 33`
	
	- `Sensor 2 ECHO` -> `GPIO 32`


------------



#### 💻 Software Setup
Flash the program using PlatformIO or similar software.


------------

#### 📲 How to Use
1. Power the device
2. Scan the device through the website `https://workshop-tk.netlify.app`
3. Pair with `ESP32_WS_Input`
4. Output distance will be displayed via website dashboard updated every second
