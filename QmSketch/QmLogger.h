/**
   Logger

   @project QuickMeeting
*/

#ifndef QmLogger_h
#define QmLogger_h

#include <Arduino.h>

class QmLogger {
  public:
    QmLogger();
    void debug(String message);
    void debugln(String message);
    void debugParam(String name, String value);
    void debugParam(String name, int value);
};

#endif

