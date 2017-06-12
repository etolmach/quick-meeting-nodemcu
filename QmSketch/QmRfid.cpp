#include "QmRfid.h"

QmRfid::QmRfid(QmSerialLogger logger) {
  this->logger = logger;
}

void QmRfid::init(int ssPin, int rstPin) {
  logger.debugln("Initializing RFID reader...");
  logger.debugParam("ssPin", ssPin);
  logger.debugParam("rstPin", rstPin);

  mfrc522 = new MFRC522(ssPin, rstPin);
  mfrc522->PCD_Init();

  logger.debugln("Done.\n");
}

boolean QmRfid::isCard() {
  if(mfrc522->PICC_IsNewCardPresent() && mfrc522->PICC_ReadCardSerial()){
    logger.debugln("\nRFID reader detected a card:");
    logger.debugParam("UUID", readUid());
    return true;
  }
  return false;
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

