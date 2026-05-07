const char* msg1 = "Ich säge Holz.";
const char* msg2 = "Ich säge Metall.";
const char* msg3 = "Ich säge Hand.";

const char* material[] = {
  msg1, msg1, msg2, msg1, msg2,
  msg2, msg3, msg1, msg2, msg3
};

uint16_t dauer[] = {
  1111, 500, 2700, 2222, 500,
  1777, 2432, 678, 986, 1456
};

constexpr uint8_t ANZAHL = 10;
constexpr uint8_t notaus_pin = 2;

void setup() {
  Serial.begin(9600);
}

void stopp() {
  Serial.println("Säge wird sofort gestoppt");
  Serial.flush();
  abort();
}

void loop() {
  for (uint8_t i = 0; i < ANZAHL; i++) {
    Serial.println(material[i]);
    delay(dauer[i]);
  }
}
