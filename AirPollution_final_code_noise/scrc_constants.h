/*
 * scrc_constant.h
 *
 *  Created on: 16-Oct-2020
 *      Author: BSRC-Sam
 *  last update :22-08-2023
 *      Author : SCRC-Sasidhar
 */

#ifndef INCLUDE_SCRC_CONSTANT_H_
#define INCLUDE_SCRC_CONSTANT_H_

/*
 * uncomment to print debug statements
 */
#define DEBUG false

/*
 * node type
 */

#define NT_POLLUTION
//#define NT_WATER
#define led_pin D7
/*
 * Controller type
 */
#define CT_ESP_8266
//#define CT_ESP_32

/*
 * uncomment to publish to om2m
 */
#define PUB_OM2M

/*
 * uncomment to publish to ThingSpeak
 */
#define PUB_THINGSPEAK

/*
 * time interval in milliseconds
 */
#define TIME_INTERVAL_15_SEC  15000

#define TIME_INTERVAL_1_HR    3600000             //1 * 60* 60 * 1000

#define TIME_INTERVAL_10_MIN  600000             //10*60 * 1000
#define TIME_INTERVAL_1_MIN  60000             //10*60 * 1000

// count of sensor reading in 10 min @ 15 sec, i.e., 4 reading per min, (40)
#define PRIMARY_BUF_COUNT  40

// count of 10 min avg sensor reading in 1 days, i.e., 6 reading per 1 hour, (144 reading)
#define SEC_BUF_COUNT  100

// #define NODE_1     //GuestHouse 
// #define NODE_2     //Main gate
// #define NODE_3     //T-Hub
// #define NODE_4     //Pump House -3
// #define NODE_5     //Library
// #define NODE_6     //Palash Nivas
// #define NODE_7     //Food Ball Ground
// #define NODE_8     //kadhamaba 
// #define NODE_9     //Faculty Quaters
#define NODE_10    //ph-4


/*
 * WiFi credentials
 * Thingspeak Credentials
 * Https  define 
//  */

  // #define MAIN_SSID "JioFi3_259D0E" // air-iot wifi  
  // #define MAIN_PASS "k61m12m0u5"

#ifdef NODE_1 // Guest house

  // #define MAIN_SSID "SAHANA-1"  
  // #define MAIN_PASS "0BEEF6590BEEF6590BEEF65926"
  
  #define MAIN_SSID "TP-Link_1E6D"//main
  #define MAIN_PASS "18228953"

  #define HTTPS     false
  #define OM2M_NODE_ID   "AQ-SN00-00"
  #define OM2M_DATA_CONT  "AQ-SN00-00/Data"
  #define OM2M_DATA_LBL   "[\"AE-AQ\", \"V4.1.0\", \"AQ-SN00-00\", \"AQ-V4.1.0\"]"
  
  #define myChannel 885762;
  #define writeAPIKey  "VWMXNW6NJOQVVVI3"
 
  const float m_pm25 = 1.41658769;
  const float c_pm25 = -17.59258932;
  const float m_pm10 = 1.09787734;
  const float c_pm10 = -45.27896897;
  const float m_db = 1.11269314;
  const float c_db = -17.7747384;
  const float m_temp = 1.0;
  const float c_temp = 0.0;
  const float m_rh = 1.0;
  const float c_rh = 0.0;

#endif

#ifdef NODE_2 // Main Gate 

  #define MAIN_SSID "TP-Link_0EC8"  
  #define MAIN_PASS "78726598" 

  #define HTTPS     false
  #define OM2M_NODE_ID   "AQ-MG00-00"
  #define OM2M_DATA_CONT  "AQ-MG00-00/Data"
  #define OM2M_DATA_LBL   "[\"AE-AQ\", \"V4.1.0\", \"AQ-MG00-00\", \"AQ-V4.1.0\"]"

  #define myChannel 939888;
  #define writeAPIKey  "WDVVTDSX00XL5V05"

  const float m_pm25 = 1.40246426;
  const float c_pm25 = 6.246854816;
  const float m_pm10 = 1.17011993;
  const float c_pm10 = -26.75273789;
  const float m_db = 1.02441544;
  const float c_db = -10.72394619;
  const float m_temp = 1.0;
  const float c_temp = 0.0;
  const float m_rh = 1.0;
  const float c_rh = 0.0;

