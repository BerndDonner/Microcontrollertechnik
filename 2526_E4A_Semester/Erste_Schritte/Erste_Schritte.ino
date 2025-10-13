// int8_t wiesn;  Dies ist eine global definierte Variable. Vermeiden wenn möglich!

//~a Einserkomplement
//-a Zweierkomplement -a = (~a+1)
// a & b  and [logisches und: &&]
// a | b  or  [logisches oder: ||]
// a ^ b  xor

void setup() {
  Serial.begin(9600);
  Serial.println("Hallo E3A");
  
  int8_t benno = 20; //in8_t -128.127!!!
  Serial.println(benno);  //negative Zahl
  Serial.println((uint8_t) benno);

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
