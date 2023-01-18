void setup() {
  // put your setup code here, to run once:
  unsigned int sepp = 0xffff;
  int hias = 0b10011110111;
  

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

  Serial.print("Größe in Bytes von sepp: ");
  Serial.println(sizeof(sepp));
}

void loop() {
  // put your main code here, to run repeatedly:
  double sepp = 3.0;
}
