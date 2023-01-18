#include <CapacitiveSensor.h>
CapacitiveSensor Sensor = CapacitiveSensor(4, 6);
long val;
const long schwellwert_high = 20000;
const long schwellwert_low  = 4000;
int pos = 0;
#define led 13

void setup()
{
  Serial.begin(9600);
  pinMode(led, OUTPUT);
}

void loop()
{
  val = Sensor.capacitiveSensor(30);
  Serial.println(val);
  if (val >= schwellwert_high && pos == 0) {
    digitalWrite(led, HIGH);
    pos = 1;
    delay(500);
  }

  else if (val <= schwellwert_low && pos == 1) {
    digitalWrite(led, LOW);
    pos = 0;
    delay(500);
  }

  delay(100);
}
