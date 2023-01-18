void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:


  volatile byte c = 0x2A;
  volatile byte d = 0x39;
  volatile byte e = 0x0;

  Serial.print("1. Rechnung in C.   Ergebnis: ");
  Serial.println(c+d, HEX);

  e = c+d;
  asm (
    "BRVC end" "\n"
  );
  Serial.println("Overflow ist gesetzt!");

  asm("end:");
}

void loop() {
}
