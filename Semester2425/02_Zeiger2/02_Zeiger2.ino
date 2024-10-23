template <typename F>
void print_inhalt_adresse(F& a)         //<---Referenz auf a
{
  Serial.print("Inhalt der Variable Zahl: ");
  Serial.println(a);
  Serial.print("Adresse der Variable Zahl: ");
  Serial.println((uint16_t) &a, HEX);   //<---Adresse von a
}

template <typename F>
void print_inhalt_adresse(F* a)         
{
  Serial.print("Inhalt des Zeigers: ");
  Serial.println((F) (*a));
  Serial.print("Adresse: ");
  Serial.println((uint16_t) a, HEX);
  Serial.print("Adresse der Zeigers: ");
  Serial.println((uint16_t) &a, HEX);   
}

void setup() {
  Serial.begin(9600);

  int16_t zahl0 = 42;
  int32_t zahl1 = 1024;
  int8_t* spion = (int8_t*) &zahl1;     //<---in dem Zeiger spion ist die Adresse von zahl1 gespeichert
  Serial.print("Datengroesse Spion: ");
  Serial.println(sizeof(spion));

  print_inhalt_adresse(zahl0);
  print_inhalt_adresse(zahl1);
  print_inhalt_adresse(spion);
  print_inhalt_adresse(*(spion+1));     //<---erhöhe die gespeicherte Adresse um 1 und betrachte den Inhalt dieser neuen Adresse
}

void loop() {
}
