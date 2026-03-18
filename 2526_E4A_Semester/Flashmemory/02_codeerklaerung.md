# Codeerklärung: Flash-Speicher am Arduino Uno

In dieser Datei werden die drei Sketch-Versionen Schritt für Schritt erklärt.

Der Fokus liegt dabei auf dem Umgang mit:

- großem konstantem Datenmaterial
- `PROGMEM`
- `F(...)`
- Zeichenliteralen wie `'X'`

Die Zielplattform ist ausschließlich der **Arduino Uno mit ATmega328P**.

---

## 1. Das Font-Array

In allen drei Versionen gibt es ein großes Font-Array mit 256 Zeichen zu je 5 Bytes.

### Version 1

```cpp
const uint8_t font[] = { ... };
```

Hier sieht das Array zunächst wie ein ganz normales Datenfeld aus.

Das ist als Ausgangssituation gut, weil der Zugriff sehr einfach ist und die Schüler den ursprünglichen Code schnell verstehen.

### Version 2 und Version 3

```cpp
const uint8_t font[] PROGMEM = { ... };
```

Hier wird das gleiche Font-Array bewusst in den Programmspeicher gelegt.

Das ist auf dem Uno eine sinnvolle Optimierung, weil der Font mit 1280 Byte sehr groß ist.

---

## 2. Die Konstanten für Breite und Höhe

```cpp
constexpr uint8_t FONT_BREITE = 5;
constexpr uint8_t FONT_HOEHE  = 8;
```

Diese beiden Konstanten beschreiben die Struktur eines Zeichens.

- Ein Zeichen ist 5 Spalten breit.
- Jede Spalte enthält 8 Bit für 8 Pixel in der Höhe.

### Warum `constexpr`?

Diese Werte stehen schon beim Übersetzen fest und ändern sich nicht.

Gerade bei so kleinen elementaren Konstanten ist das eine saubere und einfache Lösung.

Didaktisch wichtig:

Hier muss man **nicht** mit `PROGMEM` arbeiten. Es geht ja nicht um große Datentabellen, sondern nur um sehr kleine feste Werte.

---

## 3. Die Compile-Zeit-Prüfung

```cpp
static_assert(sizeof(font) % FONT_BREITE == 0,
              "Font-Array hat keine gueltige Breite.");
```

### Bedeutung

Schon beim Übersetzen wird geprüft, ob die Gesamtgröße des Arrays ein Vielfaches von 5 ist.

Wenn das nicht stimmt, passt die angenommene Font-Struktur nicht.

### Warum ist das schön?

Das ist sauberer als ein Fehler, der erst zur Laufzeit auffällt.

Die Schüler sehen hier außerdem einen wichtigen Unterschied:

- Manche Fehler prüft man **erst zur Laufzeit**.
- Andere Fehler kann man schon **beim Übersetzen** erkennen.

---

## 4. `sizeof(font)`

In allen drei Versionen wird `sizeof(font)` verwendet, zum Beispiel hier:

```cpp
sizeof(font) / FONT_BREITE
```

Damit berechnen wir die Anzahl der Zeichen im Font.

### Wichtiger Punkt

Das funktioniert auch dann, wenn `font` als `PROGMEM` deklariert wurde.

Warum?

Weil `sizeof(...)` mit dem bekannten Typ und der bekannten Arraygröße arbeitet. Es muss dazu die Daten nicht aus dem Flash lesen.

---

## 5. Das lokale Array `zeichen`

```cpp
uint8_t zeichen[FONT_BREITE];
```

Dieses Array dient als kleiner Arbeitsbereich.

In dieses Feld laden wir immer genau **ein Zeichen** mit 5 Bytes.

Warum ist das sinnvoll?

Wir wollen beim Ausgeben nicht direkt ständig mit dem kompletten Font-Array arbeiten, sondern nur mit einem kleinen Puffer für das aktuelle Zeichen.

Das ist auch bei Version 2 und 3 sinnvoll:

- Der große Font bleibt im Flash.
- Für die eigentliche Ausgabe holen wir nur die gerade benötigten 5 Bytes in ein kleines RAM-Array.

---

## 6. Zugriff in Version 1

```cpp
zeichen[i] = font[k * FONT_BREITE + i];
```

Hier wird direkt auf das Array zugegriffen.

Das ist die einfache Ausgangssituation.

