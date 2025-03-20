const char* msg1 = "Ich säge Holz.";
const char* msg2 = "Ich säge Metall.";
const char* msg3 = "Ich säge Hand.";

char*    matrial[] = {msg1, msg1, msg2, msg1, msg2, msg2, msg3, msg1, msg2, msg3};
uint16_t dauer[] =   {1111, 500,  2700, 2222,  500, 1777, 2432,  678,  986, 1456}; 

void setup() {
  Serial.begin(9600);
  /* pinMode(2, INPUT_PULLUP); //DDRD PORTD PD2 */

  DDRD  &= ~(1 << PD2); //Bit ausschalten auch möglich DDRD = 0;
  PORTD |=  (1 << PD2); //Bit einschalten
/*  attachInterrupt(digitalPinToInterrupt(2), stopp, FALLING); //PD2 -> INT0 */
  // fallende Flanke EICRA: ISC01=1 ISC00=0
  // Interrupt ein   EIMSK: INT0=1
  
  cli();
  EICRA |=  (1 << ISC01);
  EICRA &= ~(1 << ISC00);
  EIMSK |=  (1 << INT0);
  sei();

}

/* void stopp() { */
ISR(INT0_vect) {
  Serial.println("Säge wird sofort gestoppt");
  Serial.flush();
  abort();
}

void loop() {
  for (int i = 0; i < 10; i++)
  {
    Serial.println(matrial[i]);
    delay(dauer[i]);
  }
}
