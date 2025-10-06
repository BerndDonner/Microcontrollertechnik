// int8_t wiesn;  Dies ist eine global definierte Variable. Vermeiden wenn möglich!


void setup() {
  Serial.begin(9600);
  Serial.println("Hallo E3A");
  for (int8_t wiesn = 123; (uint8_t) wiesn <= 133; ++wiesn) {  //Deklaration und Initialisierung von wiesn
    Serial.print(wiesn);
    Serial.print("\t");
    Serial.print((uint8_t) wiesn, BIN);
    Serial.print("\t");
    Serial.println((uint8_t) ~wiesn, BIN); //Einserkomplement
  }
}

void loop() {
}
