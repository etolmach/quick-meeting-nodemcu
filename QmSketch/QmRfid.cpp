#include "QmRfid.h"

QmRfid::QmRfid() {}

void QmRfid::init(int ssPin, int rstPin) {
  mfrc522 = new MFRC522(ssPin, rstPin);
  mfrc522->PCD_Init();
}

boolean QmRfid::isCard() {
  return mfrc522->PICC_IsNewCardPresent() && mfrc522->PICC_ReadCardSerial();
}

String QmRfid::readUid() {
  String uid = "";
  for (byte i = 0; i < mfrc522->uid.size; i++) {
    if (mfrc522->uid.uidByte[i] < 0x10) {
      uid.concat("0");
    }
    uid.concat(String(mfrc522->uid.uidByte[i], HEX));
  }
  uid.toUpperCase();
  return uid;
}

