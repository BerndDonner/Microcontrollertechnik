# LED-Dimmen mit Timer2 am ATmega328P

## Ausgangssituation

Eine LED soll nicht nur **ein** oder **aus** sein, sondern in ihrer Helligkeit einstellbar werden.

Mit einem Mikrocontroller ist das zunächst nicht ganz offensichtlich, denn ein digitaler Ausgang kennt normalerweise nur zwei Zustände:

- `0 V`
- `5 V`

Trotzdem kann eine LED so angesteuert werden, dass sie **heller** oder **dunkler** wirkt.

Genau das wird in diesem Beispiel mit **Timer2** des ATmega328P gemacht.

## Warum kann man eine LED überhaupt dimmen?

Eine LED reagiert sehr schnell.

Wenn wir sie sehr schnell hintereinander:

- einschalten,
- wieder ausschalten,
- wieder einschalten,
- wieder ausschalten,

... dann erkennt das menschliche Auge oft nicht mehr das schnelle Flackern, sondern nur noch eine **mittlere Helligkeit**.

Das Prinzip heißt:

```text
PWM = Pulsweitenmodulation
```

## Grundidee der PWM

Bei PWM bleibt die Spannung am Ausgang weiterhin digital.

Das Signal ist also nicht „halb 5 Volt“ oder „ein bisschen 5 Volt“, sondern immer nur:

- ganz an
- ganz aus

Der Trick ist die **Zeitverteilung**.

### Beispiel

Wenn das Signal:

- 50 % der Zeit an ist
- 50 % der Zeit aus ist

... dann wirkt die LED ungefähr halb so hell.

Wenn das Signal:

- 90 % der Zeit an ist
- 10 % der Zeit aus ist

... dann wirkt sie deutlich heller.

Wenn das Signal:

- 10 % der Zeit an ist
- 90 % der Zeit aus ist

... dann wirkt sie deutlich dunkler.

## Tastgrad

Der Anteil der Einschaltzeit heißt **Tastgrad** oder auf Englisch **duty cycle**.

Beispiele:

- `0 %`  → LED praktisch aus
- `25 %` → LED eher dunkel
- `50 %` → mittlere Helligkeit
- `75 %` → ziemlich hell
- `100 %` → LED dauerhaft an

## Warum macht man das nicht einfach in `loop()`?

Man könnte versuchen, die LED im Hauptprogramm ständig ein- und auszuschalten.

Das hat aber Nachteile:

- Das Timing wäre ungenau.
- Andere Programmbefehle würden das Blinken beeinflussen.
- Das Hauptprogramm wäre mit dieser Aufgabe unnötig beschäftigt.

Deshalb verwendet man einen **Hardwaretimer**.

## Die Hardwaretimer des ATmega328P

Der ATmega328P besitzt mehrere Timer:

- **Timer0**: 8-Bit
- **Timer1**: 16-Bit
- **Timer2**: 8-Bit

Diese Timer arbeiten in Hardware. Dadurch können sie Signale sehr regelmäßig erzeugen, auch wenn das Hauptprogramm gerade etwas anderes tut.

Für das LED-Dimmen ist das ideal.

## Warum eignet sich Timer2 für PWM?

Timer2 kann verschiedene Betriebsarten.

In diesem Beispiel wird der **Fast-PWM-Modus** verwendet.

Dabei zählt der Timer regelmäßig hoch und erzeugt automatisch ein PWM-Signal an einem passenden Ausgangspin.

Das ist didaktisch schön, weil man gut sieht:

- Der Timer zählt im Hintergrund.
- Die PWM entsteht in Hardware.
- Die CPU muss die LED nicht dauernd selbst umschalten.

## Der Ausgang OC2B

Timer2 ist mit bestimmten Pins des Controllers verknüpft.

Hier wird der Ausgang:

```text
OC2B = PD3
```

verwendet.

Das bedeutet:

