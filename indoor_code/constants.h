// WiFi Configuration
// const char* WIFI_SSID = "JioFi3_259D0E";  // WiFi SSID
// const char* WIFI_PASSWORD = "k61m12m0u5"; // WiFi Password

const char* WIFI_SSID = "esw-m19@iiith";  // WiFi SSID
const char* WIFI_PASSWORD = "e5W-eMai@3!20hOct"; // WiFi Password


#define CSE_IP			  "dev-onem2m.iiit.ac.in"
#define OM2M_ORGIN    "Tue_20_12_22:Tue_20_12_22"

// #define CSE_IP			  "onem2m.iiit.ac.in"  // onem2m
// #define OM2M_ORGIN    "AQSRMon@20:psX9MSnnrvyH"
#define CSE_PORT    443
#define HTTPS     false
#define OM2M_MN     "/~/in-cse/in-name/"
#define OM2M_AE     "AE-SR/SR-AQ"


// #define node_1  //VN90-00 //library              1 
// #define node_2//TH04-00    t-hub 5th floor    2
// #define node_3//SN00-00 air-iot lab           6
#define node_4//KN00-00//water-IOT lab        5
// #define node_5//KH95-01 lab _3
// #define node_6//VN01-00 sachin sir lab

#ifdef node_1

  #define CHANNEL_ID 2657305
  #define CHANNEL_API_KEY "Z8JPQP9Z110MJJCA"  

  #define OM2M_Node_ID "SR-AQ-VN90-00"
  #define OM2M_DATA_CONT  "SR-AQ-VN90-00/Data"
  #define OM2M_DATA_LBL "[\"AE-SR-AQ\", \"SR-AQ-VN90-00\", \"V3.1.0\", \"SR-AQ-V3.1.0\"]"

  float m_pm2 = 1.0;
  float c_pm2 = 1.0;
  float m_pm10 = 1.0;
  float c_pm10 = 1.0;

  float m_db = 1.0;
  float c_db = 1.0;

#endif

#ifdef node_2

  #define CHANNEL_ID 2657592
  #define CHANNEL_API_KEY "8C8CH9B2JUNZWYU6"

  #define OM2M_Node_ID "SR-AQ-TH04-00"
  #define OM2M_DATA_CONT  "SR-AQ-TH04-00/Data"
  #define OM2M_DATA_LBL "[\"AE-SR-AQ\", \"SR-AQ-TH04-00\", \"V3.1.0\", \"SR-AQ-V3.1.0\"]"

  float m_pm2 = 1.0;
  float c_pm2 = 1.0;
  float m_pm10 = 1.0;
  float c_pm10 = 1.0;

  float m_db = 1.0;
  float c_db = 1.0;

#endif

#ifdef node_3
  #define CHANNEL_ID 2657617
  #define CHANNEL_API_KEY "88KR7A5K4ASO4RE5"

  #define OM2M_Node_ID "SR-AQ-SN00-00"
  #define OM2M_DATA_CONT  "SR-AQ-SN00-00/Data"
  #define OM2M_DATA_LBL "[\"AE-SR-AQ\", \"SR-AQ-SN00-00\", \"V3.1.0\", \"SR-AQ-V3.1.0\"]"

  float m_pm2 = 1.0;
  float c_pm2 = 1.0;
  float m_pm10 = 1.0;
  float c_pm10 = 1.0;

  float m_db = 1.0;
  float c_db = 1.0;

#endif

#ifdef node_4

  #define CHANNEL_ID 2657616
  #define CHANNEL_API_KEY "CXI1Z1HP0VVDKIG7"

  #define OM2M_Node_ID "SR-AQ-KN00-00"
  #define OM2M_DATA_CONT  "SR-AQ-KN00-00/Data"
  #define OM2M_DATA_LBL "[\"AE-SR-AQ\", \"SR-AQ-KN00-00\", \"V3.1.0\", \"SR-AQ-V3.1.0\"]"

  float m_pm2 = 1.06805859;
  float c_pm2 = 1.421629131241616;
  float m_pm10 = 0.74048506;
  float c_pm10 = 21.169480930789746;

  float m_db = 1.0;
  float c_db = 1.0;

#endif

#ifdef node_5

  #define CHANNEL_ID  1591608
  #define CHANNEL_API_KEY "MGYZNCH5TAPELMYO"

  #define OM2M_Node_ID "SR-AQ-KH95-01"
  #define OM2M_DATA_CONT  "SR-AQ-KH95-01/Data"
  #define OM2M_DATA_LBL "[\"AE-SR-AQ\", \"SR-AQ-KH95-01\", \"V3.1.0\", \"SR-AQ-V3.1.0\"]"

  float m_pm2 = 1.0;
  float c_pm2 = 1.0;
  float m_pm10 = 1.0;
  float c_pm10 = 1.0;

#endif

#ifdef node_6

  #define CHANNEL_ID  1591611
  #define CHANNEL_API_KEY "Z3GHUG9HGXHVYKFY"

  #define OM2M_Node_ID "SR-AQ-VN01-00"
  #define OM2M_DATA_CONT  "SR-AQ-VN01-00/Data"
  #define OM2M_DATA_LBL "[\"AE-SR-AQ\", \"SR-AQ-VN01-00\", \"V3.1.0\", \"SR-AQ-V3.1.0\"]"

  float m_pm2 = 1.0;
  float c_pm2 = 1.0;
  float m_pm10 = 1.0;
  float c_pm10 = 1.0;

  float m_db = 1.0;
  float c_db = 1.0;

#endif

unsigned long prev_time = 0;              // Time tracking variable for PM readings

// Time tracking variables
unsigned long previousMillis = 0;

// WiFi client for posting data
WiFiClient client;
HTTPClient http;

int code;

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "time.google.com");
ESP32Time rtc(0);

#define MIN_VALID_TIME 1672531200
#define MAX_VALID_TIME 2082844799

static uint64_t ntp_epoch_time = 0;

// Sound Sensor Configuration
#define SoundSensorPin 36                 // GPIO pin for sound sensor
#define VREF 5.0                          // Reference voltage for sound sensor
float voltageValue, dbValue,dbValue_cal;              // Variables to store sensor readings

// CO2 Sensor Configuration
const int CO2_PIN = 13;                   // GPIO pin for CO2 sensor
unsigned long duration, th, tl;           // Timing variables for CO2 reading
int ppm;                                  // CO2 ppm value

// AHT10 Sensor Configuration
Adafruit_AHT10 aht;                       // AHT10 sensor object
Adafruit_Sensor* aht_humidity;            // Humidity sensor object
Adafruit_Sensor* aht_temp;                // Temperature sensor object
float t;                                  // Temperature value
float h;                                  // Humidity value

// PM Sensor Configuration
int pm2 = 0;                              // Variable to store PM2.5 value
int pm10 = 0;    
float pm2_cal=0;
float pm10_cal=0;
byte command_frame[9] = {0xAA, 0x02, 0x00, 0x00, 0x00, 0x00, 0x01, 0x67, 0xBB}; // PM command frame
byte received_data[9];                    // Data received from PM sensor
int sum = 0;                              // Checksum variable

float aqiValue = 0; // Global variable to store the AQI value
