#ifndef TESTESP32_WEBSERVERAPI_H
#define TESTESP32_WEBSERVERAPI_H

#include <WiFi.h>
#include <Preferences.h>
#include <ESPAsyncWebServer.h>

class WebServerAPI {
public:
    WebServerAPI();

    void begin();

    void setupWiFi();

private:
    Preferences preferences;
    AsyncWebServer server;
    const int ledPin1 = 16;
    const int ledPin2 = 17;
    String ssid;
    String password;
    String ipAddress;
    String ApiName = "/api/v1";

    void setupEndpoints();
};


#endif //TESTESP32_WEBSERVERAPI_H
