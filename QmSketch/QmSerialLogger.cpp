#include "QmSerialLogger.h"
#include "QmConfigs.h"

QmSerialLogger::QmSerialLogger() {}


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

void QmSerialLogger::debugParamPrefix(String name) {
  Serial.print("   ");
  Serial.print(name);
  Serial.print(" = ");
}

void QmSerialLogger::debugParam(String name, String value) {
#ifdef DEBUG
  debugParamPrefix(name);
  Serial.println(value);
#endif
}

void QmSerialLogger::debugParam(String name, int value) {
#ifdef DEBUG
  debugParamPrefix(name);
  Serial.println(value);
#endif
}