Didaktisch ist das gut, weil man zuerst den Grundgedanken des Programms versteht:

- `k` wählt das Zeichen aus.
- `i` läuft durch die 5 Spalten des Zeichens.

---

## 7. Zugriff in Version 2 und 3

```cpp
zeichen[i] = pgm_read_byte(font + k * FONT_BREITE + i);
```

Jetzt liegt der Font im Flash.

Darum kann man die Daten auf dem AVR nicht mehr einfach wie ein normales RAM-Array lesen.

### Bedeutung der Zeile

- `font + k * FONT_BREITE + i` berechnet die Adresse des gewünschten Bytes im Font.
- `pgm_read_byte(...)` liest genau dieses Byte aus dem Programmspeicher.

Das ist der eigentliche Kern der `PROGMEM`-Version.

---

## 8. Die äußere Schleife über alle Zeichen

```cpp
for (uint16_t k = 0; k < sizeof(font) / FONT_BREITE; ++k)
```

### Bedeutung

Diese Schleife geht durch den gesamten Font.

Da ein Zeichen aus 5 Bytes besteht, erhalten wir die Anzahl der Zeichen über:

```cpp
sizeof(font) / FONT_BREITE
```

### Warum `uint16_t`?

Die Anzahl der Zeichen ist hier 256.

Ein `uint8_t` könnte auf dem Uno zwar Werte bis 255 speichern, aber eben nicht 256.

Darum ist `uint16_t` die sichere Wahl.

---

## 9. Die Schleife über die 5 Bytes eines Zeichens

```cpp
for (uint8_t i = 0; i < FONT_BREITE; ++i)
```

Hier werden die 5 Spalten eines Zeichens in das lokale Array `zeichen` geladen.

Jedes Byte repräsentiert eine Spalte mit 8 Bit.

---

## 10. Ausgabe des Zeichenindex

```cpp
Serial.print(k);
Serial.println(F(".tes Zeichen:"));
```

In Version 1 steht dort noch ein normales Stringliteral, in Version 2 und 3 wird `F(...)` verwendet.

Die Idee dahinter:

Der Text ist konstant und muss nicht unnötig als normale RAM-Daten behandelt werden.

---

## 11. Die Schleife über die 8 Pixelzeilen

```cpp
for (uint8_t j = 0; j < FONT_HOEHE; ++j)
```

Da jede Spalte 8 Bit enthält, müssen wir 8 Mal durchlaufen.

In jedem Durchlauf betrachten wir das jeweils niederwertigste Bit jeder Spalte.

---

## 12. Die eigentliche Pixel-Ausgabe

Der Test ist in allen Versionen gleich:

```cpp
if (zeichen[i] & 0x01)
```

### Bedeutung

Mit `0x01` prüfen wir, ob das niederwertigste Bit gesetzt ist.

Wenn ja, wird ein sichtbares Zeichen ausgegeben. Wenn nein, ein Leerzeichen.

Danach wird das Byte nach rechts geschoben:

```cpp
zeichen[i] >>= 1;
```

So rückt beim nächsten Schleifendurchlauf das nächste Pixel-Bit an die Prüfposition.

---

## 13. Version 1: Ausgabe mit normalen Strings

```cpp
if (zeichen[i] & 0x01) Serial.print("X");
else                   Serial.print(" ");
```

Das ist leicht lesbar und für die Ausgangssituation völlig in Ordnung.

Didaktisch ist das die einfache Basisversion.

---

## 14. Version 2: Ausgabe mit `F("X")`

```cpp
if (zeichen[i] & 0x01) Serial.print(F("X"));
else                   Serial.print(F(" "));
```

Hier wird bewusst auch bei sehr kurzen Ausgaben `F(...)` benutzt.

Warum?

Weil in dieser zweiten Version die **maximale Flash-Nutzung** demonstriert werden soll.

Das ist technisch bei einzelnen Zeichen nicht die eleganteste Endlösung, aber als Unterrichtsschritt sehr nützlich.

Die Schüler sehen dadurch deutlich:

- Auch konstante Ausgabetexte kann man in den Flash legen.
- `F(...)` ist ein Werkzeug für AVR-Programme mit knappem SRAM.

---

## 15. Version 3: Ausgabe mit Zeichenliteralen

```cpp
if (zeichen[i] & 0x01) Serial.print('X');
else                   Serial.print(' ');
```

