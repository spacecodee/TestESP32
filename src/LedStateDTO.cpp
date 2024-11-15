#include "LEDStateDTO.h"

bool LEDStateDTO::fromJson(const String &jsonString) {
    JsonDocument doc;
    DeserializationError error = deserializeJson(doc, jsonString);
    if (error) {
        return false;
    }
    state = doc["state"].as<String>();
    return true;
}

String LEDStateDTO::toJson() const {
    JsonDocument doc;
    doc["state"] = state;
    String jsonString;
    serializeJson(doc, jsonString);
    return jsonString;
}

String LEDStateDTO::getState() const {
    return state;
}

void LEDStateDTO::setState(const String &nState) {
    LEDStateDTO::state = nState;
}