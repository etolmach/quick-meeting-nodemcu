#include "QmWebClient.h"
#include <ESP8266WiFi.h>

QmWebClient::QmWebClient() {}

/**
   Setup QmWebClient by initializyng WiFi connection
*/
void QmWebClient::init(const char* ssid, const char* password) {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
}

boolean QmWebClient::isConnected() {
  return WiFi.status() != WL_CONNECTED;
}

/**
   Sends a http request, returns http code or -1 in case of error
*/
int QmWebClient::httpRequest(const char* host, const int port, const char* method, String path) {
  Serial.print("Trying to connecto to ");
  Serial.println(host);

  // use WiFiClient to create TCP connection
  WiFiClient client;
  if (!client.connect(host, port)) {
    Serial.println("connection failed");
    return -1;
  }

  Serial.println(String("Sending request: ") + method + " " + host + path);

  // preparing http request
  String request =
    String("") + method + " " + path + " HTTP/1.1\r\n" +
    "Host: " + host + "\r\n" +
    "Connection: close\r\n\r\n";

  // send the request to the server
  client.print(request);

  unsigned long timeout = millis();
  while (client.available() == 0) {
    if (millis() - timeout > 5000) {
      Serial.println(">>> Client Timeout !");
      client.stop();
      return -1;
    }
  }

  String line = client.readStringUntil('\r\n');
  Serial.print("Received response headers: ");
  Serial.println(line);


  int firstSpaceAt = line.indexOf(' ');
  int secondSpaceAt = line.indexOf(' ', firstSpaceAt + 1);
  String responseCode = line.substring(firstSpaceAt + 1, secondSpaceAt);

  return responseCode.toInt();
}

/**
   Attempts a resevation for predefined room and user UUID
   Returns http code or -1 on error
*/
int QmWebClient::attemptReservation(String uid) {
  String path = String(HTTP_RESERVATION_PATH) + uid;
  return httpRequest(HTTP_HOST, HTTP_PORT, "GET", path);
}
