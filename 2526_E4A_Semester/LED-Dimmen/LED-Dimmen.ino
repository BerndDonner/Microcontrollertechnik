void setup() {
  DDRD |= (1 << PD3); // PD3 = OC2B als Ausgang

  // Timer2: Fast PWM, TOP = 255, inverting mode
  TCCR2A = (1 << WGM20) | (1 << WGM21) | (1 << COM2B1) | (1 << COM2B0);
  TCCR2B = (1 << CS22) | (1 << CS21); // Prescaler 256

  OCR2B = 128; // je nach Verdrahtung sehr dunkel / aus
}

void loop() {
}