- Der Timer erzeugt intern das PWM-Signal.
- Dieses Signal erscheint am Pin **PD3**.
- Die LED muss also passend an diesem Pin angeschlossen sein.

## Der Zählbereich bei Fast PWM

Timer2 ist ein **8-Bit-Timer**.

Er zählt also von:

```text
0 bis 255
```

Das sind insgesamt **256 Schritte**.

Bei Fast PWM mit `TOP = 255` läuft der Timer immer wieder durch diesen Bereich.

Dadurch entsteht ein periodisches Signal.

## Die Rolle von `OCR2B`

Die Variable beziehungsweise das Register `OCR2B` bestimmt, an welcher Stelle innerhalb dieser 256 Schritte der Ausgang umgeschaltet wird.

Damit legt `OCR2B` fest, wie groß der Tastgrad ist.

Im Beispiel steht:

```cpp
OCR2B = 128;
```

Das liegt ungefähr in der Mitte des Bereichs.

Daher entsteht ungefähr ein Tastgrad im mittleren Bereich.

Die LED erscheint also ungefähr mittelhell.

## Warum steht im Kommentar „inverting mode“?

In diesem Sketch wird nicht der normale PWM-Modus verwendet, sondern der **invertierende Modus**.

Das bedeutet vereinfacht:

- Das Signal ist gegenüber dem normalen Verhalten umgedreht.
- Ein größerer Vergleichswert kann dann je nach Verdrahtung zu einer anderen Helligkeitswirkung führen, als man zunächst erwartet.

Darum steht im Code auch der Hinweis, dass `OCR2B = 128` je nach Verdrahtung eher dunkel oder eher aus wirken kann.

## Die PWM-Frequenz

Der Timer läuft hier mit einem **Prescaler von 256**.

Ausgehend von:

```text
f_CPU = 16 MHz
```

wird daraus:

```text
16 MHz / 256 = 62500 Hz
```

Da der Timer pro PWM-Periode 256 Schritte durchläuft, ergibt sich ungefähr:

```text
62500 / 256 ≈ 244 Hz
```

Das ist schnell genug, damit die LED für das menschliche Auge meist nicht sichtbar flackert.

## Warum ist das didaktisch sinnvoll?

Dieses Beispiel zeigt sehr gut:

- Ein Timer kann mehr als nur Zeit messen.
- Hardware kann selbstständig Signale erzeugen.
- PWM ist kein analoges Signal, sondern ein schnelles digitales Signal.
- Über den Tastgrad kann man die Helligkeit einer LED beeinflussen.

## Rolle des Hauptprogramms

In `loop()` passiert hier nichts.

Das ist gerade der interessante Punkt:

Die PWM läuft trotzdem weiter.

Die Helligkeit der LED hängt also nicht davon ab, dass das Hauptprogramm ständig arbeitet.

## Zusammenfassung

Das LED-Dimmen funktioniert nach diesem Prinzip:

1. PD3 wird als Ausgang geschaltet.
2. Timer2 wird in den Fast-PWM-Modus versetzt.
3. Der Timer zählt ständig von `0` bis `255`.
4. `OCR2B` legt den Umschaltpunkt fest.
5. Dadurch entsteht ein PWM-Signal.
6. Die LED wirkt je nach Tastgrad heller oder dunkler.

## Merksätze

- PWM bedeutet Pulsweitenmodulation.
- Eine LED wird beim Dimmen nicht analog angesteuert, sondern schnell ein- und ausgeschaltet.
- Der Tastgrad bestimmt die mittlere Helligkeit.
- Hardwaretimer können PWM selbstständig erzeugen.
- `OCR2B` beeinflusst den Tastgrad.

## Kontrollfragen

1. Warum kann eine LED mit einem digitalen Signal gedimmt werden?
2. Was bedeutet PWM?
3. Welche Aufgabe hat `OCR2B`?
4. Warum ist ein Hardwaretimer für PWM günstiger als eine Lösung in `loop()`?
5. Warum läuft die PWM weiter, obwohl `loop()` leer ist?
