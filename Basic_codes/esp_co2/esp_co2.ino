// CO2 Sensor Configuration
const int CO2_PIN = 13;                   // GPIO pin for CO2 sensor
unsigned long duration, th, tl;           // Timing variables for CO2 reading
int ppm;       

// Function to monitor CO2 levels
void CO2_Monitor() {
  th = pulseIn(CO2_PIN, HIGH, 2008000) / 1000;
  tl = 1004 - th;
  ppm = 2000 * (th - 2) / (th + tl - 4);
  Serial.print("CO2 Concentration: ");
  Serial.println(ppm);
  }

  void setup() {
  Serial.begin(9600);      // Initialize serial communication
  pinMode(CO2_PIN, INPUT); // Set CO2 sensor pin as input      
  delay(1000);     
}

void loop() {
 
  CO2_Monitor();      // Read CO2 concentration
    delay(2000);             // Delay for system stability
}