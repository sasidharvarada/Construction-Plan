#include <SDS011.h>
#include <SoftwareSerial.h>

float pm2_5, pm10;
int err;

// Initialize SoftwareSerial for SDS011
SoftwareSerial sdsSerial(16, 17);  // RX = 16, TX = 17
SDS011 my_sds;

void setup() {
    Serial.begin(115200);       // Start the main serial monitor
    sdsSerial.begin(9600);      // SDS011 uses 9600 baud
    my_sds.begin(16, 17);       // Use RX and TX pin numbers directly

    Serial.println("SDS011 Sensor Initialized.");
}

void loop() {
    // Read PM2.5 and PM10 values from SDS011
    err = my_sds.read(&pm2_5, &pm10);
    if (!err) {
        Serial.print("PM2.5: " + String(pm2_5) + " µg/m³");
        Serial.println("PM10:  " + String(pm10) + " µg/m³");
    } else {
        Serial.println("Failed to read from SDS011 sensor!");
    }
    delay(2000);  // Wait 10 seconds between readings
}
