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
QmBuzzer buzzer;
QmRelay relay;
QmLcdDisplay lcd;
QmRfid rfid;
QmWebClient webClient = QmWebClient(SERVER_HOST, logger);

void setup() {
  Serial.begin(SERIAL_BAUDRATE);
  SPI.begin();
  delay(100);

  buzzer.init(BUZZER_PIN);
  relay.init(RELAY_PIN);
  rfid.init(RFID_SS_PIN, RFID_RST_PIN);
  lcd.init(LCD_SDA_PIN, LCD_SCL_PIN, LCD_WIDTH, LCD_HEIGHT);
  webClient.init(WIFI_SSID, WIFI_PASS);
  
  logger.debug("Connecting to WiFi");
  while (!webClient.isConnected()) {
    // TODO:
    // do something while waiting for connection
    // e.g. log something
    logger.debug(".");
    delay(200);
  }
  logger.debugln("done");
  buzzer.success();
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
}

void loop() {
  refreshHomePage();
  if (rfid.isCard()) {
    String uid = rfid.readUid();
    int result = webClient.attemptReservation("chi-reu209", uid);
    switch (result) {
      case ROOM_BOOKING_SUCCESSFUL:
        logger.booked(uid);
        lcd.print(1, BOOKED_MESSAGE);
        buzzer.success();
        relay.switchOn();
        break;
      case ROOM_BOOKING_DENIED:
        logger.cannotBook(uid);
        lcd.print(1, BUSY_MESSAGE);
        buzzer.error();
        break;
      case ROOM_CANCEL_MEETING_SUCCESSFUL:
        logger.cancelledMeeting(uid);
        lcd.print(1, CANCELLED_MESAGE);
        buzzer.cancel();
        relay.switchOff();
        break;
      case ROOM_BOOKING_NETWORK_ERROR:
      case ROOM_BOOKING_ERROR:
        // TODO:
        // Log an error message
        // lcd.print(1, NETWORK_ERROR_MESSAGE);
        buzzer.error();
        break;
    }
  }
}
