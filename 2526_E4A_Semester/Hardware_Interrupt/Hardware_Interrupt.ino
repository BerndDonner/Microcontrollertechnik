constexpr uint8_t interrupt_pin = 2;
volatile bool event = false;
void taster_gedrueckt();

void setup() {
  Serial.begin(9600);
  pinMode(interrupt_pin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interrupt_pin), taster_gedrueckt, FALLING);
}

void taster_gedrueckt() {
  event = true;
}

void loop() {
  static uint32_t i = 0;
  Serial.println(i);
  i += 1;
  if (event == true) {
    i = 0;
    event = false;
  }
}