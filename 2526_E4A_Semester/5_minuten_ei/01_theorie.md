# Timer2 als 5-Minuten-Eieruhr am ATmega328P

## Ausgangssituation

Während der Mikrocontroller im Hauptprogramm rechenintensive Aufgaben erledigt, soll er gleichzeitig als **5-Minuten-Eieruhr** dienen.

In unserem Beispiel sucht der Controller ständig nach Primzahlen. Trotzdem soll nach genau 5 Minuten eine Meldung ausgegeben werden, dass die Eier fertig sind.

Das Ziel ist also:

- Im Hauptprogramm wird weiterhin gerechnet.
- Die Zeitmessung läuft unabhängig davon im Hintergrund.
- Nach 5 Minuten wird ein Alarm ausgelöst.

## Warum nicht einfach mit `delay()` arbeiten?

Eine naheliegende Idee wäre, einfach 5 Minuten zu warten, zum Beispiel mit `delay()`.

Das ist hier aber keine gute Lösung:

- Während `delay()` läuft, steht das Programm praktisch still.
- Die Primzahlsuche könnte in dieser Zeit nicht weiterlaufen.
- Wir wollen aber **gleichzeitig rechnen und Zeit messen**.

Darum verwenden wir einen **Hardwaretimer**.

## Grundidee: Wie misst ein Mikrocontroller Zeit?

Ein Mikrocontroller besitzt selbst keine Uhr im menschlichen Sinn. Er kennt zunächst nur seinen **Takt**.

Unser ATmega328P läuft hier mit:

```text
f = 16 MHz
```

Das bedeutet:

```text
16 000 000 Takte pro Sekunde
```

Die Dauer eines einzelnen Takts ist damit:

```text
T = 1 / f = 1 / 16 000 000 s = 62,5 ns
```

Der Mikrocontroller kann also Zeitunterschiede erfassen, indem er Takte zählt.

## Die Hardwaretimer des ATmega328P

Der ATmega328P besitzt mehrere Hardwaretimer:

- **Timer0**: 8-Bit
- **Timer1**: 16-Bit
- **Timer2**: 8-Bit

Ein 8-Bit-Timer kann von `0` bis `255` zählen, also insgesamt **256 Zustände**.

Ein wichtiger Punkt:

Die Timer arbeiten in Hardware. Sie laufen also weitgehend unabhängig vom normalen Programmablauf. Das Hauptprogramm darf rechnen, Schleifen ausführen oder Funktionen aufrufen, während der Timer im Hintergrund weiterzählt.

## Warum wird hier Timer2 verwendet?

Für unser Beispiel ist Timer2 praktisch:

- er ist relativ einfach zu benutzen,
- er ist ein echter Hardwaretimer,
- und wir geraten nicht direkt in Konflikt mit typischen Arduino-Funktionen von Timer0.

Timer1 wäre auch möglich, ist aber für einen Einstieg oft unnötig komplex.

## Problem 1: Der Timer ist viel zu schnell

Ein Timer zählt zunächst mit dem Systemtakt. Das wäre für eine 5-Minuten-Eieruhr viel zu schnell.

Darum verwendet man einen **Prescaler**.

## Der Prescaler

Ein Prescaler teilt den Takt herunter.

Beispiel:

- Prescaler 8 bedeutet: Nur jeder 8. Takt wird an den Timer weitergegeben.
- Der Timer läuft dadurch 8-mal langsamer.

Beim ATmega328P kann Timer2 unter anderem mit dem Prescaler **1024** betrieben werden.

Dann zählt der Timer nur noch mit:

```text
16 MHz / 1024 = 15625 Hz
```

Das bedeutet:

```text
15625 Zählschritte pro Sekunde
```

## Wie lange dauert ein Overflow?

Timer2 ist ein 8-Bit-Timer. Er zählt also von `0` bis `255`.

Danach springt er wieder auf `0`. Das nennt man **Overflow**.

Ein Overflow dauert also:

```text
256 * 1024 * 62,5 ns = 16,384 ms
```

