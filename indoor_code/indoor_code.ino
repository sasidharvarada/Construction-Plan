#include <ThingSpeak.h>          // For ThingSpeak communication
#include <WiFi.h>                // For WiFi connectivity
#include <WiFiUdp.h>             // For WiFi UDP
#include <Adafruit_AHT10.h>      // For AHT10 sensor (Temperature and Humidity)
#include <time.h>
#include <NTPClient.h>
#include <ESP32Time.h>
#include <HTTPClient.h>
#include "constants.h"

void initWiFi() {
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.println("Connecting to WiFi");
  unsigned long startTime = millis();
  while (WiFi.status() != WL_CONNECTED && millis() - startTime < 30000) {
    Serial.print('.');
    delay(1000);
  }
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\nConnected to " + String(WIFI_SSID) + " network");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
    Serial.print("Mac Address: ");
    Serial.println(WiFi.macAddress());
    Serial.print("Signal strength (RSSI): ");
    Serial.println(WiFi.RSSI());
  } else {
    Serial.println("\nFailed to connect to WiFi within 30 seconds. Restarting...");
    ESP.restart();
  }
}

void sync_time() {
  static bool first_time = true;
  int num_tries = 5;  // Number of attempts to get valid NTP time

  // Check if the ESP32 is connected to WiFi
  if (WiFi.status() == WL_CONNECTED) {
    if (first_time == true) {
      // Initialize NTPClient only once
      timeClient.begin();
      timeClient.setTimeOffset(0);
      timeClient.update();
      first_time = false;
    }
    // Configure the time zone (IST: Indian Standard Time, UTC+5:30)
    configTime(5 * 3600, 30 * 60, "pool.ntp.org");
    while (num_tries > 0) {
      // Get the obtained NTP time
      uint64_t ntp_time = timeClient.getEpochTime();
      Serial.println(ntp_time);
      // Validate the obtained NTP time
      if (ntp_time != 0 && ntp_time >= MIN_VALID_TIME && ntp_time <= MAX_VALID_TIME) {
        // Set the RTC time using the NTP time
        rtc.setTime(ntp_time);
        ntp_epoch_time = rtc.getEpoch();
        Serial.println(ntp_epoch_time);
        if (ntp_epoch_time < 1672000000) {
          sync_time();
        }
        // Print the universal time and epoch time
        Serial.print("Universal time: " + rtc.getDateTime(true) + "\t");
        Serial.println(ntp_epoch_time, DEC); // For UTC, take timeoffset as 0
        // Update the last_update time
        prev_time = millis();
        return;  // Exit the function after successful synchronization
      } else {
        // Invalid NTP time, reduce the number of remaining attempts
        Serial.println("Invalid NTP time, retrying...");
        num_tries--;
        delay(1000);
        Serial.println("All attempts failed, performing restarting time function ...");
        ESP.restart();
      }
    }
  }
}

void aht_setup() {
  if (!aht.begin()) {
    Serial.println("Failed to find AHT10 chip");
    while (1) {
      delay(10);
    }
  }
  Serial.println("AHT10 Found!");
  aht_temp = aht.getTemperatureSensor();
  aht_humidity = aht.getHumiditySensor();
}

void aht_loop() {
  sensors_event_t humidity;
  sensors_event_t temp;
  aht_humidity->getEvent(&humidity);
  aht_temp->getEvent(&temp);
  t = temp.temperature;
  h = humidity.relative_humidity;
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.println(" °C\t");
  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.println("% rH");
  ThingSpeak.setField(1, t);
  ThingSpeak.setField(2, h);
}

void PM_setup() {
  sendCommand(0x01);
  Serial.println("PM Found!");
}

void PM_Reading() {
  if (millis() - prev_time > 5000) {
    sendCommand(0x02);
    prev_time = millis();
  }
  if (Serial.available()) {
    Serial.readBytes(received_data, 9);
    if (checksum()) {
      calculatePM();
    }
  }
}

