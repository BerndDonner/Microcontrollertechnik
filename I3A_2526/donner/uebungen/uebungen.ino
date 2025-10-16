#include "Arduino.h"

void setup() {
    Serial.begin(115200);
    int8_t i = 0xa5;
    uint8_t u = 0xa5;

    Serial.println((int8_t) i);
    Serial.println((uint8_t) u);
    Serial.println((int16_t) i, HEX);
    Serial.println((uint16_t) u, HEX);
}

void loop() {
}
