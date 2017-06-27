/**
   Driver for RFID reader MFRC522

   @project QuickMeeting
*/

#ifndef QmRfid_h
#define QmRfid_h

#include <Arduino.h>
#include <MFRC522.h>
#include "QmLogger.h"
#include "QmComponent.h"

class QmRfid : QmComponent {
  private:
    MFRC522* mfrc522;
  public:
    QmRfid(QmLogger logger);
    void init(int ssPin, int rstPin);
    
    boolean isCard();
    String readUid();
};

#endif