Das ist die didaktisch und technisch schönere Endfassung für diesen Teil.

### Warum?

`"X"` ist ein Stringliteral.

`'X'` ist ein einzelnes Zeichenliteral.

Für die Ausgabe genau eines Zeichens ist `'X'` die passendere Form.

Das gleiche gilt für:

```cpp
' '
'\n'
```

Diese Version zeigt also sehr schön:

- Große konstante Daten gehören in `PROGMEM`.
- Längere feste Texte dürfen mit `F(...)` in den Flash.
- Einzelne Zeichen schreibt man besser direkt als Zeichenliteral.

---

## 16. Warum wird `Serial.print('\n')` verwendet?

In Version 3 steht unter anderem:

```cpp
Serial.print('\n');
```

Das ist bewusst ein einzelnes Zeichenliteral für den Zeilenumbruch.

In Version 2 wurde dagegen noch demonstrativ geschrieben:

```cpp
Serial.print(F("\n"));
```

Gerade an diesem Vergleich kann man gut den Unterschied zwischen:

- Zeichenliteral
- Stringliteral

besprechen.

---

## 17. Der Mess-Sketch

Der zusätzliche Mess-Sketch enthält:

```cpp
#define MESSUNG_VARIANTE 1
```

Dort kann man zwischen drei Varianten umschalten.

### Ziel des Mess-Sketches

Die Schüler sollen nicht nur den Code sehen, sondern auch Messwerte vergleichen:

1. Build-Ausgabe der Arduino IDE
2. freies SRAM zur Laufzeit

### Wichtige Aussage

Die wichtigste Information für den Unterricht liefert die Build-Ausgabe der Arduino IDE.

Dort erscheinen typischerweise Werte für:

- Program storage space
- Global variables

Genau dort sieht man am klarsten, was das Verschieben des Font-Arrays in den Flash bewirkt.

---

## 18. Die Funktion `freiesSram()`

```cpp
int freiesSram()
{
  extern int __heap_start;
  extern int* __brkval;
  int v;
  return reinterpret_cast<int>(&v) -
         (__brkval == nullptr ? reinterpret_cast<int>(&__heap_start)
                              : reinterpret_cast<int>(__brkval));
}
```

Diese Funktion liefert eine grobe Abschätzung des noch freien SRAM.

Für den Unterricht ist das nützlich, weil man zusätzlich zur Compiler-Ausgabe noch eine Laufzeitbeobachtung hat.

Wichtig ist aber:

Diese Messung ist eher ein Hilfsmittel. Die Build-Ausgabe bleibt die Hauptreferenz.

---

## 19. Was ist der eigentliche Unterrichtskern?

Die drei Versionen bilden eine sinnvolle didaktische Treppe:

### Stufe 1

Erst den einfachen Ausgangscode verstehen.

### Stufe 2

Dann zeigen, wie große konstante Daten und feste Texte gezielt in den Flash verschoben werden.

### Stufe 3

Zum Schluss sauber unterscheiden zwischen:

- großem konstantem Datenblock
- festem Text
- einzelnem Zeichen

Genau dabei entsteht das gewünschte Verständnis für:

- Harvard-Architektur
- getrennten Programmspeicher und SRAM
- sinnvollen statt blinden Einsatz von `PROGMEM` und `F(...)`

---

## Was sollen die Schüler nach der Stunde können?

1. Sie sollen erklären können, warum ein großer Font auf dem Uno problematisch für den SRAM ist.
2. Sie sollen wissen, was `PROGMEM` auf dem AVR bewirkt.
3. Sie sollen verstehen, warum man bei `PROGMEM` mit `pgm_read_byte(...)` liest.
4. Sie sollen `F("...")` als Werkzeug für feste Texte erkennen.
5. Sie sollen den Unterschied zwischen `'X'` und `"X"` in Grundzügen benennen können.

---

## Denkfragen

1. Warum ist `uint16_t k` hier sinnvoller als `uint8_t k`?
2. Warum braucht die dritte Version weiterhin `PROGMEM`, obwohl `'X'` kein String mehr ist?
3. Was ist der eigentliche Speicherfresser: das Zeichen `'X'` oder das Font-Array?
4. Warum ist `sizeof(font)` auch bei `PROGMEM` korrekt?
5. Warum ist Version 2 als Zwischenschritt didaktisch sinnvoll, obwohl Version 3 am Ende eleganter ist?
