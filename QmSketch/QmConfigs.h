#ifndef QmConfigs_h
#define QmConfigs_h

#include <Arduino.h>

// Serial configs
#define SERIAL_BAUDRATE 9600

// Buzzer settings
#define BUZZER_PIN D0
#define BUZZER_ERROR_LENGTH 100
#define BUZZER_ERROR_DELAY 50
#define BUZZER_SUCCESS_LENGTH 200
#define BUZZER_CANCEL_LENGTH 200
#define BUZZER_CANCEL_DELAY 40

// Relay settings
#define RELAY_PIN 255 // dummy value

// RFID settings
#define RFID_RST_PIN D1
#define RFID_SS_PIN D2

//#define RFID_RST_PIN 3
//#define RFID_SS_PIN 4

// LCD settings
#define LCD_SDA_PIN D4
#define LCD_SCL_PIN D3
#define LCD_WIDTH 16
#define LCD_HEIGHT 2

// WiFi settings
#define WIFI_SSID "foo-bar-ssid"
#define WIFI_PASSWORD "foo-bar-paswd"

#define HTTP_HOST "virtserver.swaggerhub.com"
#define HTTP_PORT 80
#define HTTP_RESERVATION_PATH "/sbleihp5/QuickMeeting/1.0.0/quick-meeting/CHI-REU309/"

const int HTTP_RESERVATION_SUCCESSFUL = 200;
const int HTTP_RESEVATION_CANCELLED = 400;
const int HTTP_RESEVATION_DENIED = 423;
const int HTTP_ERROR = 500;
const int HTTP_NETWORK_ERROR = -1;

// LCD messages
// Note that the message length should be equal to LCD_WITDTH
#define ROOM_NAME_MESSAGE     "   CHI-REU309   "
#define BOOKED_MMESSAGE       " Booked 15 mins "
#define BUSY_MESSAGE          " Room is BUSY ! "
#define CANCELLED_MESAGE      "  Cancelled !   "
#define NETWORK_ERROR_MESSAGE " Network error! "

#define ROOM_NAME "CHI-REU309"

// Count of loops until home page refresh
#define HOME_PAGE_REFRESH_LOOPS 1000
#define HOME_PAGE_REFRESH_DELAY 100

#endif
