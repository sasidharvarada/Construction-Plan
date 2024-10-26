/*
 * scrc_noise.cpp
 *
 *  Created on: 16-Oct-2020
 *      Author: BSRC-Sam
 *  Last update: 20-08-2024
 *      Author: SCRC-Sasidhar
 */

#include <Arduino.h>
#include "scrc_noise.h"
#include "scrc_constants.h"

#define SOUND_SENSOR_PIN A0  // Define the analog pin for the sound sensor
#define VREF 3.3  // Voltage reference for the ESP8266

#define MIN_NOISE_READING 0.0  // Minimum noise level (in dBA)
#define MAX_NOISE_READING 130.0  // Maximum noise level (in dBA)

void hw_setup_noise() {
    // No specific setup needed for the analog noise sensor
    Serial.println("Noise sensor setup complete");
}

void hw_read_noise(float *buf_dbValue,float *buf_dbValue_cal){
    Serial.println("...hw_read_noise");
    
    float voltageValue = analogRead(SOUND_SENSOR_PIN) / 1024.0 * VREF;
    *buf_dbValue = voltageValue * 50.0;  // Convert voltage to decibel value
      
      Serial.println(analogRead(SOUND_SENSOR_PIN));

      Serial.println(voltageValue);

    // Error validation
    if (isnan(*buf_dbValue) || *buf_dbValue < MIN_NOISE_READING || *buf_dbValue > MAX_NOISE_READING) {
        *buf_dbValue = NAN;
    }

    Serial.print("Noise level (dBA): ");
    Serial.println(*buf_dbValue);
    
    float db_cal = (m_db * (*buf_dbValue)) + c_db;

    *buf_dbValue_cal = db_cal ;

    Serial.print(" Calibrated Noise level (dBA): ");
    Serial.println(*buf_dbValue_cal);
}
