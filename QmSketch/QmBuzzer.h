/**
   Driver for Buzzer

   @project QuickMeeting
*/

#ifndef QmBuzzer_h
#define QmBuzzer_h

#include <Arduino.h>
#include "QmSerialLogger.h"

class QmBuzzer {
  private:
    int buzzerPin;
    QmSerialLogger logger;
  public:
    QmBuzzer(QmSerialLogger logger);
    void init(int buzzerPin);

    void buzz(int milliseconds, int buzzerPin);
    void buzz(int milliseconds);

    void success();
    void error();
    void cancel();
};

#endif
