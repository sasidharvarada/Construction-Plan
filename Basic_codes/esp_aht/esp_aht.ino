#include <Adafruit_AHT10.h>  // AHT10 sensor library

Adafruit_AHT10 aht;          // AHT10 sensor object
Adafruit_Sensor* aht_humidity;
Adafruit_Sensor* aht_temp;

void setup() {
  Serial.begin(9600);    // Initialize serial communication
  aht_setup();           // Initialize AHT10 sensor
  delay(3000);           // Delay for system stability
}

void loop() {
  aht_loop();            // Read temperature and humidity
}

void aht_setup() {
  if (!aht.begin()) {
    Serial.println("Failed to find AHT10 chip");
    while (1) { delay(10); }
  }
  Serial.println("AHT10 Sensor Initialized!");
  aht_temp = aht.getTemperatureSensor();
  aht_humidity = aht.getHumiditySensor();
}

void aht_loop() {
  sensors_event_t humidity;
  sensors_event_t temp;
  
  aht_humidity->getEvent(&humidity);
  aht_temp->getEvent(&temp);

  float t = temp.temperature;
  float h = humidity.relative_humidity;

  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.println(" °C");
  
  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.println("% rH");
}
