/**
   Driver for relay

   @project QuickMeeting
*/

#ifndef QmRelay_h
#define QmRelay_h

#include <Arduino.h>
#include "QmLogger.h"
#include "QmComponent.h"

class QmRelay : QmComponent {
  private:
    int controlPin;
  public:
    QmRelay(QmLogger logger);
    void init(int controlPin);

    void switchOn();
    void switchOff();
    boolean isSwitchedOn();
};

#endif
