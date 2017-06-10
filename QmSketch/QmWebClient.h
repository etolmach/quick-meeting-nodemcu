/**
   WiFi web client

   @project QuickMeeting
*/

#ifndef QmWebClient_h
#define QmWebClient_h

#include <Arduino.h>
#include "QmConfigs.h"


class QmWebClient {
  public:
    QmWebClient();
    void init(const char* ssid, const char* password);

    boolean isConnected();
    int httpRequest(const char* host, const int port, const char* method, String path);
    int attemptReservation(String uid);
};

#endif
