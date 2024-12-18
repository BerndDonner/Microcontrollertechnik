volatile bool isTaster = false;
volatile unsigned long recent_key = 0; 
const unsigned long dead_time = 10;  //10ms 

void setup() {
  Serial.begin(9600);
  uint8_t interruptPin = 2;
  pinMode(interruptPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin), ichBinDerGroesste, FALLING);
}

void ichBinDerGroesste() {
  if (isTaster == false) {
    isTaster = true;
    recent_key = millis();
  }
}

void loop() {
  static int32_t i = 0;

  if ((isTaster) && (recent_key + dead_time < millis())) {  //if (isTaster == true) {}
    Serial.println("Du bist wirklich toll!!!");
    isTaster = false;
  }
  
  Serial.print("Schwere Arbeit: ");
  Serial.println(i);
  i++;
}
