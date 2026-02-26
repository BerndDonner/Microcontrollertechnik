constexpr uint8_t pin = 8;

void setup() {
  //  pinMode(pin, OUTPUT);
  DDRB |= (1 << DDB0);
}

void loop() {
/**
 * f = 12MHz
 * T = 1/f = 62.5ns
 */

//  digitalWrite(pin, LOW); //3.3us im low-Zustand --> ca 53 Takte
//  digitalWrite(pin, HIGH);

  PORTB &= ~(1 << PORTB0); //125ns im low-Zustand --> 2 Takte
  PORTB |= (1 << PORTB0);
}