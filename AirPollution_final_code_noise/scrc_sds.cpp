#include <SDS011.h>
#include "Arduino.h"
#include "scrc_sds.h"
#include "scrc_constants.h"
#define MIN_READING 0.1
#define MAX_READING 999.9
#define node_RX D5
#define node_TX D6

SDS011 my_sds;
float p25, p10;


void hw_setup_sds() {
    my_sds.begin(D5, D6);
}

void hw_read_sds(float *buf_pm25, float *buf_pm25cal , float *buf_pm10, float *buf_pm10cal) {
    float error = my_sds.read(&p25, &p10);
    Serial.println(p25);
    float pm25_cal = (m_pm25 * p25) + c_pm25;
    Serial.println("//////////////////////////////////");
    Serial.println(pm25_cal);

    *buf_pm25cal = pm25_cal; // Store the calculated value in the buffer

    *buf_pm25 = p25;
    //error = validate_pm25(p25);
    if (*buf_pm25 == 0 || *buf_pm25 < MIN_READING || *buf_pm25 > MAX_READING) {
        *buf_pm25 = NAN;
    }

    Serial.print("PM25 :");
    Serial.println(*buf_pm25);

    *buf_pm10 = p10;
    float pm10_cal = (m_pm10 * p10) + c_pm10;
    Serial.println("//////////////////////////////////");
    Serial.println(pm10_cal);

    *buf_pm10cal = pm10_cal; // Store the calculated value in the buffer
    //error = validate_pm10(p10);
    if (*buf_pm10 == 0 || *buf_pm10 < MIN_READING || *buf_pm10 > MAX_READING) {
        *buf_pm10 = NAN;
    }
    Serial.print("PM10 :");
    Serial.println(*buf_pm10);
   
    Serial.print("PM25_cal :");
    Serial.println(*buf_pm25cal);

    Serial.print("PM10_cal :");
    Serial.println(*buf_pm10cal);


}
