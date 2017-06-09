/**
   Driver for LCD display

   @project QuickMeeting
*/

#ifndef QmLcdDisplay_h
#define QmLcdDisplay_h

#include <Arduino.h>

class QmLcdDisplay {
  public:
    QmLcdDisplay();
    void init(int sdaPin, int sclPin, int width, int height);

    void clear();
    void print(int line, int offset, String message);
    void print(int line, String message);
    void print(String message1, int offset1, String message2, int offset2);
    void print(String message1, String message2);
};

#endif