#endif

#ifdef NODE_3  //Behind // T-hub

  #define MAIN_SSID "esw-m19@iiith"         
  #define MAIN_PASS "e5W-eMai@3!20hOct"

  // #define HTTPS     false
  // #define OM2M_NODE_ID   "AQ-KH00-00"
  // #define OM2M_DATA_CONT  "AQ-KH00-00/Data"
  // #define OM2M_DATA_LBL   "[\"AE-AQ\", \"V4.0.0\", \"AQ-KH00-00\", \"AQ-V4.0.0\"]"

  #define HTTPS     false
  #define OM2M_NODE_ID   "AQ-TH00-00"
  #define OM2M_DATA_CONT  "AQ-TH00-00/Data"
  #define OM2M_DATA_LBL   "[\"AE-AQ\", \"V4.1.0\", \"AQ-TH00-00\", \"AQ-V4.1.0\"]"

  #define myChannel 947311;
  #define writeAPIKey  "1CLG8H9WWR7Y7HGF"

  const float m_pm25 = 1.87335395;
  const float c_pm25 = 13.23741689;
  const float m_pm10 = 1.69155145;
  const float c_pm10 = 13.54872622;
  const float m_db = 2.31051237;
  const float c_db = -119.9798494;
  const float m_temp = 1.0;
  const float c_temp = 0.0;
  const float m_rh = 1.0;
  const float c_rh = 0.0;

#endif

#ifdef NODE_4  //Pump House -3

  // #define MAIN_SSID "JioFi3_B51E5B" 
  // #define MAIN_PASS "P1m9h0u53@3"

  #define HTTPS     false
  #define OM2M_NODE_ID   "AQ-PH03-00"
  #define OM2M_DATA_CONT  "AQ-PH03-00/Data"
  #define OM2M_DATA_LBL   "[\"AE-AQ\", \"V4.1.0\", \"AQ-PH03-00\", \"AQ-V4.1.0\"]"

  #define myChannel 1099442;
  #define writeAPIKey  "UUESWH1NUKNQXM47"

  const float m_pm25 = 1.44879669;
  const float c_pm25 = 9.841701201;
  const float m_pm10 = 1.27246423;
  const float c_pm10 = -19.26395298;
  const float m_db = 1.19493434;
  const float c_db = -19.64293589;
  const float m_temp = 1.0;
  const float c_temp = 0.0;
  const float m_rh = 1.0;
  const float c_rh = 0.0;

#endif

#ifdef NODE_5 //library

  // #define MAIN_SSID "esw-m19@iiith"         
  // #define MAIN_PASS "e5W-eMai@3!20hOct"

  #define HTTPS     false
  #define OM2M_NODE_ID   "AQ-VN90-00"
  #define OM2M_DATA_CONT  "AQ-VN90-00/Data"
  #define OM2M_DATA_LBL   "[\"AE-AQ\", \"V4.1.0\", \"AQ-VN90-00\", \"AQ-V4.1.0\"]"

  #define myChannel 944545;
  #define writeAPIKey  "LH08QHJZ82YEXWUL"

  const float m_pm25 = 1.3022951;
  const float c_pm25 = 2.356997737;
  const float m_pm10 = 1.15422263;
  const float c_pm10 = -13.44127555;
  const float m_db = 9.14919991;
  const float c_db = -602.786015;
  const float m_temp = 1.0;
  const float c_temp = 0.0;
  const float m_rh = 1.0;
  const float c_rh = 0.0;

#endif

