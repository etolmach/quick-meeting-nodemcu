#include "QmLogger.h"
#include "QmConfigs.h"

QmLogger::QmLogger() {
#ifndef BEGIN_SERIAL_CONNECTION
#define BEGIN_SERIAL_CONNECTION
  Serial.begin(SERIAL_BAUDRATE);
#endif
}

void QmLogger::debug(String message) {
#ifdef DEBUG
  Serial.print(message);
#endif
}

void QmLogger::debugln(String message) {
#ifdef DEBUG
  Serial.println(message);
#endif
}

void __debugParamPrefix(String name) {
  Serial.print("   ");
  Serial.print(name);
  Serial.print(" = ");
}

void QmLogger::debugParam(String name, String value) {
#ifdef DEBUG
  __debugParamPrefix(name);
  Serial.println(value);
#endif
}

void QmLogger::debugParam(String name, int value) {
#ifdef DEBUG
  __debugParamPrefix(name);
  Serial.println(value);
#endif
}
