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
#include "QmWebClient.h"

QmSerialLogger logger;
QmBuzzer buzzer(logger);
QmRelay relay(logger);
QmLcdDisplay lcd(logger);
QmRfid rfid(logger);
QmWebClient webClient(SERVER_HOST, logger);

void setup() {
  Serial.begin(SERIAL_BAUDRATE);
  SPI.begin();
  delay(200);

  buzzer.init(BUZZER_PIN);
  relay.init(RELAY_PIN);
  rfid.init(RFID_SS_PIN, RFID_RST_PIN);
  lcd.init(LCD_SDA_PIN, LCD_SCL_PIN, LCD_WIDTH, LCD_HEIGHT);
  webClient.init(WIFI_SSID, WIFI_PASS);

  logger.debugln("Connecting to WiFi...");
  while (!webClient.isConnected()) {
    // TODO:
    // do something while waiting for connection
    // e.g. log something
    logger.debug(".");
    delay(200);
  }
  //  logger.debugln("done");
  buzzer.success();
}

void debugUidAction(String uid, String message) {
  logger.debug(uid);
  logger.debug(" ");
  logger.debug(message);
  logger.debugln(".");
}

int loopCounter = 0;
boolean isBooked = false;
String timeStr = "--:--"; // Nothe that the length of this variable should be equal to 5

void refreshHomePage() {
  if (loopCounter % HOME_PAGE_REFRESH_LOOPS == 0) {
    // TODO:
    // Do request to the remote server
    // And update 'isBooked' and 'timeStr' variables
    loopCounter = 0;
  } else {
    loopCounter++;
  }
  lcd.print(0, ROOM_NAME_MESSAGE);
  lcd.print(1, String(isBooked ? "Busy until " : "Free until ") + timeStr);
  //lcd.print(1, String(isBooked ? " Room is busy ! " : "  Room is free  ") + timeStr);
}

void loop() {
  refreshHomePage();
  if (rfid.isCard()) {
    String uid = rfid.readUid();
    int result = webClient.attemptReservation(uid);
    switch (result) {
      case ROOM_BOOKING_SUCCESSFUL:
        debugUidAction(uid, "booked 15 minutes");
        lcd.print(1, BOOKED_MESSAGE);
        buzzer.success();
        relay.switchOn();
        break;
      case ROOM_BOOKING_DENIED:
      case ROOM_CANCEL_MEETING_DENIED:
        debugUidAction(uid, "cannot book/cancel room");
        lcd.print(1, BUSY_MESSAGE);
        buzzer.error();
        break;
      case ROOM_CANCEL_MEETING_SUCCESSFUL:
        debugUidAction(uid, "cancelled meeting");
        lcd.print(1, CANCELLED_MESAGE);
        buzzer.cancel();
        relay.switchOff();
        break;
      case ROOM_BOOKING_NETWORK_ERROR:
      case ROOM_BOOKING_ERROR:
        logger.debugln("Network error occured");
        logger.debugParam("HTTP_CODE", result);
        lcd.print(1, NETWORK_ERROR_MESSAGE);
        buzzer.error();
        break;
    }
  }
  delay(100);
}
