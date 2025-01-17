#include <avr/io.h>
#include <avr/interrupt.h>

const uint8_t ledPin = 13;
const uint8_t interruptPin0 = 2;
volatile bool state = true;  //volatile ist wichtig, das die Variable in der ISR geändert wird.


/** Das ist die ISR */
ISR(INT0_vect)
{
  state = !digitalRead(interruptPin0);
}

void setup()
{
  pinMode(ledPin, OUTPUT);
  pinMode(interruptPin0, INPUT_PULLUP); //INPUT_PULLUP heißt: mit einem internen 10kOhm Wiedersstand mit 5V verbunden. D.h im unbeschaltenten Zustand: HIGH
  cli(); //noInterrupts();
  EICRA = (1<<ISC00);	// Interrupt INT0 wird bei jeder Flanke ausgelöst (siehe EICRA Register im Datenblatt) 
  EIMSK = (1<<INT0);  // Interrupt INT0 setzen
  sei(); //interrupts();
}


printf("%.5f\n", x);

void loop()
{
  digitalWrite(ledPin, state);
}

