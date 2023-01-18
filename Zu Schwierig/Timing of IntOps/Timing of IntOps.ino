/** Zeitmessung: jetzt fangen wir an zu spinnen ... */

/* Durch timer2 gibt es einen overhead, der natürlich selber clockcycles
 * frisst. Evtl könnte man versuchen diesen overhead durch inlinen von
 * timer2.reset() und timer2.get_count() noch weiter zu reduzieren.
 * Aber diesen overhead kann man sowieso herausrechnen indem man die
 * Zeit 8 mal b += a mit der Zeit 16 mal b += a vergleicht!
 *
 * Ergebnisse:
 * Ein b += a braucht:
 * unsigned char:      7/8 * 0.5us -> 7  clockcycle
 * unsigned int:       7/4 * 0.5us -> 14 clockcycle
 * unsigned Long:      7/2 * 0.5us -> 28 clockcycle
 * unsigned long long: 9   * 0.5us -> 72 clockcycle
 *
 * 1 clockcycle entspricht 0.0625us
 */ 

#include "eRCaGuy_Timer2_Counter.h"

typedef unsigned char integer_to_test;

void setup()
{
  Serial.begin(9600);
  timer2.setup();
}


#pragma GCC push_options
#pragma GCC optimize ("-O0")

void loop()
{
  integer_to_test a = 0x7;
  integer_to_test b = 0xff;

  noInterrupts();
  timer2.reset();
  
  b = b + a + a;
  b = b + a + a;
  b = b + a + a;
  b = b + a + a;
  b = b + a + a;
  b = b + a + a;
  b = b + a + a;
  b = b + a + a;

  b = b + a + a;
  b = b + a + a;
  b = b + a + a;
  b = b + a + a;
  b = b + a + a;
  b = b + a + a;
  b = b + a + a;
  b = b + a + a;

  long t_stop = timer2.get_count();
  interrupts();
  delay(10);
  Serial.print("Benoetigte Zeit: ");
  Serial.println(t_stop);
}

#pragma GCC pop_options

