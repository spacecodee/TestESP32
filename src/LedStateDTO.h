#ifndef TESTESP32_LEDSTATEDTO_H
#define TESTESP32_LEDSTATEDTO_H

#include <ArduinoJson.h>

class LEDStateDTO {
public:
    LEDStateDTO() = default;

    bool fromJson(const String &jsonString);

    String toJson() const;

    String getState() const;

    void setState(const String &nState);

private:
    String state;

};


#endif //TESTESP32_LEDSTATEDTO_H