#ifndef QmConfigs_h
#define QmConfigs_h

#include <Arduino.h>

// Serial configs
#define SERIAL_BAUDRATE 115200

// Buzzer settings
#define BUZZER_PIN D0
#define BUZZER_ERROR_LENGTH 100
#define BUZZER_ERROR_DELAY 50
#define BUZZER_SUCCESS_LENGTH 200
#define BUZZER_CANCEL_LENGTH 200
#define BUZZER_CANCEL_DELAY 40

// Relay settings
#define RELAY_PIN D1 // dummy value

// RFID settings
#define RFID_RST_PIN D3
#define RFID_SS_PIN D4

//#define RFID_RST_PIN 3
//#define RFID_SS_PIN 4

// LCD settings
#define LCD_SDA_PIN D2
#define LCD_SCL_PIN D1
#define LCD_WIDTH 16
#define LCD_HEIGHT 2

// LCD messages
// Note that the message length should be equal to LCD_WITDTH
#define ROOM_NAME_MESSAGE     "   CHI-REU306   "
#define BOOKED_MESSAGE        " Booked 15 mins "
#define BUSY_MESSAGE          " Room is BUSY ! "
#define CANCELLED_MESAGE      "  Cancelled !   "
#define NETWORK_ERROR_MESSAGE " Network error! "
#define BOOKING_ERROR_MESSAGE " Booking error! "

// WiFi settings
#define WIFI_SSID "..."
#define WIFI_PASS "..."

#define SERVER_HOST "http://10.187.5.97/api/meeting/chi_reu306/"

#define DEBUG 1

// Count of loops until home page refresh
#define HOME_PAGE_REFRESH_LOOPS 1000
#define HOME_PAGE_REFRESH_DELAY 100

// MOCKS 
#define MOCK_RFID false
#define MOCK_WEB_CLIENT true

#endif
