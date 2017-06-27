/**
   WiFi web client

   @project QuickMeeting
*/

#ifndef QmWebClient_h
#define QmWebClient_h

#include <Arduino.h>
#include "QmConfigs.h"
#include "QmLogger.h"
#include "QmComponent.h"

const int ROOM_BOOKING_NETWORK_ERROR = -2;
const int ROOM_BOOKING_ERROR = -1;
const int ROOM_BOOKING_SUCCESSFUL = 1;
const int ROOM_BOOKING_DENIED = 2;
const int ROOM_CANCEL_MEETING_SUCCESSFUL = 3;
const int ROOM_CANCEL_MEETING_DENIED = 4;

class QmWebClient : QmComponent{
  private:
    String host;
  public:
    QmWebClient(String host, QmLogger logger);
    void init(const char* ssid, const char* password);

    boolean isConnected();
    int attemptReservation(String uid);
    int checkStatus(String roomId);
};

#endif
