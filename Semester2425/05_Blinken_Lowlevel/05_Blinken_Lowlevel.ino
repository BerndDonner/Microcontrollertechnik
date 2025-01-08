
void setup() {
  DDRB |= (1 << PB5); // Portmanipulation: replaces pinMode(13, OUTPUT);
}

void loop() {
//  PORTB |= (1 << PB5); //digitalWrite(ledPin, HIGH);
//  PORTB &= ~(1 << PB5); //digitalWrite(ledPin, LOW);
  PORTB ^= (1 << PB5);  // toggle PB5, Pin 13 Arduino
}
