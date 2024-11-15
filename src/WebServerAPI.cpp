#include "WebServerAPI.h"
#include "LEDStateDTO.h"

WebServerAPI::WebServerAPI() : server(80) {}

String webServer;

void WebServerAPI::begin() {
    Serial.begin(115200);
    delay(1000);

    webServer = WebServerAPI::ApiName;

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
    auto handleLedRequest = [](AsyncWebServerRequest *request, uint8_t *data, size_t len, int ledPin) {
        LEDStateDTO dto;
        if (!dto.fromJson(String((char *) data))) {
            request->send(400, "application/json", R"({"error":"Invalid JSON"})");
            return;
        }

        if (dto.getState().equals("on")) {
            digitalWrite(ledPin, HIGH);
        } else if (dto.getState().equals("off")) {
            digitalWrite(ledPin, LOW);
        }
        request->send(200, "application/json", R"({"message":"LED state changed"})");
    };

    server.onRequestBody(
            [this, handleLedRequest](AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t, size_t) {
                if (request->url() == "/led1") {
                    handleLedRequest(request, data, len, ledPin1);
                } else if (request->url() == "/led2") {
                    handleLedRequest(request, data, len, ledPin2);
                }
            });

    server.on("/status", HTTP_GET, [this](AsyncWebServerRequest *request) {
        String status = "LED1: " + String(digitalRead(ledPin1) == HIGH ? "on" : "off") +
                        ", LED2: " + String(digitalRead(ledPin2) == HIGH ? "on" : "off");
        request->send(200, "application/json", R"({"status":")" + status + "\"}");
    });
}