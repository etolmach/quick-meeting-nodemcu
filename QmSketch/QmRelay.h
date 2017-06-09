/**
   Driver for relay

   @project QuickMeeting
*/

#ifndef QmRelay_h
#define QmRelay_h

#include <Arduino.h>

class QmRelay {
  private:
    int controlPin;
  public:
    QmRelay();
    void init(int controlPin);

    void switchOn();
    void switchOff();
    boolean isSwitchedOn();
};

#endif
