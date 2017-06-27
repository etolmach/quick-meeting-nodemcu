/**
   Driver for Buzzer

   @project QuickMeeting
*/

#ifndef QmBuzzer_h
#define QmBuzzer_h

#include <Arduino.h>
#include "QmLogger.h"
#include "QmComponent.h"

class QmBuzzer : QmComponent {
  private:
    int buzzerPin;
  public:
    QmBuzzer(QmLogger logger);
    void init(int buzzerPin);

    void buzz(int milliseconds, int buzzerPin);
    void buzz(int milliseconds);

    void success();
    void error();
    void cancel();
};

#endif
