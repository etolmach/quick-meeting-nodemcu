#include "QmSerialLogger.h"
#include "QmConfigs.h"

QmSerialLogger::QmSerialLogger() {}

void QmSerialLogger::logAction(String uid, String message) {
  Serial.print(uid);
  Serial.print(" ");
  Serial.println(message);
}

void QmSerialLogger::debug(String message) {
  #ifdef DEBUG
  Serial.print(message);
  #endif
}

void QmSerialLogger::debugln(String message) {
  #ifdef DEBUG
  Serial.println(message);
  #endif
}

void QmSerialLogger::cancelledMeeting(String uid) {
  QmSerialLogger::logAction(uid, "cancelled meeting.");
}

void QmSerialLogger::cannotBook(String uid) {
  QmSerialLogger::logAction(uid, "cannot book already booked room!");
}

void QmSerialLogger::booked(String uid) {
  QmSerialLogger::logAction(uid, "booked 15 minutes.");
}
