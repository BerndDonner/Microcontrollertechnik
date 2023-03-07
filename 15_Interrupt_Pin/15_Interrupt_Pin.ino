const uint8_t ledPin = 13;
const uint8_t interruptPin = 2;
volatile bool state = true;  //volatile ist wichtig, das die Variable in der ISR geändert wird.


/** Das ist die ISR */
void blink()
{
  state = digitalRead(interruptPin);
}

void setup()
{
  pinMode(ledPin, OUTPUT);
  pinMode(interruptPin, INPUT_PULLUP); //INPUT_PULLUP heißt: mit einem internen 10kOhm Wiedersstand mit 5V verbunden. D.h im unbeschaltenten Zustand: HIGH
  attachInterrupt(digitalPinToInterrupt(interruptPin), blink, CHANGE); //Hier wird die ISR installiert
}

void loop()
{
  digitalWrite(ledPin, state);
}

