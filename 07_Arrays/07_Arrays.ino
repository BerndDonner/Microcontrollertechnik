//Array Dimensionen werden von aussen nach innen angegeben
char text [5][4] = {
  {'a', 'b', 'c', 'd'},  // 0->4     1->3    2->2    i->4-i
  {'A', 'B', 'C', 'D'},
  {'1', '2', '3', '4'},
  {'w', 'x', 'y', 'z'},
  {'W', 'X', 'Y', 'Z'},
};

char text2 [5][4];


//Die Implementation dieser Funktion ist nicht ganz einfach und ist _nicht_ schulaufgabenrelevant!

void ausgabe(void* ptr, uint8_t im, uint8_t jm)
{
  char (*text)[jm] = ptr;

  for (uint8_t i = 0; i < im; i++)
  {
    for (uint8_t j = 0; j < jm; j++)
    {
      Serial.print(text[i][j]); 
      Serial.print("\t");
    }
    Serial.println();
  }
}

/*
void ausgabe(char* text, uint8_t im, uint8_t jm)
{
  for (uint8_t i = 0; i < im; i++)
  {
    for (uint8_t j = 0; j < jm; j++)
    {
      Serial.print(*(text + i * jm + j)); //<--- Die Zeile hat es in sich!
      Serial.print("\t");
    }
    Serial.println();
  }
}
*/

void setup()
{
  Serial.begin(9600);

  Serial.println("Original Array: ");
  ausgabe(text, 5, 4);

  for (uint8_t i = 0; i < 5; i++)
  {
    for (uint8_t j = 0; j < 4; j++)
    {
      text2[4 - i][j] = text[i][j];
    }
  }
  Serial.println("Modifiziertes Array: ");
  ausgabe(text2, 5, 4);
}




void loop() {
}
