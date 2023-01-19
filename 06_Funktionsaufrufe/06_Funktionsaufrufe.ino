//&: Aus Inhalt wird Adresse
//*: Aus Adresse wird Inhalt

int8_t quadrat(int8_t x) //Call by Value
{
  x = x*x;
  return x;
}


void quadrat_neu(int8_t* addr) //Call by Reference
{
  (*addr) = (*addr)*(*addr);
}

void setup() {
  Serial.begin(9600);
  int8_t a = 7;
  int8_t b = quadrat(a);
  Serial.println(a);
  quadrat_neu(&a);
  Serial.println(a);


}

void loop() {
  // put your main code here, to run repeatedly:

}
