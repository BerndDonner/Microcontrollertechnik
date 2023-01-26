//Array Dimensionen werdenvon aussen nach innen angegeben
char text [5][4]= {
  {'a', 'b', 'c', 'd'},  // 0->4     1->3    2->2    i->4-i
  {'A', 'B', 'C', 'D'},
  {'1', '2', '3', '4'},
  {'w', 'x', 'y', 'z'},
  {'W', 'X', 'Y', 'Z'},
};


void setup() {
  Serial.begin(9600);

  //Zeiger und Arrays sind ganz eng verwandt
  char* text_view1 = text[0]; //text_view1 Zeiger zeigt 
  char* text_view2 = &text[0][0]; //Adresse von text[0][0]
  Serial.print("1. Zeichen: ");
  Serial.println(text[1][4]); //erster Index startet immer bei 0, 0
  Serial.print("2. Zeichen: ");
  Serial.println(text[0][19]); //2-dimensionales Array als 1-dimensionales Array
  Serial.print("3. Zeichen: ");
  Serial.println(*(*(text+1)+4)); //out of bounds - the way to hell
  Serial.print("4. Zeichen: ");
  Serial.println(text_view2[19]); //erster Index startet immer bei 0, 0
  Serial.print("5. Zeichen: ");
  Serial.println(*(text_view2+19)); //erster Index startet immer bei 0, 0
}


void loop()
{ 
}
