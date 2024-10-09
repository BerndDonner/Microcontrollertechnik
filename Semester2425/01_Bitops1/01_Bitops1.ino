void binPrint(uint16_t x, char* buffer)
{
  {
    auto k{x};
    for (uint8_t j = sizeof(x)*8; j > 0; k >>= 1)   buffer[--j] = '0' + (k & 0x1);
  }
}

void setup() {
  uint16_t a = 0xa35c;
  char buffer[sizeof(a)*8+1];
  buffer[sizeof(a)*8] = '\0';

  Serial.begin(9600);
  Serial.println(a);

  uint16_t bitmaske = 0b0000111111110000; //0x0ff0

  binPrint(a, buffer);
  Serial.println(buffer);

  binPrint(a & bitmaske, buffer);
  Serial.println(buffer);

  bitmaske = 0b0000000011111111;
  
  binPrint(a | bitmaske, buffer);
  Serial.println(buffer);

  bitmaske = 0b1000000000000000; //0x8000
  
  binPrint(a ^ bitmaske, buffer);
  Serial.println(buffer);

}

void loop() {

}
