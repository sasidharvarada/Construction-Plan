#include <SoftwareSerial.h>
#include <Adafruit_AHT10.h>

// Define RX and TX pins for the GPRS module
#define GPRS_RX 2 // Adjust according to your connections
#define GPRS_TX 4 // Adjust according to your connections

// Use SoftwareSerial for GPRS communication
SoftwareSerial gprsSerial(GPRS_RX, GPRS_TX);

// Initialize AHT10 sensor
Adafruit_AHT10 aht;

void setup() {
  gprsSerial.begin(9600); // Initialize GPRS serial communication
  Serial.begin(9600); // Initialize Serial Monitor
  
  // Initialize AHT10 sensor
  if (!aht.begin()) {
    Serial.println("Could not find AHT10? Check wiring");
    while (1) delay(10);
  }
  Serial.println("AHT10 sensor initialized");

  delay(1000); // Allow time for module initialization
}

void loop() {
  // Read and display temperature and humidity from AHT10
  sensors_event_t humidity, temp;
  aht.getEvent(&humidity, &temp);

  float h = humidity.relative_humidity;
  float t = temp.temperature;

  Serial.print("Temperature = ");
  Serial.print(t);
  Serial.println(" °C");
  Serial.print("Humidity = ");
  Serial.print(h);
  Serial.println(" %");

  // AT commands to set up GPRS
  sendATCommand("AT"); // Check if the module is responding
  sendATCommand("AT+CPIN?"); // Check if SIM is ready
  sendATCommand("AT+CREG?"); // Check network registration
  sendATCommand("AT+CGATT?"); // Check GPRS attachment
  
  sendATCommand("AT+CIPSHUT"); // Close any existing connection
  sendATCommand("AT+CIPSTATUS"); // Check connection status
  sendATCommand("AT+CIPMUX=0"); // Set single connection mode

  sendATCommand("AT+CSTT=\"bsnlnet\""); // Set APN for BSNL
  sendATCommand("AT+CIICR"); // Bring up wireless connection
  sendATCommand("AT+CIFSR"); // Get local IP address

  sendATCommand("AT+CIPSPRT=0"); // Disable print of extra information

  // Start TCP connection to ThingSpeak
  sendATCommand("AT+CIPSTART=\"TCP\",\"api.thingspeak.com\",\"80\"");

  // Prepare and send the HTTP GET request
  String str = "GET /update?api_key=TF4XOOJ7EZSHSGU4&field1=" + String(t, 2) + "&field2=" + String(h, 2) + " HTTP/1.1\r\nHost: api.thingspeak.com\r\nConnection: close\r\n\r\n";
  Serial.println(str);
  
  gprsSerial.println("AT+CIPSEND=" + String(str.length())); // Prepare to send data
  delay(4000);

  ShowSerialData();

  gprsSerial.println(str); // Send the HTTP GET request
  delay(4000);
  ShowSerialData();

  gprsSerial.println((char)26); // End of the request
  delay(5000); // Wait for response

  ShowSerialData(); // Read the final response

  sendATCommand("AT+CIPSHUT"); // Close the connection
  delay(10000); // Wait before the next iteration
}

void ShowSerialData() {
  while (gprsSerial.available()) {
    Serial.write(gprsSerial.read());
  }
  delay(1000); // Shorter delay to read response more quickly
}

void sendATCommand(const char* command) {
  Serial.print("Sending command: ");
  Serial.println(command);
  gprsSerial.println(command);
  delay(2000); // Increased delay for reliability
  ShowSerialData();
}
