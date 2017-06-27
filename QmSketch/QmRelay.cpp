#include "QmRelay.h"

QmRelay::QmRelay(QmLogger logger) : QmComponent(logger) {
}

void QmRelay::init(int pin) {
  logger.debugln("Initializing relay...");
  logger.debugParam("pin", pin);
  
  this->controlPin = pin;
  pinMode(pin, OUTPUT);

  logger.debugln("Done.\n");
}

void QmRelay::switchOn() {
  digitalWrite(controlPin, HIGH);
}

void QmRelay::switchOff() {
  digitalWrite(controlPin, LOW);
}

boolean QmRelay::isSwitchedOn() {
  return digitalRead(controlPin);
}

