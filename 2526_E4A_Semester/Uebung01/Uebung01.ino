void setup() {
  Serial.begin(9600);
  Serial.println("1.te Aufgabe:");
  Serial.println(47, HEX);
  Serial.println("2.te Aufgabe:");
  Serial.println(0xffea, DEC);
  Serial.println("3.te Aufgabe:");
  Serial.println(0xff);
  Serial.println("4.te Aufgabe:");
  Serial.println(0xffff);
  Serial.println("5.te Aufgabe:");
  Serial.println(0xffffffff);
  Serial.println("6.te Aufgabe:");
  Serial.println(sizeof(float));
  Serial.println("7.te Aufgabe:");
  Serial.println(sizeof(double));
  Serial.println("8.te Aufgabe:");
  Serial.println(0xfa, BIN);
  Serial.println((uint8_t) ~0xfa, BIN);
  Serial.println("9.te Aufgabe:");
  Serial.println("10.te Aufgabe:");
  

  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
