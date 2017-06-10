/**
   Serial logger

   @project QuickMeeting
*/

#ifndef QmSerialLogger_h
#define QmSerialLogger_h

#include <Arduino.h>

class QmSerialLogger {
  public:
    QmSerialLogger();
    void logAction(String uid, String message);
    void cancelledMeeting(String uid);
    void cannotBook(String uid);
    void booked(String uid);
};

#endif
