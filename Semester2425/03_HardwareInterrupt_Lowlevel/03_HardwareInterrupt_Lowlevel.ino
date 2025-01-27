volatile bool isTaster = false;

void setup() {
  Serial.begin(9600);
  uint8_t interruptPin = 2;
  pinMode(interruptPin, INPUT_PULLUP);
  cli();
  EICRA |=  (1<<ISC01);
  EICRA &= ~(1<<ISC00);
  EIMSK |=  (1<< INT0);
  sei();
  //attachInterrupt(digitalPinToInterrupt(interruptPin), ichBinDerGroesste, FALLING);
}

//void ichBinDerGroesste() {
ISR(INT0_vect) {
  isTaster = true;
}

void loop() {
  static int32_t i = 0;

  if (isTaster) {  //if (isTaster == true) {}
    Serial.println("Du bist wirklich toll!!!");
    isTaster = false;
  }

  Serial.print("Schwere Arbeit: ");
  Serial.println(i);
  i++;
}

/*
EICRA |=  (1<<ISC01);

#define EICRA _SFR_MEM8(0x69)
#define _SFR_IO8(io_addr) (*(volatile uint8_t *)(0x20 + (io_addr)))

(*(volatile uint8_t *)(0x89)) |= (1<<ISC01);
*/