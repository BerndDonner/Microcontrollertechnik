void print_inhalt_adresse(int8_t* a) //a ist eine Adresse(Zeiger, Referenzen)
{
  Serial.print("Inhalt der Variable Zahl: ");
  Serial.println(*a);
  Serial.print("Adresse der Variable Zahl: ");
  Serial.println((uint16_t) a, HEX);
}

void print_inhalt_adresse(int16_t& a)
{
  Serial.print("Inhalt der Variable Zahl: ");
  Serial.println(a);
  Serial.print("Adresse der Variable Zahl: ");
  Serial.println((uint16_t) &a, HEX);
}

void print_inhalt_adresse(int32_t& a)
{
  Serial.print("Inhalt der Variable Zahl: ");
  Serial.println(a);
  Serial.print("Adresse der Variable Zahl: ");
  Serial.println((uint16_t) &a, HEX);
}

void setup() {
  Serial.begin(9600);

  int16_t zahl0 = 42;
  int32_t zahl1 = 1024;
  int8_t* spion = (int8_t*) &zahl1;
  Serial.print("Datengroesse Spion: ");
  Serial.println(sizeof(spion));

  print_inhalt_adresse(zahl0);
  print_inhalt_adresse(zahl1);
  print_inhalt_adresse(spion+1);
}

void loop() {
}
