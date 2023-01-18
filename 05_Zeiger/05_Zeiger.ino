
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  long a; //4 bytes
  byte b; //1 byte
  int  c = 668; //2 bytes 668 = 0x029C
  // byte spion;
  // &spion = 0x08FC;
  byte *spion;
  spion = (byte *) &c + 1;
  // spion = (byte *) 0x08F9;
  //nur zum nachschauen von der Adressse von a: &a
  
  Serial.print("a: ");
  Serial.println(a);
  Serial.println((int) &a);
  Serial.print("b: ");
  Serial.println(b);
  Serial.println((int) &b);
  Serial.print("c: ");
  Serial.println(c);
  Serial.println((int) &c);
  Serial.print("Spion: ");
  Serial.println(*spion, HEX);
}


void loop() {
  // put your main code here, to run repeatedly:
}
