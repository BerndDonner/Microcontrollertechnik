void binPrint(uint16_t x, char* buffer)
{
  {
    auto k{x};
    for (uint8_t j = sizeof(x)*8; j > 0; k >>= 1)   buffer[--j] = '0' + (k & 0x1);
  }
}

void setup() {

  uint8_t a = 0b10100011; //0xa3;

  char buffer[sizeof(a)*8+1];
  buffer[sizeof(a)*8] = '\0';

  Serial.begin(9600);
  
  Serial.print("Start    Bitmuster: ");
  Serial.print(a, BIN);
  Serial.print("\n");
  Serial.print("Start    Zahl: ");
  Serial.print(a);
  Serial.print("\n");

  uint8_t b = a << 2;

  Serial.print("Ergebnis Bitmuster: ");
  Serial.print(b, BIN);
  Serial.print("\n");
  Serial.print("Ergebnis Zahl: ");
  Serial.print(b);
  Serial.print("\n");

  uint8_t c = b >> 2;

  Serial.print("Ergebnis Bitmuster: ");
  Serial.print(c, BIN);
  Serial.print("\n");
  Serial.print("Ergebnis Zahl: ");
  Serial.print(c);
  Serial.print("\n");

  uint8_t d = 5/2; //0b0101 >> 2 = 0b0001

  Serial.print("Ergebnis Division: ");
  Serial.println(d);
}

void loop() {

}
