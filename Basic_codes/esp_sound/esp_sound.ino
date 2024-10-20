//esp8266
// #define SoundSensorPin A0  // ESP8266 uses A0 for analog input
// #define VREF  3.3  // Voltage reference for ESP8266 (operating voltage)

#define SoundSensorPin 36  // GPIO pin for sound sensor
#define VREF 5.0           // Reference voltage for sound sensor
float voltageValue, dbValue;

void setup() {
  Serial.begin(9600);  // Initialize serial communication
  pinMode(SoundSensorPin, INPUT);  // Set sound sensor pin as input
  delay(3000);                     // Delay for system stability
}

void loop() {
  sound_loop();  // Read sound levels
}

void sound_loop() {
  voltageValue = analogRead(SoundSensorPin) / 4096.0 * VREF;
  dbValue = voltageValue * 50.0;
  Serial.print("Sound Level: ");
  Serial.print(dbValue, 1);
  Serial.println(" dBA");
}
