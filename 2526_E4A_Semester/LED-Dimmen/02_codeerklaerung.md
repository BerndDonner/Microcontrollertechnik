# Codeerklärung zum LED-Dimmen mit Timer2

In dieser Datei wird die **Timer- und PWM-Logik** des Sketches Schritt für Schritt erklärt.

Der Sketch ist bewusst sehr kurz gehalten. Gerade deshalb eignet er sich gut, um die Grundidee von **PWM mit Hardwaretimer** zu verstehen.

---

## 1. Die `setup()`-Funktion

```cpp
void setup() {
  DDRD |= (1 << PD3); // PD3 = OC2B als Ausgang

  // Timer2: Fast PWM, TOP = 255, inverting mode
  TCCR2A = (1 << WGM20) | (1 << WGM21) | (1 << COM2B1) | (1 << COM2B0);
  TCCR2B = (1 << CS22) | (1 << CS21); // Prescaler 256

  OCR2B = 128; // je nach Verdrahtung sehr dunkel / aus
}
```

Die gesamte eigentliche Arbeit passiert hier in `setup()`.

Danach läuft die PWM automatisch weiter.

---

## 2. PD3 als Ausgang

```cpp
DDRD |= (1 << PD3);
```

### Bedeutung

Hier wird der Pin **PD3** als Ausgang geschaltet.

### Warum genau PD3?

PD3 ist beim ATmega328P mit der Timerfunktion **OC2B** verbunden.

Das ist wichtig, weil Timer2 sein PWM-Signal nicht an beliebigen Pins ausgeben kann, sondern nur an den dafür vorgesehenen Compare-Ausgängen.

In diesem Beispiel soll das PWM-Signal also an **PD3** erscheinen.

### Warum mit `|=`?

Mit

```cpp
DDRD |= (1 << PD3);
```

wird nur das Bit für PD3 gesetzt.

Andere Bits im Register `DDRD` bleiben unverändert.

Das ist oft sauberer, als das gesamte Register komplett neu zu beschreiben.

---

## 3. Die Waveform-Generation-Bits

```cpp
TCCR2A = (1 << WGM20) | (1 << WGM21) | (1 << COM2B1) | (1 << COM2B0);
```

In dieser Zeile werden gleich mehrere Einstellungen vorgenommen.

Wir trennen sie deshalb gedanklich auf.

### Die Bits `WGM20` und `WGM21`

Diese Bits wählen den Betriebsmodus des Timers.

Hier gilt:

```text
WGM21 = 1
WGM20 = 1
WGM22 = 0
```

Das entspricht bei Timer2 dem Modus:

```text
Fast PWM, TOP = 255
```

### Bedeutung von Fast PWM

Der Timer zählt schnell von `0` bis `255`.

Danach beginnt er wieder bei `0`.

Während dieses Zählvorgangs wird automatisch das PWM-Signal erzeugt.

---

## 4. Die Compare-Output-Bits für OC2B

In derselben Zeile werden auch diese Bits gesetzt:

```cpp
(1 << COM2B1) | (1 << COM2B0)
```

### Bedeutung

Diese beiden Bits legen fest, wie sich der Ausgang **OC2B** beim PWM-Betrieb verhalten soll.

Hier wird der **invertierende Modus** gewählt.

### Was bedeutet „invertierend“?

Vereinfacht gesagt wird das PWM-Signal gegenüber dem nicht-invertierenden Standardfall umgedreht.

Dadurch kann die Helligkeitswirkung je nach Schaltung anders sein, als man es zuerst erwartet.

Deshalb steht auch im Kommentar:

```cpp
OCR2B = 128; // je nach Verdrahtung sehr dunkel / aus
```

Ob eine größere Zahl zu mehr oder zu weniger sichtbarer Helligkeit führt, hängt hier also auch von der Verdrahtung der LED ab.

---

## 5. Der Prescaler

```cpp
TCCR2B = (1 << CS22) | (1 << CS21); // Prescaler 256
```

### Bedeutung

