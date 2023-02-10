void setup() {
  Serial.begin(9600);
  float a = 432.59;
  float b = (a-(int)a)*100;
  uint32_t* c = (uint32_t*) &b;
  uint32_t d = 0b1010111111111110100000;


  Serial.println(  b,8  );
  Serial.println(*c, BIN);
  Serial.println(  d  );
  Serial.println(__FLT_EPSILON__, 8);
  Serial.println(__DBL_EPSILON__, 8);
 
  // put your setup code here, to run once:

}

void loop() {

}
