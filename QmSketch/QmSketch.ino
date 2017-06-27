/**
  QuickMeeting main sketch
  @project QuickMeeting
*/

#include <SPI.h>

#include "QmConfigs.h"

#include "QmLogger.h"
#include "QmBuzzer.h"
#include "QmRfid.h"
#include "QmLcdDisplay.h"
#include "QmRelay.h"
#include "QmWebClient.h"

QmLogger logger;
QmBuzzer buzzer(logger);
QmRelay relay(logger);
QmLcdDisplay lcd(logger);
QmRfid rfid(logger);
QmWebClient webClient(SERVER_HOST, logger);

void setup() {
  SPI.begin();
  delay(200);

  webClient.init(WIFI_SSID, WIFI_PASS);
  logger.debugln("Connecting to WiFi...");
  while (!webClient.isConnected()) {
    // TODO:
    // do something while waiting for connection
    // e.g. log something
    logger.debug(".");
    delay(200);
  }


  ESP.wdtDisable();

  rfid.init(RFID_SS_PIN, RFID_RST_PIN);

  //lcd.init(LCD_SDA_PIN, LCD_SCL_PIN, LCD_WIDTH, LCD_HEIGHT);

  buzzer.init(BUZZER_PIN);
  relay.init(RELAY_PIN);

  logger.debugln("Initialization completed.");
  buzzer.success();
  ESP.wdtEnable(WDTO_8S);
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
  //  logger.debugln("Refresh home page.");
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
  //  refreshHomePage();
  if (rfid.isCard()) {
    String uid = rfid.readUid();
    int result = webClient.attemptReservation(uid);
    logger.debugln("Received result code:");
    logger.debugParam("HTTP_CODE", result);
    switch (result) {
      case ROOM_BOOKING_SUCCESSFUL:
        debugUidAction(uid, "booked 15 minutes");
        lcd.print(1, BOOKED_MESSAGE);
        buzzer.success();
        relay.switchOn();
        isBooked = true;
        break;
      case ROOM_BOOKING_DENIED:
      case ROOM_CANCEL_MEETING_DENIED:
        debugUidAction(uid, "cannot book/cancel room");
        lcd.print(1, BUSY_MESSAGE);
        buzzer.error();
        break;
      case ROOM_CANCEL_MEETING_SUCCESSFUL:
        debugUidAction(uid, "cancelled meeting");
        //lcd.print(1, CANCELLED_MESAGE);
        buzzer.cancel();
        relay.switchOff();
        isBooked = false;
        break;
      case ROOM_BOOKING_NETWORK_ERROR:
        logger.debugln("Network error occured!");
        lcd.print(1, NETWORK_ERROR_MESSAGE);
        buzzer.error();
        break;
      case ROOM_BOOKING_ERROR:
        logger.debugln("Booking error occured!");
        lcd.print(1, BOOKING_ERROR_MESSAGE);
        buzzer.error();
        break;
      default:
        logger.debugln("Unexpected result code!");
        lcd.print(1, BOOKING_ERROR_MESSAGE);
        buzzer.error();
    }
  }
  delay(100);
}
