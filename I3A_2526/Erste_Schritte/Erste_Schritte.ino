#include <Arduino.h>

void setup()
{
    Serial.begin(115200);
    Serial.println("Hallo Welt!!!");

    int8_t wiesn = 0xff;
    int8_t traunsteiner = 0b01111111; // 127 dezimal
    int8_t augustiner = 0x7f; // 127 dezimal

    uint8_t gaeubodenfest = 0xab;
    uint8_t paulaner = ~gaeubodenfest+1; //Zweierkomplement

    Serial.println("Zweierkomplement: ");
    Serial.println(gaeubodenfest, BIN);
    Serial.println(paulaner, BIN);
    Serial.println((uint8_t) -gaeubodenfest, BIN);

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
