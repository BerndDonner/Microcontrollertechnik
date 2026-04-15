# Codeerklärung zum SPI-Senden an eine LED-Platine

In dieser Datei wird die **SPI-Logik** des Sketches Schritt für Schritt erklärt.

Der Sketch ist bewusst kurz gehalten. Gerade deshalb eignet er sich gut, um die Grundidee der seriellen Übertragung zwischen Master und Slave zu verstehen.

---

## 1. Einbinden der SPI-Bibliothek

```cpp
#include <SPI.h>
```

### Bedeutung

Diese Bibliothek stellt die wichtigsten SPI-Funktionen für Arduino bereit.

Dadurch müssen wir die SPI-Hardware des Controllers nicht von Hand über viele Register konfigurieren.

Für den Einstieg ist das didaktisch sinnvoll, weil wir uns auf die äußere Schnittstelle konzentrieren können:

- **MOSI**
- **SCLK**
- **SS**

Die interne Verarbeitung im Slave spielt heute noch keine Hauptrolle.

---

## 2. Die Konstanten

```cpp
constexpr uint8_t SS_PIN = 10;
constexpr bool BURST_MODE = true;
```

### `SS_PIN`

Hier wird festgelegt, dass **Pin 10** als SS-Leitung verwendet wird.

Das passt zum klassischen SPI-Pinblock des Arduino Uno:

```text
13 = SCLK
12 = MISO
11 = MOSI
10 = SS
```

### `BURST_MODE`

Mit dieser Konstante kann bequem zwischen zwei Betriebsarten umgeschaltet werden:

- `true`  → Burst-Übertragung
- `false` → Einzelübertragung

Didaktisch ist das praktisch, weil derselbe Sketch für beide Demonstrationen benutzt werden kann.

---

## 3. Das Datenarray

```cpp
const uint8_t frames[] = {
  0b00000000,
  0b00000001,
  0b00000111,
  0b00011110,
  0b01111100,
  0b11111111,
  0b11110000,
  0b11000000
};
```

### Bedeutung

Dieses Array enthält die Byte-Muster, die an die LED-Platine gesendet werden.

Die Platine setzt diese Daten so um, dass daraus sichtbare LED-Zustände entstehen.

### Warum gerade diese Muster?

Die Folge ist:

- nicht streng symmetrisch,
- nicht chaotisch,
- und für das Auge gut verfolgbar.

Dadurch lässt sich die Wirkung der Datenübertragung leicht beobachten.

---

## 4. Die Funktion `sendSingleFrames()`

```cpp
void sendSingleFrames()
{
  for (uint8_t i = 0; i < sizeof(frames); ++i)
  {
    digitalWrite(SS_PIN, LOW);
    SPI.transfer(frames[i]);
    digitalWrite(SS_PIN, HIGH);
    delay(250);
  }
}
```

Diese Funktion sendet die Muster **einzeln**.

### Die Schleife

```cpp
for (uint8_t i = 0; i < sizeof(frames); ++i)
```

Die Schleife läuft durch alle Einträge des Arrays.

Da `frames` aus `uint8_t`-Werten besteht, ist `sizeof(frames)` hier genau die Anzahl der gespeicherten Bytes.

### `digitalWrite(SS_PIN, LOW);`

Damit wird die SS-Leitung aktiv.

Didaktisch bedeutet das hier:

```text
Jetzt beginnt diese Übertragung.
```

### `SPI.transfer(frames[i]);`

Hier wird genau **ein Byte** übertragen.

Die Bits dieses Bytes werden seriell über MOSI ausgegeben und mit dem SCLK des Masters getaktet.

### `digitalWrite(SS_PIN, HIGH);`

Damit wird die Übertragung wieder beendet.

In dieser Betriebsart hat also jedes einzelne Byte seinen eigenen Übertragungsrahmen.

### `delay(250);`

Die Pause dient nur der Beobachtung.

Ohne diese Verzögerung würde das Muster zu schnell wechseln.

---

## 5. Die Funktion `sendBurstFrames()`

```cpp
void sendBurstFrames()
{
  digitalWrite(SS_PIN, LOW);

  for (uint8_t i = 0; i < sizeof(frames); ++i)
  {
    SPI.transfer(frames[i]);
    delay(150);
  }

  digitalWrite(SS_PIN, HIGH);
  delay(1000);
}
```

Diese Funktion sendet mehrere Bytes in einer zusammenhängenden Übertragung.

### `digitalWrite(SS_PIN, LOW);`

