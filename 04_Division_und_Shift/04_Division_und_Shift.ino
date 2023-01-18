#define MEASURE_START   noInterrupts();     \
                        TCCR1A = 0;         \
                        TCCR1B = 1 << CS10; \
                        TCNT1 = 0;

/** offset empty loop is 4 cycles with optimization off */
/** offset empty loop is 1 cycles with standard optimization */
#define MEASURE_STOP(c, offset)  c = TCNT1;         \
                         c = c - offset;         \
                         interrupts();

  

void setup()
{
  Serial.begin(9600);

  volatile int32_t a = 0xffff;
  volatile int32_t b = 0x0002;
  volatile int32_t c = 0x0001; //Zusammenhang zwischen c und b: b = 2^c
  
  int32_t e;

  unsigned int cycles;

  MEASURE_START
  
  e = a >> c;
  
  MEASURE_STOP(cycles, 1)

  delay(10);
  Serial.print("Ergebnis Shift: ");
  Serial.println(e);
  Serial.print("Benoetigte Takte Shift: "); //27 cycles!!!
  Serial.println(cycles);

  MEASURE_START
  
  e = a / b;
  
  MEASURE_STOP(cycles, 1)

  delay(10);
  Serial.print("Ergebnis Division: ");
  Serial.println(e);
  Serial.print("Benoetigte Takte Division: "); //654 cycles!!
  Serial.println(cycles);

}



void loop()
{
}
