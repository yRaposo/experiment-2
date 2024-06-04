#include <DHT_U.h>
#include <DHT.h>

#define DHTPIN 2          // Pin where the DHT22 sensor is connected
#define DHTTYPE DHT22     // Type of the DHT sensor (DHT22 in this case)

DHT dht(DHTPIN, DHTTYPE); // Initialize the DHT sensor

void setup() {
    // Code to run once when the sketch starts
    Serial.begin(9600);    // Initialize serial communication
    dht.begin();           // Initialize the DHT sensor
}

void loop() {
    // Code to run repeatedly
    float temperature = dht.readTemperature();  // Read temperature from the DHT sensor
    float humidity = dht.readHumidity();        // Read humidity from the DHT sensor

    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.print(" °C, Humidity: ");
    Serial.print(humidity);
    Serial.println(" %");

    delay(2000);  // Delay for 2 seconds before reading again
}