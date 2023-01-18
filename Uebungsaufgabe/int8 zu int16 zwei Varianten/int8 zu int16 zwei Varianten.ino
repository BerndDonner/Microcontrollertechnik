void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  uint8_t irpixels[2] = {0x12, 0x34};
  int16_t* spion = (int16_t*) &irpixels[0];
  int16_t vir = (int16_t)(irpixels[1] << 8 | irpixels[0]);

  
  Serial.println("Wert der Variablen");
  Serial.print("Variante Bitoperationen: ");
  Serial.println((int16_t) vir, HEX);
  Serial.print("Variante Zeiger:         ");
  Serial.println(*spion, HEX);
}

 

void loop() {
  // put your main code here, to run repeatedly:
}
