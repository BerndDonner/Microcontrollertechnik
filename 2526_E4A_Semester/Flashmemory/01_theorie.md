# Flash-Speicher und SRAM am Arduino Uno

## Ausgangssituation

Wir wollen ein relativ großes Font-Array auf einem **Arduino Uno mit ATmega328P** verwenden.

Jedes Zeichen besteht hier aus **5 Bytes**. Bei **256 Zeichen** ergibt das:

```text
256 * 5 = 1280 Byte
```

Der Uno besitzt aber nur:

```text
SRAM  = 2048 Byte
Flash = 32768 Byte
```

Ein Font mit `1280 Byte` ist für den Flash unproblematisch, für den SRAM aber bereits sehr groß.

---

## Warum ist das auf dem Uno überhaupt ein Thema?

Der **ATmega328P** ist ein Mikrocontroller mit **Harvard-Architektur**.

Das bedeutet vereinfacht:

- **Programmspeicher (Flash)** und **Datenspeicher (SRAM)** sind getrennt.
- Der Prozessor arbeitet also nicht mit einem einzigen gemeinsamen Speicher.
- Darum ist es wichtig zu unterscheiden, **wo** Daten liegen.

Für unser Beispiel sind zwei Speicherbereiche besonders wichtig:

### Flash

Im Flash liegt das eigentliche Programm.

Dort können auch **konstante große Tabellen** sinnvoll abgelegt werden, zum Beispiel:

- Fonts
- Bitmaps
- Nachschlagetabellen
- feste Menüttexte

### SRAM

Im SRAM liegen zur Laufzeit vor allem:

- veränderliche Variablen
- lokale Variablen
- der Stack
- Puffer
- Objekte, die tatsächlich als Daten im RAM gebraucht werden

Der SRAM ist beim Uno sehr knapp.

---

## Die drei Programmversionen im Überblick

## Version 1: Ausgangssituation

In der ersten Version steht das Font-Array einfach als normales Array im Programm:

```cpp
const uint8_t font[] = { ... };
```

Didaktisch ist das ein guter Startpunkt, weil der Zugriff einfach aussieht:

```cpp
zeichen[i] = font[k * FONT_BREITE + i];
```

Das Problem dabei:

Das große Font-Array ist noch **nicht als PROGMEM-Daten organisiert**. Für den Uno ist das daher keine gute Endlösung, wenn man SRAM sparen will.

---

## Version 2: Maximale Flash-Nutzung

In der zweiten Version wird das große Font-Array bewusst in den Programmspeicher gelegt:

```cpp
const uint8_t font[] PROGMEM = { ... };
```

Zusätzlich werden auch Stringliterale für `Serial.print(...)` mit `F(...)` versehen:

```cpp
Serial.println(F("Start: Font liegt im Flash (PROGMEM)"));
Serial.print(F("X"));
```

Damit verfolgen wir didaktisch zwei Ziele:

1. Das große Font-Array soll den knappen SRAM nicht unnötig belasten.
2. Auch konstante Ausgabetexte sollen möglichst im Flash bleiben.

Wichtig ist dabei:

Auf dem AVR kann man ein `PROGMEM`-Array nicht einfach wie ein normales RAM-Array lesen.

Darum braucht man Funktionen wie:

```cpp
pgm_read_byte(...)
```

Beispiel:

```cpp
zeichen[i] = pgm_read_byte(font + k * FONT_BREITE + i);
```

---

## Version 3: Finale Version mit Zeichenliteralen

In der dritten Version bleibt das große Font-Array weiterhin in `PROGMEM`.

Aber bei der eigentlichen Zeichenausgabe wird jetzt nicht mehr

```cpp
Serial.print(F("X"));
```

verwendet, sondern

```cpp
Serial.print('X');
```

und entsprechend

```cpp
Serial.print(' ');
```

Warum ist das sinnvoll?

`"X"` ist ein **Stringliteral**. Das ist also ein kleines nullterminiertes Zeichenfeld:

```text
'X' '\0'
```

`'X'` dagegen ist nur ein **einzelnes Zeichenliteral** vom Typ `char`.

Für genau diese Ausgabe ist das die passendere Form.

Didaktisch ist die Aussage also:

- Ein großer Font gehört in den Flash.
- Ein langer Ausgabetext darf gern mit `F(...)` in den Flash.
- Ein einzelnes Zeichen wie `'X'` oder `' '` braucht kein eigenes Stringobjekt.

---

## Wichtiger Gedanke zu kleinen Konstanten

In der Stunde soll auch deutlich werden:

Nicht jede Konstante muss krampfhaft in ein `PROGMEM`-Array verschoben werden.

Beispiele:

```cpp
constexpr uint8_t FONT_BREITE = 5;
constexpr uint8_t FONT_HOEHE  = 8;
```

Solche kleinen Konstanten sind für den Compiler oft direkt und unkompliziert nutzbar.

Für unseren Unterricht reicht folgende praktische Faustregel:

