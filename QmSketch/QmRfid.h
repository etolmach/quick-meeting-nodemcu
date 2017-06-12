/**
   Driver for RFID reader MFRC522

   @project QuickMeeting
*/

#ifndef QmRfid_h
#define QmRfid_h

#include <Arduino.h>
#include <MFRC522.h>
#include "QmSerialLogger.h"

class QmRfid {
  private:
    MFRC522* mfrc522;
    QmSerialLogger logger;
  public:
    QmRfid(QmSerialLogger logger);
    void init(int ssPin, int rstPin);
    
    boolean isCard();
    String readUid();
};

#endif

