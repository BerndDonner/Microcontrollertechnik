
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
  Serial.begin(9600); //Die Adruino IDE 2.0.3 hat einen Bug: https://github.com/arduino/arduino-ide/pull/1758 (workaround: baud 500000). In Version 2.0.4 behoben.
  const char* text1 = "ü";
  const char* text2 = u8"\u00F6\U0010FFFF"; 
  char ok[] = "\nDrü Chünüsün müt düm Cüntrübüs.";
  Serial.println(ok);
  Serial.println(text1);
  Serial.println(text2);

  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
