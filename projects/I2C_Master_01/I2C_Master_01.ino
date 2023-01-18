#include <Wire.h>

int slave_address = 43;
int answer_size = 2;

String question = "E4A";

void setup()
{
  Wire.begin();
  Serial.begin(9600);
  Serial.println("I2C Master!");
}

void loop()
{
  delay(50);
  Serial.print("*** Master: ");
  Serial.println("Request data");
  
  Wire.beginTransmission(slave_address);
  Wire.write(question.c_str());
  Wire.endTransmission();
    
  Serial.print("*** Master: ");
  Serial.println(question);

  
/*  
  Serial.print("*** Master: ");
  Serial.println("Receive data");
  
  Wire.requestFrom(slave_address, answer_size);
  
  String answer = "";
  while (Wire.available())
  {
      answer += (char) Wire.read();
  } 
  
  Serial.print("*** Master: ");
  Serial.println(answer);
*/
}
