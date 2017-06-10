/**
  QuickMeeting main sketch

  @project QuickMeeting
*/

#include <SPI.h>

#include "QmConfigs.h"

#include "QmSerialLogger.h"
#include "QmBuzzer.h"
#include "QmRfid.h"
#include "QmLcdDisplay.h"
#include "QmRelay.h"
#include "QmHttpClient.cpp"

boolean isBooked = false;
String ownerUid = "";

QmSerialLogger logger;
QmBuzzer buzzer;
QmRelay relay;
QmLcdDisplay lcd;
QmHttpClient httpClient = QmHttpClient(SERVER_HOST);
QmRfid rfid;

void printHomePage() {
  lcd.print(1, FIRST_HOME_LINE);
  lcd.print(2, isBooked ? "Busy until 10:30" : "  Room is free  ");
}

void setup() {
  Serial.begin(SERIAL_BAUDRATE);
  SPI.begin();
  delay(100);

  buzzer.init(BUZZER_PIN);
  relay.init(RELAY_PIN);
  rfid.init(RFID_SS_PIN, RFID_RST_PIN);
  lcd.init(LCD_SDA_PIN, LCD_SCL_PIN, LCD_WIDTH, LCD_HEIGHT);
  //httpClient.init(WIFI_SSID, WIFI_PASS, logger);

  printHomePage();
}

void loop() {
  if (rfid.isCard()) {
    String uid = rfid.readUid();
    //int result = httpClient.attemptBook(uid, ROOM_NAME);
    if (isBooked) {
      if (ownerUid == uid) {
        logger.cancelledMeeting(uid);
        lcd.print(1, CANCELLED_MESAGE);
        buzzer.cancel();
        relay.switchOff();
        isBooked = false;
      } else {
        logger.cannotBook(uid);
        lcd.print(1, BUSY_MESSAGE);
        buzzer.error();
      }
    } else {
      ownerUid = uid;
      logger.booked(uid);
      lcd.print(1, BOOKED_MMESSAGE);
      buzzer.success();
      relay.switchOn();
      isBooked = true;
    }
    printHomePage();
  }

  delay(5000);
}