- **Große konstante Tabellen**: sehr guter Kandidat für `PROGMEM`
- **Lange feste Texte**: oft sinnvoll mit `F(...)`
- **Einzelne Zeichen und kleine elementare Konstanten**: meist direkt und unkritisch

Wir müssen den Schülern hier nicht die komplette Codeerzeugung des Compilers im Detail erklären. Entscheidend ist das Grundverständnis.

---

## Speichergegenüberstellung

## 1. Großes Font-Array

Das Font-Array ist mit Abstand der wichtigste Speicherfresser in diesem Beispiel:

```text
256 Zeichen * 5 Byte = 1280 Byte
```

Wenn diese Daten ungünstig behandelt werden, bleibt vom SRAM des Uno nur noch wenig übrig.

Gerade deshalb ist `PROGMEM` hier ein sehr gutes Unterrichtsbeispiel.

---

## 2. Normale Stringliterale

Auch Texte wie

```cpp
"Start: Font liegt im Flash (PROGMEM)"
".tes Zeichen:"
"X"
" "
```

sind konstante Daten.

Bei AVR-Programmen kann es sinnvoll sein, solche Texte mit `F(...)` explizit als Flash-Daten zu behandeln:

```cpp
Serial.println(F("..."));
```

---

## 3. Einzelne Zeichen

Einzelne Zeichen wie

```cpp
'X'
' '
'\n'
```

sind keine Strings.

Sie sind für genau diesen Zweck meist die passendere und einfachere Schreibweise als:

```cpp
"X"
" "
"\n"
```

Die dritte Version zeigt das ganz bewusst.

---

## Warum funktioniert `sizeof(font)` auch bei `PROGMEM`?

Das ist ein wichtiger Punkt.

`sizeof(font)` fragt nicht den Speicherinhalt zur Laufzeit ab, sondern arbeitet mit dem bekannten Typ und der bekannten Arraygröße.

Darum funktioniert:

```cpp
sizeof(font)
```

auch dann ganz normal, wenn `font` als `PROGMEM` deklariert wurde.

---

## Was ist also die eigentliche Besonderheit von `PROGMEM`?

Nicht `sizeof`, sondern der **Zugriff** ändert sich.

Normales RAM-Array:

```cpp
font[index]
```

`PROGMEM`-Array auf AVR:

```cpp
pgm_read_byte(font + index)
```

Genau dieser Unterschied ist der Kern des Beispiels.

---

## Der Mess-Sketch

Zusätzlich gibt es einen Mess-Sketch.

Mit ihm kann man drei Dinge tun:

1. denselben Sketch in mehreren Varianten übersetzen,
2. die Build-Ausgabe der Arduino IDE vergleichen,
3. zusätzlich zur Laufzeit das freie SRAM grob anzeigen lassen.

Wichtig ist dabei:

Die **wichtigste Messung** liefert die Arduino-IDE selbst beim Kompilieren.

Dort sieht man typischerweise zwei Angaben:

- **Program storage space**
- **Global variables**

Genau diese beiden Werte sollen die Schüler vergleichen.

---

## Was sollen die Schüler aus diesem Beispiel mitnehmen?

1. Der Arduino Uno besitzt getrennten **Flash** und **SRAM**.
2. Große konstante Tabellen sind sehr gute Kandidaten für den **Programmspeicher**.
3. Auf dem AVR braucht man für solche Flash-Daten einen besonderen Zugriff mit `pgm_read_byte(...)`.
4. `F(...)` ist für feste Texte oft sinnvoll.
5. Ein einzelnes Zeichen wie `'X'` ist kein String und sollte auch nicht als String behandelt werden.
6. Man verschiebt nicht blind alles in den Flash, sondern wählt sinnvoll aus.

---

## Merksätze

- Der Uno hat nur sehr wenig SRAM. Große Tabellen sind dort schnell problematisch.
- Der Flash ist auf dem Uno meist deutlich weniger kritisch als der SRAM.
- `PROGMEM` ist auf AVR ein typisches Werkzeug für große konstante Daten.
- `sizeof(font)` funktioniert auch bei `PROGMEM`.
- Nicht die Größe, sondern der **Zugriff** auf die Daten ändert sich.
- Ein Zeichenliteral wie `'X'` ist etwas anderes als ein Stringliteral wie `"X"`.

---

## Kontrollfragen

1. Warum ist das Font-Array ein guter Kandidat für `PROGMEM`?
2. Warum reicht auf dem Uno ein einfaches `const` für große Tabellen didaktisch oft nicht als Endlösung?
3. Warum braucht man bei `PROGMEM` auf dem AVR `pgm_read_byte(...)`?
4. Worin unterscheiden sich `'X'` und `"X"`?
5. Warum ist `F("...")` vor allem bei längeren Ausgabetexten sinnvoll?
6. Warum sollte man kleine elementare Konstanten nicht unnötig kompliziert behandeln?
