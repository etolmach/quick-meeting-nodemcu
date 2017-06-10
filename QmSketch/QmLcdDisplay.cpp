#include "QmLcdDisplay.h"

#include <LiquidCrystal_I2C.h>
#include <Wire.h>

#define DEFAULT_OFFSET 0

LiquidCrystal_I2C __lcd(0x27, 16, 2);

QmLcdDisplay::QmLcdDisplay() {}

void QmLcdDisplay::init(int sdaPin, int sclPin, int width, int height) {
  Wire.begin(sdaPin, sclPin);
  __lcd = LiquidCrystal_I2C(0x27, width, height);
  __lcd.begin(width, height);
  __lcd.backlight();
}

void QmLcdDisplay::clear() {
  __lcd.clear();
}

void QmLcdDisplay::print(int line, int offset, String message) {
  __lcd.setCursor(offset, line);
  __lcd.print(message);
}

void QmLcdDisplay::print(int line, String message) {
  __lcd.setCursor(DEFAULT_OFFSET, line);
  __lcd.print(message);
}

void QmLcdDisplay::print(String message1, int offset1, String message2, int offset2) {
  this->print(0, offset1,  message1);
  this->print(1, offset2, message2);
}

void QmLcdDisplay::print(String message1, String message2) {
  this->print(message1, DEFAULT_OFFSET, message2, DEFAULT_OFFSET);
}

