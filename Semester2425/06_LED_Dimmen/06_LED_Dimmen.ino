void setup() {
  TCCR2A |= (1<<WGM20) | (1<<WGM21); //Wave Generation Mode: 3
  TCCR2B |= (1<<CS22);               //Prescaler: 64

}

void loop() {
  // put your main code here, to run repeatedly:

}
