void setup() {
  char* b;
  uint16_t a = 0x235a;
  char c[] = "Chantal";

  Serial.begin(9600);
  Serial.println("Aufgabe 3.1:");
  Serial.println(c);
  Serial.println("Aufgabe 3.2:");
  // Jeder Buchstabe ein Byte und '\0' als Terminierung noch ein
  // zusätzliches Byte
  Serial.println(sizeof(c));
  Serial.println("Aufgabe 3.3:");
  Serial.println(c[4]);
  Serial.println("Aufgabe 3.4:");
  Serial.println((uint16_t) &a, HEX);
  Serial.println((uint16_t) &b, HEX);
  Serial.println((uint16_t) &c, HEX);
  Serial.println((uint16_t) &c[0], HEX);
  Serial.println("Aufgabe 3.5:");
  Serial.println((uint16_t) &c[4], HEX);
  Serial.println((uint16_t) &c+4, HEX);
/*
  int8_t benno = -17; 
  Serial.println(benno);
//  Serial.println(benno, HEX); //Problem
  Serial.println((uint8_t) benno, HEX);
*/  



 
}

void loop() {
  // put your main code here, to run repeatedly:

}
