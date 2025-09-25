#include <Arduino.h>

void setup()
{
    Serial.begin(115200);
    Serial.println("Hallo Welt!!!");

    int8_t wiesn = 127;
    Serial.println(wiesn);
    wiesn += 1;
    Serial.println(wiesn);    
}

void loop()
{
}
