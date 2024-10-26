/*
 * scrc_time.cpp
 *
 *  Created on: 16-Oct-2020
 *      Author: BSRC-Sam
 *  last update :22-08-2023
 *      Author : SCRC-Sasidhar
 */
#include <Arduino.h>
#include <WiFiUdp.h>
#include <NTPClient.h>
#include <ESP8266WiFi.h>
#include "scrc_time.h"
#include <ESP32Time.h>
#include "scrc_node.h"


#define LEAP_YEAR(Y)     ( (Y>0) && !(Y%4) && ( (Y%100) || !(Y%400) ) )

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org");//time.iiit.ac.in

ESP32Time rtc(0);  // offset in seconds GMT+5:30 (India Standard Time)
// const char* ntpServer = "pool.ntp.org";

#define MIN_VALID_TIME 1672531200  // Unix timestamp for 1st Jan 2023 00:00:00
#define MAX_VALID_TIME 2082844799  // Unix timestamp for 1st Jan 2036 00:00:00

static uint64_t ntp_epoch_time = 0;

static uint64_t last_update = 0;


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
        if(ntp_epoch_time < 1672000000){
          sync_time();
        }
        // Print the universal time and epoch time
          Serial.print("Universal time: " + rtc.getDateTime(true) + "\t");
          Serial.println(ntp_epoch_time, DEC); // For UTC, take timeoffset as 0
          Serial.println("");
        // Update the last_update time
        last_update = millis();
        return;  // Exit the function after successful synchronization
      } else {
        // Invalid NTP time, reduce the number of remaining attempts
        Serial.println("Invalid NTP time, retrying...");
        num_tries--;
        delay(1000);  
        Serial.println("All attempts failed, performing restarting time function ...");
              ESP.restart();
              // sync_time();
      }
    }
  }
}

/*
 *  return timestamp in seconds
 */
uint64_t get_timestamp() {
	return ntp_epoch_time + ((millis() - last_update) / 1000);
}

uint64_t get_timestamp(unsigned long milli) {
	return ntp_epoch_time + ((milli - last_update) / 1000);
}

String get_timestamp_str(uint64_t timestamp, uint16_t timeoffset) {
	/*
	 adapted from https://github.com/arduino-libraries/NTPClient/blob/master/NTPClient.cpp
	 */
	unsigned long hours = ((timestamp + timeoffset) % 86400L) / 3600;
	String hoursStr = hours < 10 ? "0" + String(hours) : String(hours);

	unsigned long minutes = ((timestamp + timeoffset) % 3600) / 60;
	String minuteStr = minutes < 10 ? "0" + String(minutes) : String(minutes);

	unsigned long seconds = (timestamp + timeoffset) % 60;
	String secondStr = seconds < 10 ? "0" + String(seconds) : String(seconds);

	return hoursStr + ":" + minuteStr + ":" + secondStr;
}

String get_datestamp_str(uint64_t timestamp, uint16_t timeoffset) {
	/*
	 adapted from https://github.com/taranais/NTPClient/blob/master/NTPClient.cpp
	 */
	unsigned long rawtime = ((timestamp + timeoffset) / 86400L);

	unsigned long days = 0, year = 1970;
	uint8_t month;

	static const uint8_t monthDays[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31,
			30, 31 };

	while ((days += (LEAP_YEAR(year) ? 366 : 365)) <= rawtime)
		year++;

	rawtime -= days - (LEAP_YEAR(year) ? 366 : 365); // now it is days in this year, starting at 0
	days = 0;

	for (month = 0; month < 12; month++) {
		uint8_t monthLength;
		if (month == 1) { // February
			monthLength = LEAP_YEAR(year) ? 29 : 28;
		} else {
			monthLength = monthDays[month];
		}
		if (rawtime < monthLength)
			break;
		rawtime -= monthLength;
	}
	String monthStr = ++month < 10 ? "0" + String(month) : String(month); // January is month 1
	String dayStr = ++rawtime < 10 ? "0" + String(rawtime) : String(rawtime); // day of month
	return String(year) + "-" + monthStr + "-" + dayStr;
}

/*
 *
 */
String get_date_timestamp_str(uint64_t timestamp, uint16_t timeoffset) {
	return (get_datestamp_str(timestamp, timeoffset) + " "
			+ get_timestamp_str(timestamp, timeoffset));
}
