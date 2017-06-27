#include "QmWebClient.h"

#ifdef MOCK_WEB_CLIENT

QmWebClient::QmWebClient(String host, QmLogger logger) : QmComponent(logger) {
  this->host = host;
}

/**
   Setup QmWebClient by initializyng WiFi connection
*/
void QmWebClient::init(const char* ssid, const char* password) {
  logger.debugln("Initializing webClient mock...");
  logger.debugParam("ssid", ssid);
  logger.debugParam("password", password);
}

boolean QmWebClient::isConnected() {
  logger.debugln("\nMock WiFi connection established.");
  logger.debugParam("IP address", "undefined");
  logger.debugln("Done.\n");
  return true;
}

int QmWebClient::attemptReservation(String RFID) {
  logger.debugln("\nAttempting mock reservation...");
  logger.debug("Enter result: ");
  while(Serial.available() == 0){};
  int result = Serial.parseInt();
  Serial.println(result);
  return result;
}

int QmWebClient::checkStatus(String roomId) {
  
}

#endif
