// Include the required libraries for WiFi connectivity, handling DHT sensor, and LCD
#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include "DHT.h"
#include <LiquidCrystal.h>
#include <ThingSpeak.h>  // Include the ThingSpeak library


// Define the DHT sensor pin and type
#define DHTPIN 4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// LCD pin configuration
const int rs = 19, en = 23, d4 = 18, d5 = 17, d6 = 16, d7 = 15;
//en = eneables writing
// rs = registers data
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// Enter your WiFi hotspot credentials
const char* ssid = "Emeka Adimora";
const char* password = "Ametsa00";

// Initialize the web server on port 80
WebServer server(80);

WiFiClient  client;
// ThinkSpeak Settings
unsigned long myChannelNumber = 2141764;
const char * myWriteAPIKey = "A3QW2H4OA9ILK2R9";

//timer variables 
unsigned long lastTime = 0;
unsigned long timerDelay = 30000;

//html code
const char* htmlCode = R"=====(
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/font-awesome/4.7.0/css/font-awesome.min.css">
    <style>

    a {
    text-decoration: none;
}
        * {
            margin: 0;
            padding: 0;
            box-sizing: border-box;
        }
        nav {
            background-color: #f8f9fa;
            padding: 10px;
            text-align: center;
        }
        nav ul {
            list-style-type: none;
        }
        nav ul li {
            display: inline;
        }
        nav ul li a {
            display: inline-block;
            padding: 8px 16px;
            text-decoration: none;
            color: #333;
            border-radius: 25px;
            transition: background-color 0.3s;
        }
        nav ul li a:hover {
            background-color: #007bff;
            color: #fff;
        }
        .fa {
            margin-right: 5px;
        }
        .content {
            margin: 20px;
            display: flex;
            flex-direction: column;
            justify-content: center;
            align-items: center;
            height: calc(100vh - 80px);
            text-align: center;
            display: none;
        }
        .content.active {
            display: flex;
        }
        .circle {
            width: 200px;
            height: 200px;
            border-radius: 50%;
            font-size: 30px;
            color: #fff;
            line-height: 200px;
            text-align: center;
            background: #000;
            margin: 0 auto;
            box-shadow: 0px 3px 15px rgba(0,0,0,0.2);
            transition: all 0.3s ease-in-out;
        }
        h2 {
            position: absolute;
            top: 10%;
            left: 50%;
            transform: translate(-50%, -50%);
        }
        body.dark-mode {
            background-color: #333;
            color: #f8f9fa;
        }
        body.dark-mode nav {
            background-color: #333;
            color: #f8f9fa;
        }
        body.dark-mode nav ul li a {
            color: #f8f9fa;
        }
        body.dark-mode nav ul li a:hover {
            background-color: #f8f9fa;
            color: #333;
        }
    </style>
    <title>IoT Solution</title>
</head>
<body>
    <nav>
    <ul>
        <li><a href="#home" class="home"><i class="fa fa-home"></i> Home</a></li>
        <li><a href="#about" class="about"><i class="fa fa-info-circle"></i> About</a></li>
        <li><a href="#humidity" class="humidity"><i class="fa fa-tint"></i> Humidity</a></li>
        <li><a href="#temperature" class="temperature"><i class="fa fa-thermometer-half"></i> Temperature</a></li>
        <li><a href="#charts" class="charts"><i class="fa fa-bar-chart"></i> Charts</a></li> <!-- New tab -->
        <li><a href="#" class="toggle-darkmode"><i class="fa fa-moon-o"></i> 
    </ul>
</nav>
<div id="home" class="content active">
        <h1>Welcome to Real-Time Temperature and Humidity Monitoring</h1>
        <p>This Internet of Things (IoT) project aims to monitor temperature and humidity in real-time. I have designed a versatile system that supports the United Nations Sustainable Development Goal (UN SDG) 13: Climate Action. It can be customized for use in residential, commercial, agricultural, and industrial settings.</p>
    </div>
    <div id="about" class="content">
    <section>
        
        
        <p>This project is a comprehensive IoT solution for real-time temperature and humidity monitoring. It leverages a DHT11 sensor, an ESP32 microcontroller, and a web server, offering an adaptable solution suitable for various applications.</p>

        
        <ul>
            <li><b>DHT11 Sensor:</b> A popular choice for measuring temperature and humidity levels due to its affordability, ease of use, and sufficient accuracy for most applications.</li>
            <li><b>ESP32 Microcontroller:</b> A powerful and versatile component with a wide range of capabilities, including integrated WiFi and Bluetooth connectivity, and various input/output options.</li>
            <li><b>Web Server:</b> Stores and presents the data collected by the DHT11 sensor. To ensure reliability and flexibility, a cloud-based hosting solution was chosen.</li>
        </ul>

        
        <p>The development process involved programming the microcontroller with C/C++, assembling the hardware components, integrating WiFi connectivity, and designing a responsive web interface. The system was tested and refined iteratively to ensure peak performance.</p>

        <p>Our IoT solution can be used in residential settings, commercial spaces, agriculture, and industrial environments. It helps in optimizing energy consumption, maintaining a comfortable living environment, and ensuring safety by monitoring and controlling temperature and humidity levels.</p>
        
        <p>Future enhancements for this IoT solution include improved sensor accuracy, integration with popular smart home systems, and the incorporation of machine learning algorithms for predictive analytics.</p>
    </section>
