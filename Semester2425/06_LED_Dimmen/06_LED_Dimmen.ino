void setup() {
  TCCR2A = (1<<WGM20) | (1<<WGM21) | (1 << COM2A1) | (1 << COM2A0); //Wave Generation Mode: 3, Set Pin11 on compare match, clear Pin 11 at 0
  TCCR2B = (1<<CS22);               //Prescaler: 64
  
  OCR2A = 0;

  DDRB |= (1 << PB3);

}

void loop() {
  // put your main code here, to run repeatedly:

}
