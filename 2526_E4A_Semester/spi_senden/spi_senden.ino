#include <SPI.h>

constexpr uint8_t SS_PIN = 10;
constexpr bool BURST_MODE = true;

const uint8_t frames[] = {
  0b00000000,
  0b00000001,
  0b00000111,
  0b00011110,
  0b01111100,
  0b11111111,
  0b11110000,
  0b11000000
};

void sendSingleFrames()
{
  for (uint8_t i = 0; i < sizeof(frames); ++i)
  {
    digitalWrite(SS_PIN, LOW);
    SPI.transfer(frames[i]);
    digitalWrite(SS_PIN, HIGH);
    delay(250);
  }
}

void sendBurstFrames()
{
  digitalWrite(SS_PIN, LOW);

  for (uint8_t i = 0; i < sizeof(frames); ++i)
  {
    SPI.transfer(frames[i]);
    delay(150);
  }

  digitalWrite(SS_PIN, HIGH);
  delay(1000);
}

void setup()
{
  pinMode(SS_PIN, OUTPUT);
  digitalWrite(SS_PIN, HIGH);
  SPI.begin();
}

void loop()
{
  if (BURST_MODE)
  {
    sendBurstFrames();
  }
  else
  {
    sendSingleFrames();
  }
}