#ifdef NODE_6 //Palash Nivas

  #define MAIN_SSID "TP-Link_3934"  
  #define MAIN_PASS "wdsdtumt9r"


  #define HTTPS     false
  #define OM2M_NODE_ID   "AQ-PL00-00"
  #define OM2M_DATA_CONT  "AQ-PL00-00/Data"
  #define OM2M_DATA_LBL   "[\"AE-AQ\", \"V4.1.0\", \"AQ-PL00-00\", \"AQ-V4.1.0\"]"

  #define myChannel 938513;
  #define writeAPIKey  "SP2M6BRIC92GPIM8"

  const float m_pm25 = 1.46108889;
  const float c_pm25 = -7.568486667;
  const float m_pm10 = 1.26144671;
  const float c_pm10 = -22.83544894;
  const float m_db = 1.19083974;
  const float c_db = -19.38941144;
  const float m_temp = 1.0;
  const float c_temp = 0.0;
  const float m_rh = 1.0;
  const float c_rh = 0.0;

#endif

#ifdef NODE_7 //Food Ball Ground

  // #define MAIN_SSID "esw-m19@iiith"         
  // #define MAIN_PASS "e5W-eMai@3!20hOct"

  // #define MAIN_SSID "TP-Link_BC75"       
  // #define MAIN_PASS "67653416"


  #define HTTPS     false
  #define OM2M_NODE_ID   "AQ-FG00-00"
  #define OM2M_DATA_CONT  "AQ-FG00-00/Data"
  #define OM2M_DATA_LBL   "[\"AE-AQ\", \"V4.1.0\", \"AQ-FG00-00\", \"AQ-V4.1.0\"]"

  #define myChannel 945028;
  #define writeAPIKey  "4PCMYWJ8XUHUSHUW"

  const float m_pm25 = 1.30534432;
  const float c_pm25 = -6.809701336;
  const float m_pm10 = 1.14220252;
  const float c_pm10 = -27.0608309;
  const float m_db = 3.51650074;
  const float c_db = -146.1569537;
  const float m_temp = 1.0;
  const float c_temp = 0.0;
  const float m_rh = 1.0;
  const float c_rh = 0.0;

#endif

#ifdef NODE_8 //Khdhamaba Nivas

  #define MAIN_SSID "TP-Link_5674"
  #define MAIN_PASS "49508680"
  
  #define HTTPS     false
  #define OM2M_NODE_ID   "AQ-KN00-00"
  #define OM2M_DATA_CONT  "AQ-KN00-00/Data"
  #define OM2M_DATA_LBL   "[\"AE-AQ\", \"V4.1.0\", \"AQ-KN00-00\", \"AQ-V4.1.0\"]"

  #define myChannel 937750;
  #define writeAPIKey  "W9L6N34IC1MNE7HN"

  const float m_pm25 = 1.35980515;
  const float c_pm25 = -24.60760663;
  const float m_pm10 = 1.16818845;
  const float c_pm10 = -46.75823609;
  const float m_db = 1.15669996;
  const float c_db = -17.92279091;
  const float m_temp = 1.0;
  const float c_temp = 0.0;
  const float m_rh = 1.0;
  const float c_rh = 0.0;

#endif

#ifdef NODE_9//Anand Nivas
  
  #define MAIN_SSID "TP-Link_B2D2"
  #define MAIN_PASS "94057867" 

  #define HTTPS     false   
  #define OM2M_NODE_ID   "AQ-AN00-00"
  #define OM2M_DATA_CONT  "AQ-AN00-00/Data"
  #define OM2M_DATA_LBL   "[\"AE-AQ\", \"V4.1.0\", \"AQ-AN00-00\", \"AQ-V4.1.0\"]"

  #define myChannel 944798;
  #define writeAPIKey  "IGN8L3ACV8PWB9YK"

  const float m_pm25 = 1.40279987;
  const float c_pm25 = -2.773271711;
  const float m_pm10 = 1.24840238;
  const float c_pm10 = -15.42873319;
  const float m_db = 1.24840238;
  const float c_db = -16.73790347;
  const float m_temp = 1.0;
  const float c_temp = 0.0;
  const float m_rh = 1.0;
  const float c_rh = 0.0;

#endif

