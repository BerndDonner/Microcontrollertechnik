#include "donner.h"

void setup() {
  Serial.begin(115200);
  Serial.println("Jetzt geht's los!!!");
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
}
