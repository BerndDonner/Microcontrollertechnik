#include "donner.h"

void uebungung1_10() {
  Serial.println("1.te Aufgabe:");
  Serial.println(47, HEX);
  Serial.println("2.te Aufgabe:");
  Serial.println(0xffea, DEC);
  Serial.println("3.te Aufgabe:");
  Serial.println(0xff);
  Serial.println("4.te Aufgabe:");
  Serial.println(0xffff);
  Serial.println("5.te Aufgabe:");
  Serial.println(0xffffffff);
  Serial.println("6.te Aufgabe:");
  Serial.println(sizeof(float));
  Serial.println("7.te Aufgabe:");
  Serial.println(sizeof(double));
  Serial.println("8.te Aufgabe:");
  Serial.println(0xfa, BIN);
  Serial.println((uint8_t) ~0xfa, BIN);
  Serial.println("9.te Aufgabe:");
  Serial.println(69, BIN);
  Serial.println((uint8_t) ~69, BIN);
  Serial.println("10.te Aufgabe:");
  Serial.println(~69 + 1);
  Serial.println((uint8_t) ~69 + 1, BIN);
}

void setup() {
  Serial.begin(9600);
//  uebungung1_10();

  DDRD & ~((1 << PD2) | (1 << PD3)); //<--- TODO

  Serial.print("PD2: ");
  Serial.println(PD2);

  Serial.print("PD3: ");
  Serial.println(PD3);
  
  Serial.print("1:\t\t");
  printBin((uint8_t) 1);
  
  Serial.print("1 << PD2:\t");
  printBin((uint8_t) (1 << PD2));
 
  Serial.print("1 << PD3:\t");
  printBin((uint8_t) (1 << PD3));

  Serial.print("(1 << PD2) | (1 << PD3):\t");
  printBin((uint8_t) ((1 << PD2) | (1 << PD3)));

  Serial.print("~(1 << PD2) | (1 << PD3):\t");
  printBin((uint8_t) (~((1 << PD2) | (1 << PD3))));

  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);

  Serial.print("DDRD: \t\t");
  printBin((uint8_t) DDRD);

  DDRD = DDRD & ~((1 << PD2) | (1 << PD3)); //<--- TODO

  Serial.print("DDRD: \t\t");
  printBin((uint8_t) DDRD);
 

  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
