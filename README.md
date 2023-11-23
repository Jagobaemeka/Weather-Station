# Weather-Station

Real-Time Temperature and Humidity Monitoring System

Overview
This project is a comprehensive IoT solution designed to monitor temperature and humidity in real-time. It leverages the capabilities of the DHT11 sensor, 
an ESP32 microcontroller, and a web server to provide a versatile system suitable for various applications.

Features
DHT11 Sensor Integration: Measures temperature and humidity levels.
ESP32 Microcontroller: Provides WiFi connectivity and processes sensor data.
Web Server: Hosts a responsive web interface that displays real-time temperature and humidity readings.
ThingSpeak Integration: Cloud-based platform used to store and visualize data.
LCD Display: Shows alternating temperature and humidity readings.


Setup
Hardware Requirements
ESP32 Microcontroller
DHT11 Temperature and Humidity Sensor
LCD Display
Software Dependencies
WiFi.h: For WiFi connectivity.
DHT.h: To handle the DHT sensor.
LiquidCrystal.h: To manage the LCD display.
ThingSpeak.h: To integrate with the ThingSpeak platform.
WebServer.h: To set up the web server.

WiFi Configuration
Replace the placeholders in the following lines with your WiFi credentials:
const char* ssid = "Your_SSID";
const char* password = "Your_PASSWORD";

ThingSpeak Configuration
Replace the placeholders with your ThingSpeak channel number and API key:
unsigned long myChannelNumber = YOUR_CHANNEL_NUMBER;
const char * myWriteAPIKey = "YOUR_WRITE_API_KEY";

Usage
Power on the ESP32 microcontroller.
The system will automatically connect to the specified WiFi network.
Open a web browser and navigate to the IP address displayed in the serial monitor.
The web interface will display real-time temperature and humidity readings.
The LCD will alternate between showing the temperature and humidity every 3.5 seconds.
Data is sent to ThingSpeak for storage and visualization.

Web Interface
The web interface provides a user-friendly way to view the temperature and humidity readings. It includes:

Home: An introduction to the project and its objectives.
About: Detailed information about the project, its components, and its applications.
Humidity: Displays the current humidity reading.
Temperature: Displays the current temperature reading.
Charts: Visualizes the temperature and humidity data using ThingSpeak charts.
Troubleshooting
Ensure that the DHT11 sensor is correctly connected to the ESP32.
Check the WiFi credentials and ensure the ESP32 is within range of the WiFi network.
If the LCD does not display readings, ensure it's correctly wired and initialized in the code.
Future Enhancements
Improve sensor accuracy.
Integrate with popular smart home systems.
