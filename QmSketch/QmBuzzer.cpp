/**
    Driver for Buzzer
*/

#include "QmBuzzer.h"
#include "QmConfigs.h"

QmBuzzer::QmBuzzer() {}

void QmBuzzer::init(int pin) {
  this->buzzerPin = pin;
  pinMode(pin, OUTPUT);
}

void QmBuzzer::buzz(int milliseconds, int pin) {
  digitalWrite(pin, HIGH);
  delay(milliseconds);
  digitalWrite(pin, LOW);
}

void QmBuzzer::buzz(int milliseconds) {
  this->buzz(milliseconds, this->buzzerPin);
}

void QmBuzzer::success() {
  this->buzz(BUZZER_SUCCESS_LENGTH);
}

void QmBuzzer::error() {
  buzz(BUZZER_ERROR_LENGTH);
  delay(BUZZER_ERROR_DELAY);
  buzz(BUZZER_ERROR_LENGTH);
  delay(BUZZER_ERROR_DELAY);
  buzz(BUZZER_ERROR_LENGTH);
}

void QmBuzzer::cancel() {
  buzz(BUZZER_CANCEL_LENGTH);
  delay(BUZZER_CANCEL_DELAY);
  buzz(100);
}
