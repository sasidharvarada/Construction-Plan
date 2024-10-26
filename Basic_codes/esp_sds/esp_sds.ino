#include <SDS011.h>

float pm2_5 ,pm10;
int err;

// Initialize the SDS011 object
SDS011 my_sds;

// Define the serial port for ESP32
#ifdef ESP32
HardwareSerial port(2);  // Use Serial2 on the ESP32
#endif

void setup() {
    Serial.begin(115200);       // Start the main serial monitor
    port.begin(9600, SERIAL_8N1, 16, 17);  // SDS011 uses 9600 baud; RX=16, TX=17
    my_sds.begin(&port);        // Initialize SDS011 with the specified port
    delay(2000);                // Allow some time for the sensor to initialize

    Serial.println("SDS011 Sensor Initialized.");
}

void loop() {
    // Read PM2.5 and PM10 values from SDS011
    err = my_sds.read(&p25, &p10);
    if (!err) {
        Serial.println("PM2.5: " + String(pm2_5) + " µg/m³");
        Serial.println("PM10:  " + String(pm10) + " µg/m³");
    } else {
        Serial.println("Failed to read from SDS011 sensor!");
    }
    delay(1000);  // Wait 1 second between readings
}
