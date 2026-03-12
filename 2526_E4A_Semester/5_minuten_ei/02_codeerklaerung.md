# Codeerklärung zur Timer2-Eieruhr

In dieser Datei wird die **Timer-Logik** des Sketches Schritt für Schritt erklärt.

Die Primzahlsuche dient dabei nur als **Hintergrundlast**. Sie ist nicht der eigentliche Unterrichtsschwerpunkt. Entscheidend ist, wie der Timer so eingerichtet wird, dass nach ungefähr 5 Minuten ein Signal ausgelöst wird.

---

## 1. Die globale Variable

```cpp
volatile bool eier_fertig = false;
```

### Bedeutung

Diese Variable ist ein **Flag**.

Sie wird verwendet, um dem Hauptprogramm mitzuteilen:

```text
Die 5 Minuten sind vorbei.
```

### Warum `volatile`?

Auf diese Variable greifen zwei verschiedene Teile des Programms zu:

- die **ISR**
- das **Hauptprogramm** in `loop()`

Ohne `volatile` dürfte der Compiler annehmen, dass sich der Wert nicht „unerwartet“ ändert. Dann könnte er Optimierungen durchführen, die bei Interrupt-Programmen zu Fehlern führen.

Mit `volatile` sagen wir dem Compiler:

```text
Dieser Wert kann sich jederzeit außerhalb des normalen Programmflusses ändern.
```

---

## 2. Die Zielzahl für die Overflows

```cpp
constexpr uint16_t OVF_TARGET = 18310; // 5 min bei 16MHz, Prescaler 1024, Timer2 OVF
```

### Bedeutung

`OVF_TARGET` gibt an, wie viele Timer2-Overflows ungefähr 5 Minuten entsprechen.

### Warum `uint16_t`?

Der Wert `18310` ist größer als `255`. Ein 8-Bit-Typ wäre also zu klein.

Mit `uint16_t` können Werte von `0` bis `65535` gespeichert werden. Das reicht hier bequem aus.

### Warum `constexpr`?

`constexpr` bedeutet: Dieser Wert ist eine Konstante und steht schon zur Compile-Zeit fest.

Das ist passend, weil sich die Zahl im Programm nicht ändern soll.

---

## 3. Initialisierung in `setup()`

```cpp
void setup() {
  Serial.begin(9600);
  Serial.println("Jetzt geht's los!!!");

  // Timer2: Normal Mode (WGM2:0 = 0)
  TCCR2A = 0;
  TCCR2B = (1 << CS22) | (1 << CS21) | (1 << CS20); // Prescaler 1024
  TCNT2  = 0;
  TIMSK2 = (1 << TOIE2); // Overflow Interrupt enable
}
```

Jetzt betrachten wir die wichtigen Zeilen einzeln.

### `TCCR2A = 0;`

Damit werden die Mode-Bits in diesem Register zunächst auf `0` gesetzt.

Für unser Beispiel bedeutet das zusammen mit der Einstellung in `TCCR2B`:

- **Normal Mode**
- der Timer zählt einfach hoch
- bei `255 -> 0` entsteht ein Overflow

### `TCCR2B = (1 << CS22) | (1 << CS21) | (1 << CS20);`

Hier wird der Prescaler eingestellt.

Für Timer2 bedeutet die Bitkombination:

```text
CS22 = 1
CS21 = 1
CS20 = 1
```

also:

```text
Prescaler = 1024
```

Der Timer läuft dadurch deutlich langsamer als der CPU-Takt.

### `TCNT2 = 0;`

Das Zählregister von Timer2 wird auf `0` gesetzt.

Der Timer startet also bei `0`.

### `TIMSK2 = (1 << TOIE2);`

Hier wird der **Overflow-Interrupt** von Timer2 aktiviert.

Das bedeutet:

Sobald Timer2 überläuft, soll die zugehörige ISR aufgerufen werden.

---

## 4. Die ISR

```cpp
ISR(TIMER2_OVF_vect) {
  static uint16_t ovf = 0;
  ovf++;
  if (ovf >= OVF_TARGET) {
    eier_fertig = true;
  }
}
```

Diese Funktion wird automatisch bei jedem Timer2-Overflow ausgeführt.

### `static uint16_t ovf = 0;`

`ovf` zählt, wie viele Overflows bisher aufgetreten sind.

Warum `static`?

Ohne `static` würde die Variable bei jedem ISR-Aufruf neu angelegt und wieder mit `0` starten. Dann könnten wir nichts mitzählen.

Mit `static` bleibt ihr Wert zwischen den ISR-Aufrufen erhalten.

### `ovf++;`

Bei jedem Overflow wird der Zähler um `1` erhöht.

### `if (ovf >= OVF_TARGET)`

Sobald genug Overflows gezählt wurden, sind ungefähr 5 Minuten vergangen.

### `eier_fertig = true;`

Hier setzt die ISR nur das Flag.

Das ist eine gute Lösung, weil die ISR dadurch kurz bleibt. Sie gibt keine langen Texte aus und enthält keine unnötig aufwendigen Operationen.

