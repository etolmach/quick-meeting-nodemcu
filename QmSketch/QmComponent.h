/**
   Driver for Buzzer

   @project QuickMeeting
*/

#ifndef QmComponent_h
#define QmComponent_h

#include "QmLogger.h"

class QmComponent {
  protected:
    QmLogger logger;
  public:
    QmComponent(QmLogger logger){
      this->logger = logger;
    }
};

#endif
