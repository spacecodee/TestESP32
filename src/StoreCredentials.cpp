#include <Preferences.h>

Preferences preferences;

void setup() {
    Serial.begin(115200);
    delay(1000);

    // Open Preferences with my-app namespace
    preferences.begin("my-app", false);

    // Set the SSID and password in Preferences
    preferences.putString("WIFI_SSID", "CABLEVISION_CLAVIJO");
    preferences.putString("WIFI_PASSWORD", "eug9jAifit56sFey");

    Serial.println("SSID and Password have been set in Preferences");
}

void loop() {
    // Do nothing
}