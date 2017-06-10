/**
   Driver for Buzzer

   @project QuickMeeting
*/

#ifndef QmBuzzer_h
#define QmBuzzer_h

#include <Arduino.h>
#include "QmConfigs.h"

class QmBuzzer {
  private:
    int buzzerPin;
  public:
    QmBuzzer();
    void init(int buzzerPin);

    void buzz(int milliseconds, int buzzerPin);
    void buzz(int milliseconds);

    void success();
    void error();
    void cancel();
    void longBuzz();
};

#endif
