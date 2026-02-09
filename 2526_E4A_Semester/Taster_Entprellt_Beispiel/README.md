# README – Taster-Entprellung per Totzeit (Dead Time) mit Interrupt-Umschaltung

Dieses Beispiel zeigt eine robuste Taster-Entprellung, bei der **jede Flanke (Press/Release)** per Interrupt behandelt wird, aber **nur dann akzeptiert wird**, wenn seit dem letzten gültigen Ereignis eine feste **Totzeit** vergangen ist. Zusätzlich wird nach einem gültigen **Press** sofort auf **Release** umgeschaltet (und umgekehrt). Dadurch werden Mehrfach-Trigger durch Prellen zuverlässig abgefangen – **unabhängig davon, was im `loop()` gerade passiert**.

---

## Idee in einem Satz

**Nur die erste Flanke zählt – danach wird für z.B. 20 ms alles ignoriert (Totzeit), und außerdem wird die erwartete Flanke (FALLING/RISING) jeweils umgeschaltet.**

---

## Hardware-Annahme

- Taster an **D2** (Interrupt-Pin auf ATmega328P / Arduino Uno)
- Interner Pullup aktiv: `pinMode(interrupt_pin, INPUT_PULLUP)`
- LED an **D13** (PB5)

Typische Verdrahtung:
- D2 ↔ Taster ↔ GND  
- Im Ruhezustand ist D2 **HIGH**, beim Drücken wird D2 **LOW**.

---

## Wie die Entprellung funktioniert

### 1) Totzeit (Dead Time)

```cpp
constexpr uint32_t time_dead = 20000; // 20 ms
```

In jeder ISR:
- Zeitstempel holen: `now = micros()`
- Prüfen: `now - last_ok_us < time_dead`  
  → wenn ja: **Ereignis ignorieren**

Das filtert die typischen Prell-Impulse (mehrere schnelle Flanken innerhalb weniger Millisekunden).

### 2) Umschalten der Interrupt-Flanke

- Start: Wir erwarten einen **Press** → FALLING
- Nach gültigem Press:
  - LED an
  - Interrupt wird auf **RISING** umgestellt (Release)
- Nach gültigem Release:
  - LED aus
  - Interrupt zurück auf **FALLING** (Press)

Damit reagiert das System nur auf das, was als nächstes sinnvoll ist.

---

## Warum das robust ist (auch bei hoher Loop-Last)

Der `loop()` macht absichtlich „viel“:

```cpp
Serial.println(i++);
```

Trotzdem reagiert der Taster sofort, weil:
- LED-Schalten passiert **direkt in der ISR** (konstant schnell)
- die Totzeit verhindert Mehrfachauslösung durch Prellen
- der Loop kann „lahm“ sein, ohne dass die Tastererkennung kaputtgeht

---

## Wichtige Details im Code

### Zeitdifferenz als `uint32_t`

```cpp
if ((uint32_t)(now - last_ok_us) < time_dead) return;
```

Das ist absichtlich so geschrieben, damit es auch bei **Überlauf von `micros()`** funktioniert (der kommt nach ~70 Minuten beim Uno).

### LED direkt über PORTB (schnell)

```cpp
PORTB |= _BV(LED_BIT);     // an
PORTB &= ~_BV(LED_BIT);    // aus
```

Das ist deutlich schneller als `digitalWrite()`.

### Vorsicht: `Serial` in ISR vermeiden

Im Beispiel ist `Serial` nur im `loop()`. Das ist gut – `Serial` in ISR wäre riskant (Blockieren/Timing-Probleme).

---

## Grenzen / Hinweise

- **Totzeit ist fix**: 20 ms ist für viele Taster gut, kann aber je nach Taster zu groß/klein sein.  
  Typisch: 5–30 ms
- **`attachInterrupt()` in ISR**: funktioniert in der Praxis und ist didaktisch gut sichtbar, kostet aber etwas Zeit.  
  Für maximale ISR-Effizienz kann man alternativ beide Flanken erfassen und per Zustandsmaschine filtern.
- `expect_press` ist im gezeigten Code nicht zwingend nötig (weil die Flanke umgeschaltet wird). Als Doku-/Debug-Variable kann sie drin bleiben.

---

## Kurz: Was passiert beim Drücken?

1. FALLING kommt (Taste gedrückt)
2. Wenn Totzeit ok:
   - `last_ok_us = now`
   - LED an
   - Interrupt auf RISING umstellen
3. Prell-Flanken kommen → werden ignoriert (Totzeit)

Beim Loslassen analog.