---

## 5. Was macht die Primzahlsuche in diesem Sketch?

```cpp
void workload_safe_prime() {
  ...
}
```

Diese Funktion ist hier nur eine **Arbeitslast**.

Sie sorgt dafür, dass das Hauptprogramm nicht untätig ist, sondern ständig etwas rechnet.

Didaktisch zeigt das:

- Das Hauptprogramm darf stark beschäftigt sein.
- Der Timer läuft trotzdem im Hintergrund weiter.
- Der Alarm hängt also nicht davon ab, dass wir ständig selbst auf die Zeit schauen.

Die Primzahlsuche ist daher eher eine Demonstration für „gleichzeitig laufende Aufgaben“ als eigentlicher Kern der Timer-Aufgabe.

---

## 6. Die `loop()`-Funktion

```cpp
void loop() {
  // Workload: so oft wie möglich rechnen, drucken nur bei Treffer
  workload_safe_prime();

  if (eier_fertig) {
    uint8_t sreg = SREG;
    cli();
    eier_fertig = false;
    TIMSK2 = 0;
    TCCR2B = 0;
    SREG = sreg;

    Serial.println("Schwing Deinen Arsch zum Herd!!!");
  }
}
```

Auch hier betrachten wir nur die Timer-Logik.

### `workload_safe_prime();`

Das Hauptprogramm rechnet ganz normal weiter.

Genau das ist ja der Sinn der Übung: Zeitmessung und Rechenarbeit laufen nebeneinander.

### `if (eier_fertig)`

Hier prüft das Hauptprogramm, ob die ISR das Flag bereits gesetzt hat.

Wenn ja, sind die 5 Minuten abgelaufen.

---

## 7. Warum wird hier kurz mit `cli()` gearbeitet?

```cpp
uint8_t sreg = SREG;
cli();
eier_fertig = false;
TIMSK2 = 0;
TCCR2B = 0;
SREG = sreg;
```

### Bedeutung

Hier wird ein kurzer kritischer Abschnitt geschützt.

#### `uint8_t sreg = SREG;`

Der aktuelle Interrupt-Zustand wird gesichert.

#### `cli();`

Globale Interrupts werden kurz abgeschaltet.

Dadurch kann die ISR nicht genau in dem Moment dazwischenfunken, in dem wir gemeinsam mehrere zusammenhängende Änderungen vornehmen.

#### `eier_fertig = false;`

Das Flag wird zurückgesetzt.

#### `TIMSK2 = 0;`

Der Timer2-Overflow-Interrupt wird deaktiviert.

#### `TCCR2B = 0;`

Damit wird der Timer praktisch gestoppt, weil keine Taktquelle mehr ausgewählt ist.

#### `SREG = sreg;`

Der vorherige Zustand des Statusregisters wird wiederhergestellt.

So werden die Interrupts genau in den Zustand zurückversetzt, der vorher galt.

---

## 8. Warum ist das sauberer als alles in der ISR zu erledigen?

Man könnte versucht sein, direkt in der ISR:

- den Timer abzuschalten,
- eine serielle Ausgabe zu machen,
- weitere Aktionen auszuführen.

Didaktisch und praktisch ist es aber besser, wenn die ISR nur das Nötigste tut.

### Gute Aufgabenteilung

**ISR:**

- Overflow zählen
- Flag setzen

**Hauptprogramm:**

- Flag prüfen
- Timer abschalten
- Meldung ausgeben

So bleibt die ISR kurz und die Programmlogik klar getrennt.

---

## 9. Zeitrechnung noch einmal kompakt

Gegeben:

```text
f_CPU = 16 MHz
Prescaler = 1024
Timer2 = 8 Bit
```

Ein Timerschritt dauert:

```text
1024 / 16 000 000 s = 64 µs
```

Ein Overflow dauert bei 256 Schritten:

```text
256 * 64 µs = 16384 µs = 16,384 ms
```

Benötigte Anzahl Overflows für 5 Minuten:

```text
300 s / 0,016384 s ≈ 18310,55
```

Verwendet wird:

```cpp
OVF_TARGET = 18310;
```

Das liegt sehr nahe an 5 Minuten.

---

## 10. Was sollen Sie aus diesem Beispiel mitnehmen?

- Ein Hardwaretimer kann Zeit im Hintergrund erfassen.
- Der Prescaler macht den Timer langsamer.
- Ein Overflow kann einen Interrupt auslösen.
- In der ISR zählt man kurze Ereignisse mit.
- Das Hauptprogramm kann währenddessen andere Aufgaben erledigen.
- Eine ISR sollte möglichst kurz bleiben.

---

## Denkfragen

1. Warum muss `eier_fertig` als `volatile` deklariert werden?
2. Warum ist `ovf` in der ISR `static`?
3. Welche Wirkung hat `TIMSK2 = 0;`?
4. Welche Wirkung hat `TCCR2B = 0;`?
5. Warum ist es sinnvoll, in der ISR nur ein Flag zu setzen?
