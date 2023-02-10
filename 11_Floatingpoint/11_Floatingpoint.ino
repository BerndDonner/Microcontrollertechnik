/*
Es gibt unter der arduino-Oberfläche keinen echten Datntyp double.
Auf dem Arduino ist "sizeof(float) = sizeof(double) = 4"
Vergleichen Sie floating point niemals direkt: a == 0.5             (falsch)
sondern immer                                  abs(a-0.5) < epsilon (richtig)
exponenten mit nur 0 sind 
               nur 1

*/

void setup() {
  Serial.begin(9600);
  float a = 432.59;
  float b = (a-(int)a)*100;
  uint32_t* c = (uint32_t*) &b;
  uint32_t mantisse = 0b111010111111111110100000; //mantisse
  int8_t exponent = 0b10000100 - 127; //exponent ohne Bias

  uint32_t epsilon_bits = 0x3f800001; //Eigentlich 1 + epsilon. Oder die kleinste darstellbare Zahl größer als 1.
  float*   epsilon      = (float*) &epsilon_bits;


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

  Serial.print("\nEpsilon: ");
  Serial.println(*epsilon, 10);
  Serial.println(__FLT_EPSILON__, 10); 
  Serial.println(__DBL_EPSILON__, 10);
 }

void loop() {

}