</div>
    </div>
    <div id="humidity" class="content">
        
        <div class="circle" id="humidity-placeholder"></div>
    </div>
    <div id="temperature" class="content">
       
        <div class="circle" id="temperature-placeholder"></div>
    </div>
    <div id="charts" class="content">
        
        <iframe width="450" height="260" style="border: 1px solid #cccccc;" src="https://thingspeak.com/channels/2141764/charts/1?bgcolor=%23ffffff&color=%23d62020&dynamic=true&results=60&title=Temperature&type=line&xaxis=Date&yaxis=Temperature"></iframe>
        <iframe width="450" height="260" style="border: 1px solid #cccccc;" src="https://thingspeak.com/channels/2141764/charts/2?bgcolor=%23ffffff&color=%23d62029&dynamic=true&results=60&title=Humididty&type=line&xaxis=Time&yaxis=Humidity"></iframe>
    </div>

    <script>
        document.querySelectorAll("nav ul li a").forEach(link => {
            link.addEventListener("click", event => {
                event.preventDefault();
                let target = event.target.closest('a').getAttribute("href");
                if (target === "#") {
                    document.body.classList.toggle("dark-mode");
                    return;
                }
                document.querySelectorAll('.content.active').forEach(content =>

                content.classList.remove("active"));
                document.querySelector(target).classList.add("active");
            });
        });

        setInterval(() => {
            fetch(location.href)
                .then(response => response.text())
                .then(html => {
                    let parser = new DOMParser();
                    let htmlDoc = parser.parseFromString(html, 'text/html');

                    let temp = htmlDoc.getElementById('temperature-placeholder').textContent;
                    let humidity = htmlDoc.getElementById('humidity-placeholder').textContent;

                    let tempElement = document.getElementById('temperature-placeholder');
                    let humidityElement = document.getElementById('humidity-placeholder');

                    tempElement.textContent = temp;
                    humidityElement.textContent = humidity;

                    // Modifying circle size according to the reading
                    tempElement.style.width = tempElement.style.height = temp + 'px';
                    humidityElement.style.width = humidityElement.style.height = humidity + 'px';
                    
                    // Adjust the glow according to the reading
                    tempElement.style.boxShadow = '0px 0px ' + temp / 3 + 'px rgba(0,0,255,0.5)';
                    humidityElement.style.boxShadow = '0px 0px ' + humidity / 3 + 'px rgba(0,0,255,0.5)';
                });
        }, 3500);  // Update every 3.5 seconds
    </script>
</body>
</html>
)=====";

void handleRoot() {
  float t = dht.readTemperature();
  float h = dht.readHumidity();
  String tempHtml = String(htmlCode);
  
  tempHtml.replace("<div class=\"circle\" id=\"temperature-placeholder\"></div>", "<div class=\"circle\" id=\"temperature-placeholder\">" + String(t) + " &#8451;</div>");
  tempHtml.replace("<div class=\"circle\" id=\"humidity-placeholder\"></div>", "<div class=\"circle\" id=\"humidity-placeholder\">" + String(h) + " %</div>");
  
  server.send(200, "text/html", tempHtml);
}

// Setup function to initialize serial communication, WiFi, and the web server
void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  // Initialize the DHT sensor
  dht.begin();

  // Assign the root request handler
  server.on("/", handleRoot);
  server.begin();
  Serial.println("HTTP server started");

  // Connect to ThingSpeak
  ThingSpeak.begin(client);
} // Add the closing curly bracket here

// Main loop to handle incoming clients and read temperature
void loop() {
  server.handleClient();

  // Read temperature and humidity
  float t = dht.readTemperature();
  float h = dht.readHumidity();

  if (isnan(t) || isnan(h)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Print temperature and humidity on the LCD screen
  static bool showTemp = true;

  lcd.clear();
  if (showTemp) {
    lcd.print("Temp:");
    lcd.print(t);
    lcd.print("C");
  } else {
    lcd.setCursor(0, 1);
    lcd.print("Humid:");
    lcd.print(h);
    lcd.print("%");
  }

  showTemp = !showTemp;  // Toggle between temperature and humidity

  // Send data to ThingSpeak
  if (millis() - lastTime > timerDelay) {
    ThingSpeak.begin(client);
    ThingSpeak.setField(1, t); // Send temperature to field 1
    ThingSpeak.setField(2, h); // Send humidity to field 2
    ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey); // Write to ThingSpeak
    lastTime = millis(); // Update last time
  }

  delay(3500);  // Delay for 3.5 seconds before switching the display
}
