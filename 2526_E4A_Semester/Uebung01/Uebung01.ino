void setup() {
  Serial.begin(9600);
  Serial.println("1.te Aufgabe:");
  Serial.println(47, HEX);
  Serial.println("2.te Aufgabe:");
  Serial.println(0xffea, DEC);
  Serial.println("3.te Aufgabe:");
  Serial.println((uint8_t) 0xff); //<---cast besprechen

  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
