void setup() {
  // put your setup code here, to run once:
  unsigned int sepp = 0xffff;
  int hias = 0b10011110111;
  int a = 0x7fff;
  int b = 0x0001;
  int c = a+b;
  char sechs = 0xfa;

  Serial.begin(9600);
  Serial.print("sepp dec: ");
  Serial.println(sepp, DEC);
  Serial.print("sepp hex: ");
  Serial.println(sepp, HEX);

  Serial.print("Einserkomplement von sepp hex: ");
  Serial.println(~sepp, HEX);
  
  Serial.print("hias dec: ");
  Serial.println(hias);
  Serial.print("hias hex: ");
  Serial.println(hias, HEX);

  Serial.print("sechs dec: ");
  Serial. println(sechs, DEC);

  Serial.print("Größe in Bytes von sepp: ");
  Serial.println(sizeof(sepp));

  Serial.print("a: ");
  Serial.println(a);
  Serial.print("b: ");
  Serial.println(b);
  Serial.print("a+b: ");
  Serial.println(c);
   
}

void loop() {
  // put your main code here, to run repeatedly:
}
