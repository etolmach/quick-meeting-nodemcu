/**
   Driver for relay

   @project QuickMeeting
*/

#ifndef QmRelay_h
#define QmRelay_h

#include <Arduino.h>
#include "QmSerialLogger.h"

class QmRelay {
  private:
    int controlPin;
    QmSerialLogger logger;
  public:
    QmRelay(QmSerialLogger logger);
    void init(int controlPin);

    void switchOn();
    void switchOff();
    boolean isSwitchedOn();
};

#endif
