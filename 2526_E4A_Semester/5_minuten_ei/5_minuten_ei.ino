#include "donner.h"

/* 5.5min = 330s
   330s : 16,384ms = 20141,60 = 20142
*/

constexpr uint16_t OVF_TARGET = 20142;

volatile bool eier_fertig = false;

void setup() {
  Serial.begin(9600);
  Serial.println("Jetzt geht's los!!!");
  TCCR2A = 0;
  TCCR2B = 0;
  //TCCR2A &= ~(1 << WGM21) & ~(1 << WGM20);
  //TCCR2A &= ~((1 << WGM21) | (1 << WGM20));
  TCCR2B |= (1 << CS20) | (1 << CS21) | (1 << CS22); //Prescaler 1024
  //TCCR2B &= ~(1 << WGM22);
  TCNT2 = 0;
  TIMSK2 |= (1 << TOIE2); //Overflow Interrupt enable
}


ISR(TIMER2_OVF_vect) {
  static uint16_t ovf = 0;
  ovf++;
  
  if (ovf >= OVF_TARGET) {
    eier_fertig = true;
  }
}


// Trial Division (didaktisch simpel)
bool isPrime64(uint64_t n) {
  if (n < 2) return false;
  if ((n & 1ULL) == 0) return n == 2;

  // nur ungerade Teiler testen
  for (uint64_t d = 3; d * d <= n; d += 2) {
    if ((n % d) == 0) return false;
  }
  return true;
}

void workload_safe_prime() {
  // Start absichtlich "kleiner", sonst wird Trial Division zu langsam
  static uint64_t p = 4000000007ULL; // ungerade Startzahl (bekannter Prime-Kandidatbereich)
  p += 2; // nur ungerade prüfen

  if (isPrime64(p)) {
    uint64_t q = (p - 1) / 2;
    if (isPrime64(q)) {
      Serial.print("Safe prime p gefunden: ");
      printHex(p);
    }
  }
}

void loop() {
  // Workload: so oft wie möglich rechnen, drucken nur bei Treffer
  workload_safe_prime();

  if (eier_fertig) {
    
    TIMSK2 = 0; // disable all Timer2 interrupts
    //TIMSK2 &= ~(1 << TOIE2); //Overflow Interrupt disable
    
    Serial.println("Schwing Deinen Arsch zum Herd!!!");
  }
}
