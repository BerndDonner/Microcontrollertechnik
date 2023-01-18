#include <Wire.h>


int slave_address = 43;

String answer = "Ok";

void receiveEvent(int read_bytes)
{
  String question = "";
  while (Wire.available())
  {
      question += (char) Wire.read();
  }
  Serial.print("--- Slave:  ");
  Serial.println("Receive event");
  Serial.print("--- Slave:  ");
  Serial.println(question);
}

void requestEvent() {
  Wire.write(answer.c_str());  

  Serial.print("--- Slave:  ");
  Serial.println("Request event");
  Serial.print("--- Slave:  ");
  Serial.println(answer);
}

void setup()
{
  Wire.begin(slave_address);
  Wire.onRequest(requestEvent); 
  Wire.onReceive(receiveEvent);

  Serial.begin(9600);
  Serial.println("I2C Slave!");
}

void loop()
{
  delay(50);
}
