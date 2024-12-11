volatile bool isTaster = false;

void setup() {
  Serial.begin(9600);
  uint8_t interruptPin = 2;
  pinMode(interruptPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin), ichBinDerGroesste, FALLING);
}

void ichBinDerGroesste() {
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
