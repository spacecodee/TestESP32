#include "WebServerAPI.h"

WebServerAPI::WebServerAPI() : server(80) {}

void WebServerAPI::begin() {
    Serial.begin(115200);
    delay(1000);

    // Setting up the Wi-Fi
    setupWiFi();

    // Initialize the LED pins as outputs
    pinMode(ledPin1, OUTPUT);
    pinMode(ledPin2, OUTPUT);

    // Set-up the endpoints
    setupEndpoints();

    // Start the server
    server.begin();
}

void WebServerAPI::setupWiFi() {
    preferences.begin("my-app", false);

    ssid = preferences.getString("WIFI_SSID", "default_ssid");
    password = preferences.getString("WIFI_PASSWORD", "default_password");

    WiFi.begin(ssid.c_str(), password.c_str());

    while (WiFiClass::status() != WL_CONNECTED) {
        delay(500);
        Serial.println("Connecting to WiFi...");
    }
    ipAddress = WiFi.localIP().toString();

    Serial.println("Connected to WiFi");
    Serial.print("IP Address: ");
    Serial.println(ipAddress);
}

void WebServerAPI::setupEndpoints() {
    server.on("/led1", HTTP_POST, [this](AsyncWebServerRequest *request) {
        if (request->hasParam("state", true)) {
            String state = request->getParam("state", true)->value();
            if (state == "on") {
                digitalWrite(ledPin1, HIGH);
            } else if (state == "off") {
                digitalWrite(ledPin1, LOW);
            }
            request->send(200, "text/plain", "LED1 state changed");
        } else {
            request->send(400, "text/plain", "Bad Request");
        }
    });

    server.on("/led2", HTTP_POST, [this](AsyncWebServerRequest *request) {
        if (request->hasParam("state", true)) {
            String state = request->getParam("state", true)->value();
            if (state == "on") {
                digitalWrite(ledPin2, HIGH);
            } else if (state == "off") {
                digitalWrite(ledPin2, LOW);
            }
            request->send(200, "text/plain", "LED2 state changed");
        } else {
            request->send(400, "text/plain", "Bad Request");
        }
    });

    server.on("/status", HTTP_GET, [this](AsyncWebServerRequest *request) {
        String status = "LED1: " + String(digitalRead(ledPin1) == HIGH ? "on" : "off") +
                        ", LED2: " + String(digitalRead(ledPin2) == HIGH ? "on" : "off");
        request->send(200, "application/json", R"({"status": ")" + status + "\"}");
    });
}