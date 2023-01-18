#include <avr/io.h>
#include <avr/interrupt.h>


volatile bool     coke_alarm;
volatile uint8_t  coke_time;
const    uint8_t  coke_pin = 13;       //HIER digitales pin für cola
const    uint16_t coke_duration = 10;  //HIER wieviel Sekunden braucht cola


//This is called every 1 second
ISR(TIMER1_COMPA_vect) {
  if (coke_alarm == true)
  {
    coke_time -= 1;
    if (coke_time == 0)
    {
      coke_alarm = false;
      //HIER cola ausschalten
      digitalWrite(coke_pin, LOW);
    }
  }
}

void install_alarm()
{
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
  Serial.println("Alarm installed.");
}


void setup() {
  Serial.begin(115200);
  pinMode(coke_pin, OUTPUT);
  digitalWrite(coke_pin, LOW);

  install_alarm();
}


void loop() {
  Serial.println(coke_time);
  delay(200);
  //HIER cola einschalten wenn es noch nicht läuft, evtl andere Bedingungen auch abfragen
  if (coke_alarm == false)
  {
    digitalWrite(coke_pin, HIGH);
    coke_time = coke_duration;
    coke_alarm = true;
  }
}
