#include <avr/io.h>
#include <avr/interrupt.h>

const uint8_t ledPin = 13;
const uint8_t interruptPin = 2;
volatile bool state = true;  //volatile ist wichtig, das die Variable in der ISR geändert wird.


/** Das ist die ISR */
ISR(TIMER1_COMPA_vect)
{
  state = !state;
}

void setup()
{
  pinMode(ledPin, OUTPUT);
  pinMode(interruptPin, INPUT_PULLUP); //INPUT_PULLUP heißt: mit einem internen 10kOhm Wiedersstand mit 5V verbunden. D.h im unbeschaltenten Zustand: HIGH
  cli();
  // turn on CTC mode
  TCCR1A = 0;// set entire TCCR1A register to 0
  TCCR1B = 0;// same for TCCR1B
  TCCR1B |= (1 << WGM12);
  // Set CS12 and CS10 bit for prescaler 1024
  TCCR1B |= (1 << CS12) | (1 << CS10) ; 
  
  //initialize counter value to 0;
  TCNT1  = 0;
  
  // set timer count for every 1 second
  OCR1A = 0x3d09;  // (16*10^6)^-1 * 1024 * 0x3d09 = 1sec  
  
  // enable timer compare interrupt
  TIMSK1 |= (1 << OCIE1A);
  sei();
}

void loop()
{
  digitalWrite(ledPin, state);
}
