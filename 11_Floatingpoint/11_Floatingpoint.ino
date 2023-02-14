/*
Es gibt unter der arduino-Oberfläche keinen echten Datntyp double.
Auf dem Arduino ist "sizeof(float) = sizeof(double) = 4"
Vergleichen Sie floating point niemals direkt: a == 0.5             (falsch)
sondern immer                                  abs(a-0.5) < epsilon (richtig)
exponenten mit nur 0 sind 
               nur 1

*/
void vergleich_float()
{
  float a = 432.59;
  float b = (a-(int)a)*100; //b ist 59 oder ?!

  Serial.println("\n\n\n--- Funktion Vergleich ---");
  if (b == 59.0) Serial.println("Ja b ist 59.0, wie ich in der Schule gelernt habe.\n");
  else Serial.println("WTF, b ist nicht gleich 59.0!!!");
  Serial.println("---   Ende Vergleich   ---");
}


void bitmuster_float()
{
  float a = 432.59;
  float b = (a-(int)a)*100;

  uint32_t* c = (uint32_t*) &b;
  uint32_t fraction = (*c) & 0x007fffff;     //binäre Nachkommastellen ohne die führende 1 vor dem Komma
  uint32_t mantisse = fraction | 0x00800000; //die weggelassene 1 muss wieder dazu
  int8_t exponent = (*c) >> 23;              //exponent mit bias, Vorzeichen fällt automatisch raus, da es in die 8 Bit nicht reinpasst.
  exponent = exponent - 127;                 //jetzt ist der bias weg und wir haben den richtigen Exponenten. Achtung: der Exponent kann auch ein Vorzeichen haben.
  int8_t sign = (*c) >> 31;                  //das Vorzeichen der Mantisse

  Serial.println("\n\n\n--- Funktion Bitmuster ---");
  Serial.print("\nDie zu untersuchende Zahl: ");
  Serial.println(b, 10);
  Serial.print("Bitmuster: ");
  Serial.println(*c, BIN);
  Serial.print("Bitmuster in HEX: ");
  Serial.println(*c, HEX);
  Serial.print("\nMantisse: ");
  Serial.println(mantisse);
  Serial.print("Exponent mit abgezogenen Bias: ");
  Serial.println(exponent);
  Serial.println("---   Ende Bitmuster   ---");
}


void epsilon_float()
{
  uint32_t epsilon_bits = 0x3f800001; //Eigentlich 1 + epsilon. Oder die kleinste darstellbare Zahl größer als 1.
  float*   epsilon      = (float*) &epsilon_bits;

  Serial.println("\n\n\n--- Funktion Epsilon ---");
  Serial.print("\nEpsilon: ");
  Serial.println(*epsilon, 10);
  Serial.println(__FLT_EPSILON__, 10); 
  Serial.println(__DBL_EPSILON__, 10);
  Serial.println("---   Ende Epsilon   ---");
}

void vergleich_float_richtig()
{
  float a = 432.59;
  float b = (a-(int)a)*100; //b ist 59 oder ?!

  Serial.println("\n\n\n--- Funktion Vergleich richtig ---");
  if (fabs(b-59.0) < 1000*__FLT_EPSILON__) Serial.println("Ja b ist 59.0, wie ich in der Schule gelernt habe.\n");
  else Serial.println("WTF, b ist nicht gleich 59.0!!!");
  Serial.println("---   Ende Vergleich richtig   ---");

}


void setup() {
  Serial.begin(9600);

  vergleich_float();
  bitmuster_float();
  epsilon_float();
  vergleich_float_richtig();
 }

void loop() {

}