void sendCommand(byte command) {
  command_frame[1] = command;
  sum = command_frame[0] + command_frame[1] + command_frame[2] + command_frame[3] + command_frame[4] + command_frame[5] + command_frame[8];
  int rem = sum % 256;
  command_frame[6] = (sum - rem) / 256;
  command_frame[7] = rem;
  delay(1000);
  Serial.write(command_frame, 9);
}

bool checksum() {
  sum = int(received_data[0]) + int(received_data[1]) + int(received_data[2]) + int(received_data[3]) + int(received_data[4]) + int(received_data[5]) + int(received_data[8]);
  return sum == ((int(received_data[6]) * 256) + int(received_data[7]));
}

void calculatePM() {
  pm2 = int(received_data[4]) * 256 + int(received_data[5]);
  delay(2000);
  pm10 = int(received_data[2]) * 256 + int(received_data[3]);
  Serial.print("PM2.5: ");
  Serial.println(pm2);
  Serial.print("PM10: ");
  Serial.println(pm10);
  pm2_cal = (m_pm2 * pm2) + c_pm2;
  pm10_cal = (m_pm10 * pm10) + c_pm10;
  Serial.print("PM2.5_cal: ");
  Serial.println(pm2_cal);
  Serial.print("PM10_cal: ");
  Serial.println(pm10_cal);

  if (pm2 < 2000) {
    ThingSpeak.setField(3, pm2);
    ThingSpeak.setField(4, pm2_cal);
    ThingSpeak.setField(5, pm10);
    ThingSpeak.setField(6, pm10_cal);
  }
}

void CO2_Monitor() {
  th = pulseIn(CO2_PIN, HIGH, 2008000) / 1000;
  tl = 1004 - th;
  ppm = 2000 * (th - 2) / (th + tl - 4);
  Serial.print("CO2 Concentration: ");
  Serial.println(ppm);
  ThingSpeak.setField(7, ppm);
}

void sound_loop() {
  voltageValue = analogRead(SoundSensorPin) / 4096.0 * VREF;
  dbValue = voltageValue * 50.0;

  Serial.print("Noise :");
  Serial.print(dbValue, 1);
  Serial.println(" dBA");

  dbValue_cal = (m_db * (dbValue)) + c_db;
  Serial.print(" Calibrated Noise level (dBA): ");
  Serial.println(dbValue_cal);
  
  ThingSpeak.setField(8, dbValue);
}

float calculate_AQI(float pm2_cal, float pm10_cal, int ppm) {
    // Calculate PM2.5 sub-index
    float pm25_subIndex;
    if (pm2_cal <= 30) pm25_subIndex = pm2_cal * 50 / 30;
    else if (pm2_cal <= 60) pm25_subIndex = 50 + (pm2_cal - 30) * 50 / 30;
    else if (pm2_cal <= 90) pm25_subIndex = 100 + (pm2_cal - 60) * 100 / 30;
    else if (pm2_cal <= 120) pm25_subIndex = 200 + (pm2_cal - 90) * 100 / 30;
    else if (pm2_cal <= 250) pm25_subIndex = 300 + (pm2_cal - 120) * 100 / 130;
    else pm25_subIndex = 400 + (pm2_cal - 250) * 100 / 130;

    // Calculate PM10 sub-index
    float pm10_subIndex;
    if (pm10_cal <= 50) pm10_subIndex = pm10_cal;
    else if (pm10_cal <= 100) pm10_subIndex = pm10_cal;
    else if (pm10_cal <= 250) pm10_subIndex = 100 + (pm10_cal - 100) * 100 / 150;
    else if (pm10_cal <= 350) pm10_subIndex = 200 + (pm10_cal - 250);
    else if (pm10_cal <= 430) pm10_subIndex = 300 + (pm10_cal - 350) * 100 / 80;
    else pm10_subIndex = 400 + (pm10_cal - 430) * 100 / 80;

    // Calculate CO2 sub-index
    float co2_subIndex;
    if (ppm <= 400) co2_subIndex = ppm * 50 / 400;                     // Safe level
    else if (ppm <= 1000) co2_subIndex = 50 + (ppm - 400) * 50 / 600;  // Moderate level
    else if (ppm <= 2000) co2_subIndex = 100 + (ppm - 1000) * 100 / 1000; // Unhealthy for sensitive groups
    else if (ppm <= 5000) co2_subIndex = 200 + (ppm - 2000) * 100 / 3000; // Unhealthy
    else co2_subIndex = 300 + (ppm - 5000) * 100 / 5000;               // Very unhealthy/hazardous

    // Determine AQI as the maximum of the three sub-indices
    float maxIndex = pm25_subIndex;
    if (pm10_subIndex > maxIndex) maxIndex = pm10_subIndex;
    if (co2_subIndex > maxIndex) maxIndex = co2_subIndex;
    
    Serial.println("AQI value is "+ String(maxIndex));
    return maxIndex; // Return the highest sub-index as the AQI

    
}

