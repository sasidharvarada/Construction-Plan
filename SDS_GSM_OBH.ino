#include <Wire.h>
#include <RTClib.h>
#include <SD.h>
#include <SPI.h>
#include <SoftwareSerial.h>
#include <HardwareSerial.h>


SoftwareSerial myGSM(25,26);
HardwareSerial sdsSerial(1);
float y_1;
float y_2;
float m1=1.16894125;
float c1=-0.1620872235776547;
float m2=0.78865541;
float c2=-3.5453974804348496;


unsigned long previousMillis = 0;
const unsigned long RECONNECT_INTERVAL = 30000;

// SD Card Configuration
File dataFile;
const char* SD_FILENAME = "/Sound_Node_4/SDS_1D_NODE.csv";

//sds config
uint16_t pm25Value,pm10Value;

//RTC Configuration
RTC_DS3231 rtc;
String rtc_date_time;

void sendDataToThingSpeak() {
  if (myGSM.available())
  Serial.write(myGSM.read());
  myGSM.println("AT");
  delay(1000);
  
  myGSM.println("AT+CPIN?");
  delay(1000);
  myGSM.println("AT+CREG?");
  delay(1000);
  myGSM.println("AT+CGATT=1");
  delay(1000);
  myGSM.println("AT+CIPSHUT");
  delay(1000);
  myGSM.println("AT+CIPSTATUS");
  delay(2000);
  //myGSM.println("AT+CIPMUX=0");
  //delay(2000);
  ShowSerialData();
  myGSM.println("AT+CSTT=\"bsnlnet\"");  //start task and setting the APN,
  // myGSM.println("AT+CSTT=\"airtelgprs.com\"");
  delay(1000);
  ShowSerialData();
  myGSM.println("AT+CIICR");  //bring up wireless connection
  delay(3000);
  ShowSerialData();
  myGSM.println("AT+CIFSR");  //get local IP adress
  delay(2000);
  ShowSerialData();
  myGSM.println("AT+CIPSPRT=0");
  delay(3000);
  ShowSerialData();
  myGSM.println("AT+CIPSTART=\"TCP\",\"api.thingspeak.com\",\"80\"");  //start up the connection
  delay(6000);
  ShowSerialData();
  myGSM.println("AT+CIPSEND");  //begin send data to remote server
  delay(4000);
  ShowSerialData();
  String str = "GET https://api.thingspeak.com/update?api_key=LU9XOREDSJ5FFBS8&field1=" + String(y_1)+"&field2="+ String(y_2)+"&field3="+ String(pm25Value)+"&field4="+String(pm10Value);
  Serial.println(str);
  myGSM.println(str);  //begin send data to remote server
  delay(4000);
  ShowSerialData();
  myGSM.println((char)26);  //sending
  delay(5000);              //waitting for reply, important! the time is base on the condition of internet
  myGSM.println();
  ShowSerialData();
  myGSM.println("AT+CIPSHUT");  //close the connection
  delay(100);
  
  ShowSerialData();
  delay(1000);
}


void ShowSerialData() {
  while (myGSM.available() != 0)
    Serial.write(myGSM.read());
  delay(1000);
}

void SD_setup() {
  if (!SD.begin()) {
    Serial.println("Card Mount Failed");
    return;
  }

  if (!SD.exists(SD_FILENAME)) {
    dataFile = SD.open(SD_FILENAME, FILE_WRITE);
    if (dataFile) {
      dataFile.println("pm2.5,pm10");
      dataFile.close();
      Serial.println("CSV file created successfully!");
    } else {
      Serial.println();
      Serial.println("Error creating CSV file");
    }
  } else {
    Serial.println();
    Serial.println("File exists, Appending to existing file");
  }
}

void rtc_setup() {
  if (!rtc.begin() || rtc.lostPower()) {
    rtc.adjust(DateTime(F("2024-08-23"), F("20:00:00")));
  }
  Serial.println("RTC Found!");
}

void rtc_loop() {
  Serial.print("RTC Time: ");
  DateTime now = rtc.now();
  rtc_date_time = String(now.day(), DEC) + "-" + String(now.month(), DEC) + "-" + String(now.year(), DEC) + " " + String(now.hour(), DEC) + ":" + String(now.minute(), DEC) + ":" + String(now.second(), DEC);
  Serial.println(rtc_date_time);
}

void SD_final() {
  dataFile = SD.open(SD_FILENAME, FILE_APPEND);
  if (dataFile) {
    // dataFile.print(rtc_date_time);
    // dataFile.print(",");
    // Serial.println("Timestamp data updated successfully!");
    dataFile.print(pm25Value);
    dataFile.print(",");
    dataFile.print(pm10Value);
    Serial.println("---------- Sound updated successfully! -------------");
    dataFile.println("");
    Serial.println("---------- Updated successfully! -------------");
    dataFile.close();
  } else {
    Serial.println("-------------- Error updating ----------------");
  }
  Serial.printf("Used space: %lluMB\n", SD.usedBytes() / (1024 * 1024));
}

void sds_aqi_loop() {
  if (sdsSerial.available() >= 10) {
    uint8_t buffer[10]; // Buffer to hold the 10-byte packet
    
    // Read the 10-byte packet
    for (int i = 0; i < 10; i++) {
      buffer[i] = sdsSerial.read();
    }
    
    // Check for start characters and valid packet
    if (buffer[0] == 0xAA && buffer[1] == 0xC0 && buffer[9] == 0xAB) {
      // Extract PM2.5 and PM10 values
      pm25Value = (buffer[2] | (buffer[3] << 8)); // PM2.5 in µg/m³
      pm10Value = (buffer[4] | (buffer[5] << 8)); // PM10 in µg/m³
      
      // Print PM2.5 and PM10 values
      Serial.print("PM2.5: ");
      Serial.print(pm25Value);
      Serial.print(" µg/m³, ");
      
      Serial.print("PM10: ");
      Serial.print(pm10Value);
      Serial.println(" µg/m³");
      y_1=m1*pm25Value+c1;
      y_2=m2*pm10Value+c2;
      Serial.print("Calib value pm2.5: ");
      Serial.print(y_1);
      Serial.print("Calib Value pm10 :");
      Serial.print(y_2);
    }
  }
  delay(1000);
}

void setup() {
  Serial.begin(9600);
  Serial.println("Starting ESP32...");
  Wire.begin();
  rtc_setup();
  sdsSerial.begin(9600, SERIAL_8N1, 16, 17);
  delay(30000);
  SD_setup();
  myGSM.begin(9600);
  delay(1000);
  Serial.println("SIM800L Initialized");
}


void loop() {
  unsigned long currentMillis = millis();
  sds_aqi_loop();
  if ((currentMillis - previousMillis >= RECONNECT_INTERVAL)) {
    Serial.println("Sending data to ThingSpeak...");
    //rtc_loop();
    sds_aqi_loop();
    SD_final();
    sendDataToThingSpeak();
    previousMillis = currentMillis;
  }
  delay(1000);
}