Oder anders geschrieben:

```text
t_OVF = 16,384 ms
```

## Problem 2: Ein Overflow reicht noch lange nicht

Für unsere Eieruhr brauchen wir:

```text
5 min = 300 s
```

Ein einzelner Overflow dauert aber nur:

```text
16,384 ms = 0,016384 s
```

Das ist viel zu kurz.

Also zählen wir nicht nur die Timerstände, sondern die **Anzahl der Overflows**.

## Wie viele Overflows entsprechen 5 Minuten?

Gesucht ist:

```text
300 s / 0,016384 s ≈ 18310,55
```

Wir verwenden im Beispiel:

```text
OVF_TARGET = 18310
```

Das ergibt:

```text
18310 * 16,384 ms = 299,99104 s
```

Das sind praktisch genau 5 Minuten.

## Wie erfährt das Programm von einem Overflow?

Wenn der Timer überläuft, kann der Mikrocontroller einen **Interrupt** auslösen.

Dann unterbricht die CPU kurz das normale Programm und führt eine spezielle Funktion aus:

- die **Interrupt Service Routine**
- kurz: **ISR**

In dieser ISR erhöhen wir einfach einen Zähler für die Overflows.

Sobald die gewünschte Anzahl erreicht ist, setzen wir eine Variable, die dem Hauptprogramm mitteilt:

```text
Die 5 Minuten sind vorbei.
```

## Warum ist das didaktisch sinnvoll?

Diese Lösung zeigt sehr schön:

- **Hardware arbeitet parallel** zum Hauptprogramm.
- Zeitmessung muss nicht durch blockierende Warteschleifen erfolgen.
- Interrupts sind nützlich, um auf Ereignisse zu reagieren.
- In der ISR sollte man nur sehr wenig machen.

## Warum sollte die ISR kurz bleiben?

Die ISR unterbricht das normale Programm. Deshalb sollte sie möglichst kurz und einfach sein.

In unserem Beispiel macht sie nur Folgendes:

- Overflow mitzählen
- bei Erreichen des Zielwerts ein Flag setzen

Das ist gut, weil:

- die ISR schnell fertig ist,
- das Hauptprogramm kaum gestört wird,
- und der Code übersichtlich bleibt.

## Rolle des Hauptprogramms

Im Hauptprogramm läuft weiterhin die Primzahlsuche.

Zusätzlich wird regelmäßig geprüft, ob das Flag `eier_fertig` gesetzt wurde.

Wenn ja:

- wird der Timer abgeschaltet,
- das Flag zurückgesetzt,
- und eine Meldung auf der seriellen Schnittstelle ausgegeben.

Damit ist die Zeitmessung sauber von der eigentlichen Rechenaufgabe getrennt.

## Zusammenfassung

Die Eieruhr funktioniert nach diesem Prinzip:

1. Timer2 läuft im Normal Mode.
2. Der Prescaler 1024 verlangsamt den Timer.
3. Bei jedem Overflow wird ein Interrupt ausgelöst.
4. Die ISR zählt die Overflows.
5. Nach ungefähr 18310 Overflows sind 5 Minuten vergangen.
6. Das Hauptprogramm erkennt das gesetzzte Flag und gibt den Alarm aus.

## Merksätze

- Ein Mikrocontroller misst Zeit über seinen Takt.
- Hardwaretimer laufen unabhängig vom Hauptprogramm. Ausnahme: Die Timer Manipulation selbst.
- Ein Prescaler macht einen Timer langsamer.
- Ein Overflow-Interrupt meldet, dass der Timer einmal durchgelaufen ist.
- Lange Zeiten erzeugt man oft, indem man viele kurze Timerereignisse mitzählt.

## Kontrollfragen

1. Warum ist `delay()` für dieses Problem keine gute Lösung?
2. Welche Aufgabe hat der Prescaler?
3. Warum reicht ein einzelner Timer2-Overflow nicht für 5 Minuten?
4. Warum ist ein Interrupt hier nützlich?
5. Warum sollte die ISR möglichst kurz bleiben?