Hier wird SS nur **ein einziges Mal** zu Beginn aktiv gesetzt.

### Die Schleife mit `SPI.transfer(...)`

Nun werden alle Muster nacheinander übertragen, ohne SS dazwischen zurückzunehmen.

Genau das ist die Kernaussage des Burst-Mode:

- Eine SPI-Übertragung kann aus mehreren Bytes bestehen.
- SS muss nicht nach jedem Byte umgeschaltet werden.

### `digitalWrite(SS_PIN, HIGH);`

Erst nach allen Bytes wird die Übertragung abgeschlossen.

### `delay(1000);`

Diese Pause sorgt dafür, dass das Ende einer kompletten Musterfolge gut erkennbar bleibt.

---

## 6. Die `setup()`-Funktion

```cpp
void setup()
{
  pinMode(SS_PIN, OUTPUT);
  digitalWrite(SS_PIN, HIGH);
  SPI.begin();
}
```

Hier wird die Hardware vorbereitet.

### `pinMode(SS_PIN, OUTPUT);`

Pin 10 wird als Ausgang gesetzt.

Das ist wichtig, weil der Arduino in diesem Beispiel als **SPI-Master** arbeitet und die SS-Leitung aktiv steuern soll.

### `digitalWrite(SS_PIN, HIGH);`

Vor dem Beginn soll SS inaktiv sein.

So startet das Programm in einem sauberen Grundzustand.

### `SPI.begin();`

Mit diesem Aufruf wird die SPI-Schnittstelle initialisiert.

Danach können Übertragungen mit `SPI.transfer(...)` gestartet werden.

---

## 7. Die `loop()`-Funktion

```cpp
void loop()
{
  if (BURST_MODE)
  {
    sendBurstFrames();
  }
  else
  {
    sendSingleFrames();
  }
}
```

### Bedeutung

Hier wird entschieden, welche der beiden Demonstrationen ausgeführt werden soll.

Ist `BURST_MODE` auf `true` gesetzt, läuft die Burst-Übertragung.

Andernfalls wird die Einzelübertragung verwendet.

### Warum ist das didaktisch nützlich?

So bleibt alles in **einem einzigen Sketch**.

Gerade im Unterricht ist das angenehm, weil man nicht ständig zwischen verschiedenen Dateien wechseln muss.

---

## 8. Was zeigt der Sketch inhaltlich?

Der Sketch zeigt zwei zentrale Gedanken:

### Erste Aussage

Ein Byte kann seriell vom Master an einen Slave übertragen werden.

### Zweite Aussage

Die Rolle von **SS** hängt nicht davon ab, dass immer nur ein einziges Byte gesendet wird.

Vielmehr kann SS auch einen längeren zusammenhängenden Übertragungsrahmen markieren.

Gerade diese zweite Aussage ist wichtig, wenn man später größere Datenmengen übertragen will.

---

## 9. Was passiert im Slave?

Für die heutige Stunde genügt die äußere Sicht:

- Der Slave empfängt Daten.
- Der Slave verarbeitet sie intern.
- Die LEDs machen das Ergebnis sichtbar.

Im Inneren arbeitet dabei typischerweise eine Schieberegister-Logik oder etwas funktional Ähnliches. Das ist heute aber nicht der eigentliche Schwerpunkt.

Didaktisch ist es daher sinnvoll, den Slave zunächst als **Black Box mit SPI-Schnittstelle** zu betrachten.

---

## 10. Was sollen Sie aus diesem Beispiel mitnehmen?

- `SPI.begin()` startet die SPI-Schnittstelle.
- `SPI.transfer(...)` sendet ein Byte seriell.
- `SS_PIN = 10` orientiert sich am typischen SPI-Pinblock des Arduino Uno.
- Das Array `frames[]` enthält die sichtbaren Sendemuster.
- `sendSingleFrames()` zeigt Einzelübertragungen.
- `sendBurstFrames()` zeigt mehrere Bytes innerhalb eines gemeinsamen Übertragungsrahmens.
- Für den Einstieg genügt es, den Slave über seine äußere SPI-Schnittstelle zu verstehen.

---

## Denkfragen

1. Warum ist `SS_PIN` hier auf 10 gesetzt?
2. Welche Aufgabe hat `SPI.transfer(...)`?
3. Was ist der Unterschied zwischen `sendSingleFrames()` und `sendBurstFrames()`?
4. Warum bleibt SS im Burst-Mode länger aktiv?
5. Warum ist es für den Unterricht sinnvoll, den Slave zunächst als Black Box zu behandeln?
