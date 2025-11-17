void setup() {
  Serial.begin(9600);
   int8_t a = 42;
   int8_t* b = &a;
   Serial.println(*b);
   (*b) = 3;
   Serial.println(a);
}

void loop() {
}