void postToThingSpeak() {
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("Connected ");
  }
  int x = ThingSpeak.writeFields(CHANNEL_ID, CHANNEL_API_KEY);
  ThingSpeak.writeFields(CHANNEL_ID, CHANNEL_API_KEY);
  if (x == 200) {
    Serial.println("Channel update successful.");
  } else {
    Serial.println("Problem updating channel. HTTP error code " + String(x));
  }
}

void postToOneM2M() {
  if (WiFi.status() != WL_CONNECTED) {
    return;
  }

  String data = "[" + String(ntp_epoch_time) + " , " + String(pm2) + " , " + String(pm2_cal) + " , " + String(pm10) + " , " + String(pm10_cal) + " , " + String(t) + " , " + String(h) + " , " + String(ppm) + " , " + String(dbValue) +" , " + String(dbValue_cal) +" , " + String(aqiValue)+"]";

  String server = "http://" + String(CSE_IP) + ":" + String(CSE_PORT) + String(OM2M_MN);

  http.begin(server + OM2M_AE + "/" + OM2M_DATA_CONT + "/");

  http.addHeader("X-M2M-Origin", OM2M_ORGIN);
  http.addHeader("Content-Type", "application/json;ty=4");
  http.addHeader("Content-Length", String(data.length()));

  String req_data = "{\"m2m:cin\": {"
                    "\"con\": \""
                    + data + "\","
                             "\"lbl\": "
                    + OM2M_DATA_LBL + ","
                                      "\"cnf\": \"text\""
                                      "}}";
  code = http.POST(req_data);
  http.end();
  Serial.println("OneM2M HTTP Response Code: " + String(code));
}

void setup() {
  Serial.begin(9600);        // Initialize serial communication
  initWiFi();                // Initialize WiFi connection
  sync_time();
  PM_setup();                // Initialize PM sensor
  pinMode(CO2_PIN, INPUT);   // Set CO2 sensor pin as input
  aht_setup();               // Initialize AHT10 sensor
  pinMode(SoundSensorPin, INPUT);  // Set sound sensor pin as input
  ThingSpeak.begin(client);
  Serial.println("Starting ESP32...");
  delay(3000);               // Delay for system stability
}

void loop() {
  unsigned long currentMillis = millis();  // Get current time in milliseconds

  // Reconnect to WiFi if not connected
  if ((WiFi.status() != WL_CONNECTED) && (currentMillis - previousMillis >= 10000)) {
    Serial.println("Reconnecting to WiFi...");
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    while (WiFi.status() != WL_CONNECTED) {
      Serial.print('.');
      delay(1000);
    }
    Serial.println(" WiFi reconnected");
    previousMillis = currentMillis;
  }

  // Call sensor monitoring functions
  aht_loop();         // Read temperature and humidity
  PM_Reading();       // Read PM2.5 and PM10 levels
  CO2_Monitor();      // Read CO2 concentration
  sound_loop();       // Read sound levels
  aqiValue = calculate_AQI(pm2_cal, pm10_cal, ppm);
  //post the data
  postToThingSpeak();
  postToOneM2M();
  delay(5000);
}
