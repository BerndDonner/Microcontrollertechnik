void mul_16(uint16_t* c) {
  (*c) = (*c) * 16;
}


void setup() {
  char* b;
  uint16_t a = 0x235a;
  char s[] = "E3A";

  Serial.begin(9600);
  Serial.println(F("Aufgabe 2.1:"));

  Serial.print("Größe in Bytes von der Variable a: ");
  Serial.println(sizeof(a));
  Serial.print("Größe in Bytes von dem Zeiger b: ");
  Serial.println(sizeof(b));
  Serial.print("Größe in Bytes von dem String s: ");
  Serial.println(sizeof(s));

/*
  Serial.println(s);
  s[3] = '\0';
  Serial.println(s);
  s[3] = 'B';
  Serial.println(s);
*/

  Serial.println("Aufgabe 2.2:");

  Serial.print("Inhalt der Adresse, auf die sich b bezieht: ");
  Serial.println(*b);

  Serial.println("Aufgabe 2.3:");

  Serial.println((uint16_t) &a, HEX);
  Serial.println((uint16_t) &b, HEX);
  Serial.println((uint16_t) &s, HEX);

  Serial.println("Aufgabe 2.4:");

  b = (char *) &a;
  Serial.println(*b);  

  Serial.println("Aufgabe 2.5:");

  Serial.println(*(b+1));  

  Serial.println("Aufgabe 2.6:");

  Serial.println(a);  
  mul_16(&a);
  Serial.println(a);  

}

void loop() {
  // put your main code here, to run repeatedly:
}