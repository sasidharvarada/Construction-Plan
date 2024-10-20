#include <Wire.h>
#include <RTClib.h>  // RTC library

RTC_DS3231 rtc;  // RTC object

void setup() {
  Serial.begin(9600);  // Initialize serial communication
  Wire.begin();        // Initialize I2C communication
  rtc_setup();         // Initialize RTC
  delay(3000);         // Delay for system stability
}

void loop() {
  DateTime now = rtc.now();  // Get current date and time
  
  Serial.print(now.year(), DEC);
  Serial.print('/');
  Serial.print(now.month(), DEC);
  Serial.print('/');
  Serial.print(now.day(), DEC);
  Serial.print(" ");
  Serial.print(now.hour(), DEC);
  Serial.print(':');
  Serial.print(now.minute(), DEC);
  Serial.print(':');
  Serial.print(now.second(), DEC);
  Serial.println();
  
  delay(1000);  // Delay for 1 second before next update
}

void rtc_setup() {
  if (!rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }

  if (rtc.lostPower()) {
    Serial.println("RTC lost power, setting time to compile time!");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
  Serial.println("RTC initialized.");
}
