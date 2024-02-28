// Libraries and global variables
#include <DHT.h>
#include "heltec.h"
#include <WiFi.h>
#include <HTTPClient.h>


#define DHT_SENSOR_PIN 27 // ESP32 pin GIOP21 connected to DHT22 sensor
#define DHT_SENSOR_TYPE DHT22

DHT dht_sensor(DHT_SENSOR_PIN, DHT_SENSOR_TYPE);
float currentTempC = 0.0;
float currentTempF = 0.0;
float currentHumidity = 0.0;

const char* ssid = "Aa kurchini Madathapetti";
const char* password = "umkc@605!";
const char* serverAddress = "http://192.168.1.161:5000/post-data";

void connectToWiFi() {
  Serial.println("Connecting to WiFi...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
}

void sendDataToServer(float tempC, float tempF, float humidity) {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(serverAddress);
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");

    String postData = "team_number=1"; // Change team_number as needed
    postData += "&temperature=" + String(tempC);
    postData += "&humidity=" + String(humidity);
    postData += "&timestamp=" + String(millis());

    int httpResponseCode = http.POST(postData);
    if (httpResponseCode > 0) {
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
    } else {
      Serial.print("Error code: ");
      Serial.println(httpResponseCode);
    }
    http.end();
  } else {
    Serial.println("WiFi not connected. Cannot send data to server.");
  }
}


// LCD display function
void displayReadingsOnOled() 
{
    String FtemperatureDisplay ="Temperature: " + (String)currentTempF + "°F";
    String CtemperatureDisplay ="Temperature: " + (String)currentTempC + "°C";
    String humidityDisplay = "Humidity: " + (String)currentHumidity + "%";
    // Clear the OLED screen
    Heltec.display->clear();
    // Prepare to display temperatureF
    Heltec.display->drawString(0, 0, FtemperatureDisplay);
    // Prepare to display temperatureC
    Heltec.display->drawString(0, 12, CtemperatureDisplay);
    // Prepare to display humidity
    Heltec.display->drawString(0, 24, humidityDisplay);
    // Display the readings
    Heltec.display->display();
}

// put your setup code here, to run once:
void setup()
{
    // Serial Monitor to start
    Serial.begin(115200);
    // initialize the DHT sensor
    dht_sensor.begin(); 
    // LED light on 
    pinMode(LED,OUTPUT);
    digitalWrite(LED,HIGH);
    // Start Heltec specific LCD display
    Heltec.begin(true /*DisplayEnable Enable*/, false /*LoRa Enable*/, false /*Serial Enable*/);
    connectToWiFi();
    currentTempC = dht_sensor.readTemperature();
    currentTempF = dht_sensor.readTemperature(true);
    currentHumidity = dht_sensor.readHumidity();
    displayReadingsOnOled();
}

// put your main code here, to run repeatedly:
void loop(){
    // read humidity
    float humi = dht_sensor.readHumidity();
    // read temperature in Celsius
    float tempC = dht_sensor.readTemperature();
    // read temperature in Fahrenheit
    float tempF = dht_sensor.readTemperature(true);
    // check whether the reading is successful or not
    // display on the Serial Monitor (Check the specific COM port and baud number)

    if ( isnan(tempC) || isnan(tempF) || isnan(humi)) {
    Serial.println("Failed to read from DHT sensor!");
    } else {
    Serial.print("Humidity: ");
    Serial.print(humi);
    Serial.print("%");
    Serial.print(" | ");
    Serial.print("Temperature: ");
    Serial.print(tempC);
    Serial.print("°C ~ ");
    Serial.print(tempF);
    Serial.println("°F");
    // Now Update Heltec Specific LCD monitor
    currentTempC = tempC;
    currentTempF = tempF;
    currentHumidity = humi;
    sendDataToServer( tempC, tempF, humi);
    displayReadingsOnOled();
    }
 
    // wait a 4 seconds between readings
    delay(4000);
}