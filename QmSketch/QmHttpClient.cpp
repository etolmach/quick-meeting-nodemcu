#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

#include "QmConfigs.h"
#include "QmSerialLogger.h"

#define ROOM_BOOKING_FAIED -1
#define ROOM_BOOKING_SUCCESSFUL 1
#define ROOM_BOOKING_DENIED 2
#define ROOM_CANCEL_MEETING_SUCCESSFUL 3
#define ROOM_CANCEL_MEETING_DENIED 4

class QmHttpClient {
  private:
    QmSerialLogger logger;
    String host;

  public:
    QmHttpClient(String host) {
      this->host = host;
    }

    int init(const char* ssid, const char* password, QmSerialLogger logger) {
      this->logger = logger;
      
      logger.debug("Connecting to wifi: ");
      logger.debugln(ssid);

      // explicitly set the ESP8266 to be a WiFi-client
      WiFi.mode(WIFI_STA);
      WiFi.begin(ssid, password);
      
      // connecting to a WiFi network
      while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        logger.debug(".");
      }

      logger.debugln("WiFi connected with IP adress:");
      logger.debugln(String(WiFi.localIP()));

      return 0;
    }

    int attemptBook(String roomId, String RFID) {

      // prepare and execute request
      logger.debugln("preparing request");
      HTTPClient http;
      http.begin(host + "/sbleihp5/QuickMeeting/1.0.0/quick-meeting/" + roomId + "/" + RFID);
      int httpCode = http.GET();
      http.end();

      // httpCode will be negative on error
      if(httpCode > 0) {
          logger.debug("got http code: ");
          logger.debugln(String(httpCode));
          switch (httpCode) {
            case HTTP_CODE_OK:
              return ROOM_BOOKING_SUCCESSFUL;
            case HTTP_CODE_LOCKED:
              return ROOM_BOOKING_DENIED;
            case HTTP_CODE_ACCEPTED:
              return ROOM_CANCEL_MEETING_SUCCESSFUL;
            case HTTP_CODE_FORBIDDEN:
              return ROOM_CANCEL_MEETING_DENIED;
            default:
              return ROOM_BOOKING_FAIED;
          }

          return httpCode;
      } else {
          logger.debug("request failed with error code: ");
          logger.debugln(String(httpCode));
          http.end();
          
          return ROOM_BOOKING_FAIED;
      }
    }
};

