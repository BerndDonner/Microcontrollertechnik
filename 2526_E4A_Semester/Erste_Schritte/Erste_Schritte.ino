// int8_t wiesn;  Dies ist eine global definierte Variable. Vermeiden wenn möglich!


void setup() {
  int8_t wiesn;  //Deklaration von wiesn
  Serial.begin(9600);
  Serial.println("Hallo E3A");
  Serial.println(wiesn);
}

void loop() {
}
