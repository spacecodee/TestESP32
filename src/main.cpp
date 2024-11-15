#include <WiFi.h>
#include <Preferences.h>
#include <ESPAsyncWebServer.h>

Preferences preferences;
AsyncWebServer server(80);

const int ledPin1 = 16;
const int ledPin2 = 17;

String ssid;
String password;
String ipAddress;

void setupWiFi();

void setup() {
    Serial.begin(115200);
    delay(1000);

    //Setting up the Wi-Fi
    setupWiFi();

    // Initialize the LED pins as outputs
    pinMode(ledPin1, OUTPUT);
    pinMode(ledPin2, OUTPUT);

    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(200, "text/html",
                      R"(<form action="/get" method="GET"><input type="text" name="input1"><input type="submit" value="Submit"></form>)");
    });

    server.on("/get", HTTP_GET, [](AsyncWebServerRequest *request) {
        String input1;
        if (request->hasParam("input1")) {
            input1 = request->getParam("input1")->value();
            Serial.println("Received input: " + input1);
        }
        request->send(200, "text/html", "Received input: " + input1);
    });

    server.begin();
}

void loop() {
    // Turn on the first LED
    digitalWrite(ledPin1, HIGH);
    // Turn off the second LED
    digitalWrite(ledPin2, LOW);
    delay(1000); // Wait for 1 second

    // Turn off the first LED
    digitalWrite(ledPin1, LOW);
    // Turn on the second LED
    digitalWrite(ledPin2, HIGH);
    delay(1000); // Wait for 1 second
}

void setupWiFi() {
    // Open Preferences with my-app namespace. Each application module, library, etc
    // has to use a namespace name to prevent key name collisions. We will open storage in
    // RW-mode (second parameter has to be false).
    preferences.begin("my-app", false);

    // Retrieve the SSID and password from Preferences
    ssid = preferences.getString("WIFI_SSID", "default_ssid");
    password = preferences.getString("WIFI_PASSWORD", "default_password");

    // Connect to WiFi
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