#include <Arduino.h>

void setup()
{
    Serial.begin(115200);
    Serial.println("Hallo Welt!!!");

    int8_t wiesn = 127;
    int8_t traunsteiner = 0b01111111; // 127 dezimal
    int8_t augustiner = 0x7f; // 127 dezimal

    uint8_t gaeubodenfest = 127;
    Serial.print("wiesn: ");
    Serial.println(wiesn);
    Serial.print("traunsteiner: ");
    Serial.println(traunsteiner);
    Serial.print("augustiner: ");
    Serial.println(augustiner);
    Serial.print("gaeubodenfest: ");
    Serial.println(gaeubodenfest);
    wiesn += 1;
    gaeubodenfest += 1;
    Serial.print("wiesn nach Erhöhung um 1: ");
    Serial.println(wiesn);
    Serial.println(wiesn, BIN);    
    Serial.println(wiesn, HEX);
    Serial.print("gaeubodenfest nach Erhöhung um 1: ");
    Serial.println(gaeubodenfest);
    Serial.println(gaeubodenfest, BIN);    
    Serial.println(gaeubodenfest, HEX);    
}

void loop()
{
}
