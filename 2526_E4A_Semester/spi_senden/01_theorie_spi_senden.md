# SPI-Senden an eine LED-Platine mit dem ATmega328P

## Ausgangssituation

Ein Mikrocontroller soll Daten nicht nur an einzelne Pins ausgeben, sondern seriell an eine externe Schaltung übertragen.

In unserem Beispiel arbeitet der ATmega328P als **SPI-Master**. Er sendet Daten an eine LED-Platine, die diese Daten verarbeitet und dadurch ein sichtbares LED-Muster erzeugt.

Das Ziel ist also:

- Der Mikrocontroller sendet ein Byte seriell an die Platine.
- Die Platine reagiert auf diese Daten.
- Die LEDs machen die Übertragung sichtbar.
- Zusätzlich soll deutlich werden, welche Rolle die Leitung **SS** spielt.

## Warum eignet sich SPI für dieses Beispiel?

SPI ist ein sehr verbreitetes Bussystem in der Mikrocontrollertechnik.

Es ist für den Einstieg gut geeignet, weil die Grundstruktur klar ist:

- ein **Master**
- ein **Slave**
- klar benannte Leitungen
- eine streng getaktete Übertragung

Gerade mit einer LED-Platine ist das didaktisch praktisch, weil die Übertragung nicht nur abstrakt bleibt, sondern direkt sichtbar wird.

## Die wichtigen SPI-Leitungen in diesem Beispiel

Wir konzentrieren uns hier zunächst nur auf die **Sendeseite**.

Verwendet werden diese Signale:

- **MOSI**  
  Über diese Leitung sendet der Master die Daten zum Slave.

- **SCLK**  
  Diese Leitung liefert den Takt. Die Datenübertragung erfolgt also nicht beliebig schnell, sondern Schritt für Schritt im Rhythmus dieses Takts.

- **SS**  
  Diese Leitung markiert, wann die Übertragung aktiv ist.

Außerdem braucht die Schaltung natürlich:

- **5 V**
- **GND**

Die Leitung **MISO** gibt es ebenfalls, sie steht aber in dieser Stunde noch nicht im Mittelpunkt.

## Warum wird Pin 10 als SS verwendet?

Beim Arduino Uno bilden die Pins

```text
13 = SCLK
12 = MISO
11 = MOSI
10 = SS
```

den klassischen SPI-Pinblock.

Für unser Beispiel wäre als Master prinzipiell auch ein anderer Ausgangspin möglich.

Trotzdem ist **Pin 10** didaktisch sinnvoll, weil:

- die Schüler gleich den typischen SPI-Pinblock kennenlernen,
- die Verdrahtung übersichtlich bleibt,
- und spätere Erweiterungen leichter fallen.

## Grundidee der seriellen Übertragung

Ein Byte besteht aus **8 Bits**.

Bei SPI werden diese Bits nacheinander über **MOSI** übertragen. Gleichzeitig gibt der Master auf **SCLK** den Takt vor.

Der Slave übernimmt die Daten also nicht irgendwie „auf einmal“, sondern Bit für Bit im Takt des Masters.

Genau dadurch eignet sich SPI gut für digitale Baugruppen, die Daten seriell annehmen sollen.

## Was passiert im Slave?

Für die heutige Stunde betrachten wir die LED-Platine zunächst als **Black Box**.

Das bedeutet:

- Außen interessiert uns vor allem die SPI-Schnittstelle.
- Innen muss die Platine die ankommenden Bits irgendwie verarbeiten und auf die LEDs bringen.
- Dafür wird intern typischerweise eine Art Schieberegister-Logik verwendet.

Für das heutige Lernziel reicht aber die äußere Sicht:

```text
Master sendet Daten → Platine verarbeitet sie → LEDs zeigen das Ergebnis
```

## Warum ist SS wichtig?

Die Leitung **SS** zeigt dem Slave, wann eine Übertragung aktiv ist.

Das ist wichtig, weil dadurch klar wird:

- Jetzt gehören die kommenden Takte und Daten zu dieser Übertragung.
- Der Slave soll genau in diesem Zeitraum auf MOSI und SCLK reagieren.

