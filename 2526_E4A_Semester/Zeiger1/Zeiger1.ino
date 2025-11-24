/*
"Datentyp, den die Funktion zurückliefert"   verdoppeln( "Variablen die wir der Funktion übergeben" ) {
  ...
  return "Wert den die Funktion zurckliefert";
}
*/
float verdoppeln(float x) {
  x = 2*x;
  return x;
}

//call bz reference
void verdoppeln2(float* x) {
  (*x) = (*x) * 2;
}


void setup() {
  Serial.begin(9600);
  int8_t a = 42;
  int8_t* b = &a;
  Serial.println(*b);
  (*b) = 3;
  Serial.println(a);

  char c = 'x';

  float f = 3.1415;

  Serial.print("Das ist das verdoppelte f: ");
  Serial.println(verdoppeln(f));
  Serial.println(f);

  Serial.print("Das ist das verdoppelte f: ");
  verdoppeln2(&f);
  Serial.println(f);
  
  Serial.print("Wieviel Bytes belegt ein char: ");
  Serial.println(sizeof(char));
  Serial.print("Wieviel Bytes belegt eine Addresse von einem char: ");
  Serial.println(sizeof(char*));
  Serial.print("Wieviel Bytes belegt eine Addresse von einem char: ");
  Serial.println(sizeof(&c));
}

void loop() {
}
