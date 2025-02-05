volatile bool eier_fertig = false;

void setup() {
  Serial.begin(9600);
  Serial.println("Jetzt geht's los!!!");


  TCCR2A = 0; //Wave Generation Mode: 0
  TCCR2B = (1<<CS20) | (1<<CS21) | (1<<CS22);               //Prescaler: 1024
  
  TIMSK2 = (1 << TOIE2);
}

ISR(TIMER2_OVF_vect) {
  static uint16_t i = 0;
  i += 1;
  if (i == 23804) eier_fertig = true;
}


void loop() {
  if (eier_fertig) {
    Serial.println("Schwing Deinen Arsch zum Herd!!!");
    eier_fertig = false;
    TCCR2B = 0;
    TIMSK2 = 0;

  }
}
