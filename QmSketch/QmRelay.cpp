#include "QmRelay.h"

QmRelay::QmRelay(QmSerialLogger logger) {
  this->logger = logger;
}

void QmRelay::init(int pin) {
  controlPin = pin;
  pinMode(pin, OUTPUT);
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

