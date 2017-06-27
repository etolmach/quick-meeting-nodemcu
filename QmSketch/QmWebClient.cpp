#include "QmWebClient.h"

#ifndef MOCK_WEB_CLIENT

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

QmWebClient::QmWebClient(String host, QmLogger logger) : QmComponent(logger) {
  this->host = host;
}

/**
   Setup QmWebClient by initializyng WiFi connection
*/
void QmWebClient::init(const char* ssid, const char* password) {
  logger.debugln("Initializing webClient...");
  logger.debugParam("ssid", ssid);
  logger.debugParam("password", password);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
}

boolean QmWebClient::isConnected() {
  if (WiFi.status() == WL_CONNECTED) {
    logger.debugln("\nWiFi connection established.");
    logger.debugParam("IP address", WiFi.localIP().toString());
    logger.debugln("Done.\n");
    return true;
  }
  return false;
}

/**
    Attempts a resevation for predefined room and user UUID

   -1 ROOM_BOOKING_ERROR
   1 ROOM_BOOKING_SUCCESSFUL
   2 ROOM_BOOKING_DENIED
   3 ROOM_CANCEL_MEETING_SUCCESSFUL
   4 ROOM_CANCEL_MEETING_DENIED
*/
int QmWebClient::attemptReservation(String RFID) {
  // prepare and execute request
  logger.debugln("preparing request");
  HTTPClient http;
  http.begin(host + RFID);
  int httpCode = http.GET();
  http.end();

  // httpCode will be negative on error
  if (httpCode > 0) {
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
        return ROOM_BOOKING_ERROR;
    }
    return httpCode;
  } else {
    logger.debug("request failed with error code: ");
    logger.debugln(String(httpCode));
    http.end();

    return ROOM_BOOKING_ERROR;
  }
}

int QmWebClient::checkStatus(String roomId) {
  // prepare and execute request
  logger.debugln("preparing request");
  HTTPClient http;
  http.begin(host);
  int httpCode = http.GET();
  http.end();

  // httpCode will be negative on error
  if (httpCode > 0) {
    logger.debug("got http code: ");
    logger.debugln(String(httpCode));
    switch (httpCode) {
      case HTTP_CODE_OK:
        return ROOM_BOOKING_SUCCESSFUL;
      case HTTP_CODE_LOCKED:
        return ROOM_BOOKING_DENIED;
      default:
        return ROOM_BOOKING_ERROR;
    }

    return httpCode;
  } else {
    logger.debug("request failed with error code: ");
    logger.debugln(String(httpCode));
    http.end();

    return ROOM_BOOKING_ERROR;
  }
}

#endif
