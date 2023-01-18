void setup() {
  Serial.begin(9600);
 
  volatile byte c = 0x2A;
  volatile byte d = 0x39;

  asm (
    "next:"         "\n"
    "ADD %0, %1"    "\n"
    "BRVS overflow" "\n"
    : "=r" (c)
    : "r" (d), "0" (c)
    :
  );

  Serial.print("Rechnung in ASM. Ergebnis: ");
  Serial.println((int) c, HEX);

  asm (
    "JMP end"   "\n"
    "overflow:" "\n"
  );

  Serial.print("Rechnung in ASM. Ergebnis: ");
  Serial.println((int) c, HEX);
  Serial.println("Overflow ist gesetzt!");

  asm("end:");
}

void loop() {
}
