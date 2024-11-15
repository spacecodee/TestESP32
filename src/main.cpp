#include <WiFi.h>

const char *ssid = "CABLEVISION_CLAVIJO";
const char *password = "eug9jAifit56sFey";

const int ledPin1 = 16;
const int ledPin2 = 17;

void setup() {
    Serial.begin(115200);
    delay(1000);

    // Connect to WiFi
    WiFi.begin(ssid, password);

    while (WiFiClass::status() != WL_CONNECTED) {
        delay(500);
        Serial.println("Connecting to WiFi...");
    }

    Serial.println("Connected to WiFi");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());

    // Initialize the LED pins as outputs
    pinMode(ledPin1, OUTPUT);
    pinMode(ledPin2, OUTPUT);
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