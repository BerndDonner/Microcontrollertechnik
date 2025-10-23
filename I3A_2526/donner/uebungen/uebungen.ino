#include "Arduino.h"

void toHex()
{
    char hexa[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};

    int16_t zahl = 0b0110110000001101;
    uint16_t uz = (uint16_t)zahl;

    for (uint8_t i = 0; i < 4; ++i)
    {
        // 12 high bit Null setzten:
        uint8_t j = uz & 0b0000000000001111; // 0x000f
        Serial.print(hexa[j]);
        uz >>= 4;
    }
}

void promotion()
{
    int8_t i = 0xa5;                  // 0b1010'0101  → entspricht -91 im Zweierkomplement
    uint8_t u = 0xa5;                 // 0b1010'0101  → entspricht 165 als unsigned
    Serial.println((int16_t)i, HEX);  // ergibt 0xFFA5 (wegen Vorzeichenerweiterung)
    Serial.println((uint16_t)u, HEX); // ergibt 0x00A5 (wegen Nullenauffüllung)
}

void setup()
{
    Serial.begin(115200);

    toHex();
}

void loop()
{
}
