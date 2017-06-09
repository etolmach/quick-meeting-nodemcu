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

#define ROOM_NAME "CHI-REU309"
#define FIRST_HOME_LINE  "   CHI-REU309   "
#define BOOKED_MMESSAGE  " Booked 15 mins "
#define BUSY_MESSAGE     " Room is BUSY ! "
#define CANCELLED_MESAGE "  Cancelled !   "


#endif
