/**
   Serial logger

   @project QuickMeeting
*/

#ifndef QmSerialLogger_h
#define QmSerialLogger_h

#include <Arduino.h>

class QmSerialLogger {
  private:
    void debugParamPrefix(String name);
  public:
    QmSerialLogger();
    void debug(String message);
    void debugln(String message);
    void debugParam(String name, String value);
    void debugParam(String name, int value);
};

#endif

