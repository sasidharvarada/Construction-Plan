#include <SD.h>         // SD card library
#include <SPI.h>        // SPI communication for SD card

const int chipSelect = 5;   // Chip select pin for SD card

void setup() {
  Serial.begin(9600);     // Initialize serial communication
  SD_setup();             // Initialize SD card
  delay(3000);            // Delay for system stability
}

void loop() {
  logDataToSD();  // Read data from SD card
}

void SD_setup() {
  if (!SD.begin(chipSelect)) {
    Serial.println("SD card initialization failed!");
    while (1);
  }
  Serial.println("SD card initialized.");
}

void logDataToSD() {
  File dataFile = SD.open("data.txt");
  
  if (dataFile) {
    while (dataFile.available()) {
      Serial.write(dataFile.read());
    }
    dataFile.close();
  } else {
    Serial.println("Error opening file.");
  }
}
