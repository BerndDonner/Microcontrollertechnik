void setup() {
  char* b;
  uint16_t a = 0xa35c;
  Serial.begin(9600);
  Serial.println("Aufgabe 2.1:");

  Serial.print("Größe in Bytes von der Variable a: ");
  Serial.println(sizeof(a));
  Serial.print("Größe in Bytes von dem Zeiger b: ");
  Serial.println(sizeof(b));

  Serial.println("Aufgabe 2.2:");

  Serial.print("Inhalt der Adresse, auf die sich b bezieht: ");
  Serial.println(*b);

  Serial.println("Aufgabe 2.3:");

  Serial.println((uint16_t) &a, HEX);
  Serial.println((uint16_t) &b, HEX);

  Serial.println("Aufgabe 2.4:");

  b = (char *) &a;  


}

void loop() {
  // put your main code here, to run repeatedly:
}