Didaktisch ist das besonders wichtig, weil man daran erkennt:

```text
SPI besteht nicht nur aus Daten und Takt, sondern auch aus einer klaren Rahmensteuerung.
```

## Zwei Arten der Übertragung im Sketch

Der Sketch enthält zwei Betriebsarten.

### 1. Einzelübertragung

Hier wird für **jedes Byte** eine eigene Übertragung gestartet und beendet.

Das ist für den Einstieg gut, weil man klar sieht:

- SS wird aktiv,
- ein Byte wird gesendet,
- SS wird wieder deaktiviert.

### 2. Burst-Übertragung

Hier bleibt **SS über mehrere Bytes hinweg aktiv**.

Das zeigt eine wichtige Eigenschaft von SPI:

Eine Übertragung muss nicht aus nur einem einzigen Byte bestehen.

Stattdessen kann ein ganzer Datenblock in einem zusammenhängenden Rahmen übertragen werden.

## Warum ist der Burst-Mode didaktisch interessant?

Im Burst-Mode wird deutlich:

- Der Bus kann eine ganze Folge von Bytes transportieren.
- SS muss nicht nach jedem einzelnen Byte umgeschaltet werden.
- SPI eignet sich deshalb auch für größere Datenmengen.

Gerade das ist eine wichtige Einsicht:

```text
SPI überträgt nicht nur einzelne Zahlen, sondern ganze Datenfolgen.
```

## Warum werden hier sichtbare Bitmuster verwendet?

Damit man die Wirkung der Übertragung direkt erkennt, werden einfache Byte-Muster an die Platine gesendet.

Zum Beispiel:

```text
00000000
00000001
00000111
00011110
01111100
11111111
11110000
11000000
```

Die LEDs zeigen dadurch ein gut verfolgbares, aber nicht streng symmetrisches Muster.

So bleibt die Aufmerksamkeit bei der Datenübertragung und nicht bei einer zusätzlichen Decodierung von ASCII-Zeichen oder ähnlichen Inhalten.

## Rolle von `SPI.h`

In Arduino könnte man SPI auch direkt über Register konfigurieren.

Für den Einstieg ist hier aber die Bibliothek

```cpp
#include <SPI.h>
```

günstig.

Sie übernimmt die grundlegende Initialisierung und stellt mit

```cpp
SPI.begin();
SPI.transfer(...);
```

eine einfache Schnittstelle bereit.

So kann man sich im Unterricht zuerst auf das eigentliche Busprinzip konzentrieren.

## Rolle des Hauptprogramms

In `loop()` wird nur zwischen zwei vorbereiteten Sendefunktionen gewählt.

Der Schwerpunkt liegt also nicht auf komplizierter Programmlogik, sondern auf der eigentlichen SPI-Übertragung.

Das hält den Sketch kurz und gut lesbar.

## Zusammenfassung

Das SPI-Senden an die LED-Platine funktioniert nach diesem Prinzip:

1. Der Arduino arbeitet als SPI-Master.
2. Über **MOSI** werden Datenbits an den Slave geschickt.
3. **SCLK** liefert den Takt.
4. **SS** markiert die aktive Übertragung.
5. Die Platine verarbeitet die empfangenen Daten.
6. Die LEDs machen das Ergebnis sichtbar.

## Merksätze

- SPI sendet Daten seriell.
- MOSI liefert die Datenbits.
- SCLK taktet die Übertragung.
- SS markiert, wann eine Übertragung aktiv ist.
- Ein SPI-Slave verarbeitet die empfangenen Bits intern weiter.
- Im Burst-Mode können mehrere Bytes in einer zusammenhängenden Übertragung gesendet werden.

## Kontrollfragen

1. Welche Aufgabe hat MOSI?
2. Welche Aufgabe hat SCLK?
3. Warum ist SS in diesem Beispiel wichtig?
4. Was ist der Unterschied zwischen Einzelübertragung und Burst-Übertragung?
5. Warum ist es sinnvoll, die LED-Platine heute zunächst als Black Box zu betrachten?