Mit den `CS`-Bits wird die Taktquelle beziehungsweise der Prescaler eingestellt.

Hier gilt:

```text
CS22 = 1
CS21 = 1
CS20 = 0
```

Für Timer2 bedeutet das:

```text
Prescaler = 256
```

### Warum braucht man den Prescaler?

Ohne Prescaler würde der Timer direkt mit dem CPU-Takt laufen.

Das wäre hier unnötig schnell.

Der Prescaler verlangsamt den Timer, sodass eine sinnvolle PWM-Frequenz entsteht.

---

## 6. Die PWM-Frequenz grob berechnen

Gegeben:

```text
f_CPU = 16 MHz
Prescaler = 256
TOP = 255
```

Zuerst wird der CPU-Takt geteilt:

```text
16 000 000 / 256 = 62500 Hz
```

Der Timer benötigt 256 Schritte pro Periode:

```text
62500 / 256 ≈ 244 Hz
```

Die PWM-Frequenz liegt also ungefähr bei:

```text
244 Hz
```

Das ist für eine LED in der Regel ausreichend schnell.

---

## 7. Das Register `OCR2B`

```cpp
OCR2B = 128;
```

### Bedeutung

`OCR2B` ist das **Output Compare Register** für den Ausgang **OC2B**.

Es legt fest, bei welchem Zählerstand innerhalb der PWM-Periode ein Umschaltvorgang stattfindet.

Damit beeinflusst es direkt den Tastgrad.

### Warum ist `128` interessant?

Der Wertebereich reicht bei einem 8-Bit-Timer ungefähr von:

```text
0 bis 255
```

`128` liegt ungefähr in der Mitte.

Darum erhält man einen mittleren Tastgrad.

Im nicht-invertierenden Modus würde man das oft als ungefähr 50 % verstehen.

Im invertierenden Modus muss man zusätzlich beachten, dass das Signal umgedreht ist.

---

## 8. Warum ist `loop()` leer?

```cpp
void loop() {
}
```

Das wirkt zuerst vielleicht seltsam.

Didaktisch ist es aber sehr nützlich.

Es zeigt nämlich:

- Die PWM wird vollständig von der Hardware erzeugt.
- Das Hauptprogramm muss nichts weiter tun.
- Der Timer arbeitet selbstständig weiter.

Genau daran erkennt man die Stärke von Hardware-PWM.

---

## 9. Was würde passieren, wenn man `OCR2B` verändert?

Wenn man `OCR2B` im laufenden Betrieb verändert, ändert sich der Tastgrad.

Dadurch wird die LED heller oder dunkler.

Beispiele:

- kleiner Wert → je nach Modus und Verdrahtung eher heller oder dunkler
- mittlerer Wert → mittlere Helligkeit
- großer Wert → je nach Modus und Verdrahtung eher dunkler oder heller

Bei diesem Sketch muss man wegen des **invertierenden Modus** besonders genau beobachten, wie sich die Helligkeit tatsächlich verhält.

---

## 10. Was sollen Sie aus diesem Beispiel mitnehmen?

- Ein Timer kann PWM in Hardware erzeugen.
- PD3 ist hier der PWM-Ausgang `OC2B`.
- `WGM20` und `WGM21` schalten den Fast-PWM-Modus ein.
- `COM2B1` und `COM2B0` wählen den invertierenden Ausgangsmodus.
- `CS22` und `CS21` stellen den Prescaler 256 ein.
- `OCR2B` beeinflusst den Tastgrad und damit die wahrgenommene Helligkeit.
- `loop()` darf leer sein, weil die Hardware die Arbeit übernimmt.

---

## Denkfragen

1. Warum muss PD3 als Ausgang gesetzt werden?
2. Welche Aufgabe haben die Bits `WGM20` und `WGM21`?
3. Warum ist `OCR2B` für die Helligkeit wichtig?
4. Welche Wirkung hat der Prescaler?
5. Warum ist es lehrreich, dass `loop()` in diesem Beispiel leer bleibt?
