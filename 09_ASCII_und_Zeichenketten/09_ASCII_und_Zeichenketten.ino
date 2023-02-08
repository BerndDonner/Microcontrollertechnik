
/* ----------------------------- NUR für diejenigen, die von ASCII unterforder sind!!! ---------------------------------------- */

 //utf8 Ein codepoint ist ein Zeichen auf dem Monitor. Ein utf8 codepoint kann aus 1-4 bytes bestehen.
 //Weiterhin ist char = byte. Aber ein char ist eventuell nurmehr ein Teil eines Zeichens auf den Monitor.
 //Unvollständige utf8 Zeichen werden mit � dargestellt.
 //Ist die Eingabedatei utf8-codiert und die Ausgabe arbeitet mit utf8 so laufen die utf8 Zeichen eigentlich problemlos durch!
 //Aber es ist gut möglich dass der Font das utf8 Zeichen nicht darstellen kann. Es gibt kaum Fonts, die alle utf8 Zeichen darstellen können.
 //Syntaktisch korrekte utf8 Zeichen, für die kein Fontzeichen hinterlegt ist, werden mit 􏿿 dargestellt.
 // \u für 1-2byte codepoints es müssen immer 2 bytes angegeben werden
 // \U für 3-4byte codepoints es müssen immer 4 bytes angegeben werden

void setup()
{
  Serial.begin(9600); //Die aktuelle adruino IDE 2.0.3 hat einen Bug: https://github.com/arduino/arduino-ide/pull/1758
  const char zeichen1 = 'a';

  /* Diese Zeilen kann man ohne Schwierigkeiten ausbauen,um eine ASCII-Tabelle zu generieren! */

  Serial.print("\nZeichen\tDEC\tHEX\n");
  Serial.print(zeichen1);
  Serial.print("\t");
  Serial.print((int) zeichen1);
  Serial.print("\t0x");
  Serial.print((int) zeichen1, HEX);
  Serial.print("\n");

  const char zeichen2 = 98;  //Das ist möglich

  Serial.print(zeichen2);
  Serial.print("\t");
  Serial.print((int) zeichen2);
  Serial.print("\t0x");
  Serial.print((int) zeichen2, HEX);
  Serial.print("\n");
  
  const char zeichen3 = 'a' + 2; //Auch das geht
  
  Serial.print(zeichen3);
  Serial.print("\t");
  Serial.print((int) zeichen3);
  Serial.print("\t0x");
  Serial.print((int) zeichen3, HEX);
  Serial.print("\n\n\n");


  char text1[] = "a";  //Das ist kein Zeichen sondern eine Zeichenkette! Wie groß bin ich?
  const char* text2 = "Auch ich bin ein String!"; 
  char text3[] = "John Wayne schiesst schneller\0 als er denkt.";
  Serial.println(text1);
  Serial.println(sizeof(text1)); //Das geht nur bei char-arrays nicht bei char-pointern!!

  Serial.println(text2);
  Serial.println(sizeof(text2)); //hier wird leider nur die größe des Zeigers ausgegeben. Nicht die Größe des Strings!

  Serial.println(text3);
  Serial.println(sizeof(text3)); //Das geht nur bei char-arrays nicht bei char-pointern!!

  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
