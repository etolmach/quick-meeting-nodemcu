/**
   WiFi web client

   @project QuickMeeting
*/

#ifndef QmWebClient_h
#define QmWebClient_h

#include <Arduino.h>
#include "QmConfigs.h"
#include "QmSerialLogger.h"

#define ROOM_BOOKING_NETWORK_ERROR -2
#define ROOM_BOOKING_ERROR -1
#define ROOM_BOOKING_SUCCESSFUL 1
#define ROOM_BOOKING_DENIED 2
#define ROOM_CANCEL_MEETING_SUCCESSFUL 3
#define ROOM_CANCEL_MEETING_DENIED 4

class QmWebClient {
  private:
    String host;
    QmSerialLogger logger;
  public:
    QmWebClient(String host,  QmSerialLogger logger);
    void init(const char* ssid, const char* password);

    boolean isConnected();
    int attemptReservation(String uid);
    int checkStatus(String roomId);
};

#endif