#ifdef NODE_10  //ph-4

  // #define HTTPS     true
  // #define OM2M_NODE_ID   "AQ-BN00-00"
  // #define OM2M_DATA_CONT  "AQ-BN00-00/Data"
  // #define OM2M_DATA_LBL   "[\"AE-AQ\", \"V4.0.0\", \"AQ-BN00-00\", \"AQ-V4.0.0\"]"
  
  // #define myChannel 928486;
  // #define writeAPIKey  "PSKWJ8GP0HS55WL6"

  #define MAIN_SSID "TP-Link_5470"  
  #define MAIN_PASS "32262728"

  #define HTTPS     false
  #define OM2M_NODE_ID   "AQ-PH04-00"
  #define OM2M_DATA_CONT  "AQ-PH04-00/Data"
  #define OM2M_DATA_LBL   "[\"AE-AQ\", \"V4.1.0\", \"AQ-PH04-00\", \"AQ-V4.1.0\"]"
  
  #define myChannel 2266784;
  #define writeAPIKey  "0T3RBYHFS9G0JWEJ"

  const float m_pm25 = 1.49245678;
  const float c_pm25 = -71.02253761;
  const float m_pm10 = 1.28807028;
  const float c_pm10 = -69.96708743;
  const float m_db = 1.18603921;
  const float c_db = -16.83130494;
  const float m_temp = 1.0;
  const float c_temp = 0.0;
  const float m_rh = 1.0;
  const float c_rh = 0.0;


#endif


#define RETRY_WIFI_INTERVAL 60000  // in ms (1 min)
#define RETRY_WIFI_FACTOR 2     //multiplication factor user to increment the retry interval

#define STARTUP_WIFI_TIMEOUT  60000   //WiFi connection Timeout
#define STARTUP_WIFI_RETRY_DELAY 100  // WiFi reconnection delay

#define Timeoffset 19800

#define Reading_10min 2

#define MAX_STRING_LEN 255

/*
 * OneM2M connection details
 */
#define CSE_IP      "onem2m.iiit.ac.in"
#define OM2M_ORGIN    "AirPoll@20:22uHt@Sas"
#define CSE_PORT    443
#define FINGER_PRINT  "10 3D D5 4E B1 47 DB 4B 5C B0 89 08 41 A7 A4 14 87 10 7F E8"
#define OM2M_MN       "/~/in-cse/in-name/"
#define OM2M_AE       "AE-AQ"

// #define OM2M_NODE_ID   "AQ-SN00-00"
// #define OM2M_DATA_CONT  "AQ-SN00-00/Data"
// #define OM2M_DATA_LBL   "[\"AE-AQ\", \"V4.0.0\", \"AQ-SN00-00\", \"AQ-V4.0.0\"]"
// dev-server
// #define CSE_IP      "dev-onem2m.iiit.ac.in"
// #define OM2M_ORGIN    "Tue_20_12_22:Tue_20_12_22"

/*
 Debug Function
 */
#if DEBUG
#define debug_info(fmt, ...) Serial.print(fmt, ##__VA_ARGS__)
#define debug_err(fmt, ...) Serial.print(fmt, ##__VA_ARGS__)
#else
  #define debug_info(fmt, ...) ((void)0)
  #define debug_err(fmt, ...) ((void)0)
#endif

/*
 * Error Handling Codes
 */
#define E_OM2M_NW -101
#define E_OM2M_CONNECT -102
#define E_OM2M_CONNECTION -103
#define E_OM2M_NO_RESPONSE -104
#define E_OM2M_EMPTY_RESPONSE -105

#define E_THINGSPEAK_NW -201
#define E_THINGSPEAK_CONNECT -202
#define E_THINGSPEAK_CONNECTION -203
#define E_THINGSPEAK_NO_RESPONSE -204
#define E_THINGSPEAK_EMPTY_RESPONSE -205

/*
 * Success Codes
 */
#define SUCCESS_OM2M 400
#define SUCCESS_THINGSPEAK 800

#endif /* INCLUDE_SCRC_CONSTANT_H_ */
