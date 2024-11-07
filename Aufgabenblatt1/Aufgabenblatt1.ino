void multi_16(uint16_t* hugo)
{
  (*hugo) = (*hugo) * 16;
}



void setup()
{
  Serial.begin(9600);
  uint16_t a = 0xA35C;
  char* b;
  char c[] = "Chantal";

  // Aufgabe 1

  Serial.println("-- 1.1");
  Serial.println(a, BIN);
  Serial.println("-- 1.2");
  Serial.println(a);
  Serial.println("-- 1.3");
  Serial.println((int16_t) a);
  Serial.println("-- 1.4");
  Serial.println(a>>13, BIN);
  Serial.println("-- 1.5");
  Serial.println(a & 0x000F, BIN); //0b0000'0000'0000'1111
  Serial.println("-- 1.6");
  Serial.println(~a, BIN);
  Serial.println("-- 1.7");
  Serial.println(a & 0x0FF0, BIN); //0b0000'1111'1111'0000
  Serial.println("-- 1.8");
  Serial.println(a | 0x00FF, BIN);
  Serial.println("-- 1.9");
  Serial.println(a ^ 0x8000, BIN); //0b1000'0000'0000'0000

  // Aufgabe 2

  Serial.println("-- 2.1");
  Serial.println(sizeof(a));
  Serial.println(sizeof(b));
  Serial.println("-- 2.2");
  Serial.println(*b);
  Serial.println("-- 2.3");
  Serial.println((uint16_t) &a, HEX); //so kann man Zeiger auf dem Arduino ausgeben lassen
  Serial.println((uint16_t) &b, HEX); //Zeigerausgabe
  Serial.println("-- 2.4");
  b = (char*) &a;                     //
  Serial.println(*b);
  Serial.println("-- 2.5");
  Serial.println((uint8_t) (*(b+1)), HEX); // KEINE Zeigerausgabe, Inhalt!!!
  Serial.println("-- 2.6");
  multi_16(&a);
  Serial.println(a, HEX);

  // Aufgabe 3

  Serial.println("-- 3.1");
  Serial.println(c);
  Serial.println("-- 3.2");
  Serial.println(sizeof(c));     //Null-Terminated Strings: deshalb ein Zeichen mehr als erwartet!
  Serial.println("-- 3.3");
  Serial.println(c[4]);
  Serial.println("-- 3.4");  
  Serial.println((uint16_t) &a, HEX);    //Zeigerausgabe
  Serial.println((uint16_t) &b, HEX);    //Zeigerausgabe
  Serial.println((uint16_t) &c, HEX);    //Zeigerausgabe
  Serial.println("-- 3.4");  
  Serial.println((uint16_t) &c[4], HEX); //Zeigerausgabe
}

void loop()
{
}
