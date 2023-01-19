/** Zeitmessung: jetzt fangen wir an zu spinnen ... */

/* Durch timer2 gibt es einen overhead, der natürlich selber clockcycles
   frisst. Evtl könnte man versuchen diesen overhead durch inlinen von
   timer2.reset() und timer2.get_count() noch weiter zu reduzieren.
   Aber diesen overhead kann man sowieso herausrechnen indem man die
   Zeit 8 mal b += a mit der Zeit 16 mal b += a vergleicht!

   Ergebnisse:
   Ein b += a braucht:
   unsigned char:      7/8 * 0.5us -> 7  clockcycle
   unsigned int:       7/4 * 0.5us -> 14 clockcycle
   unsigned long:      7/2 * 0.5us -> 28 clockcycle
   unsigned long long: 9   * 0.5us -> 72 clockcycle

   1 clockcycle entspricht 0.0625us
*/

#define MEASURE_START   noInterrupts();     \
  TCCR1A = 0;         \
  TCCR1B = 1 << CS10; \
  TCNT1 = 0;

/** offset empty loop is 4 cycles with optimization off */
/** offset empty loop is 1 cycles with standard optimization */
#define MEASURE_STOP(c, offset)  c = TCNT1;         \
  c = c - offset;         \
  interrupts();




typedef unsigned int integer_to_test;

void setup()
{
  Serial.begin(9600);
}


//#pragma GCC push_options
//#pragma GCC optimize ("-O0")

void loop()
{
  volatile integer_to_test a = 0x1010;
                               
  volatile integer_to_test b = 0x0008;
  unsigned int cycles;


  uint8_t irpixels[2] = {0x12, 0x34};
  MEASURE_START
  volatile uint16_t* spion = (uint16_t*) &irpixels[0];
  MEASURE_STOP(cycles, 1)

  delay(10);
  Serial.print("Benoetigte Zeit: ");
  Serial.println(cycles);
  Serial.println(*spion, HEX);
}

//#pragma GCC pop_options
