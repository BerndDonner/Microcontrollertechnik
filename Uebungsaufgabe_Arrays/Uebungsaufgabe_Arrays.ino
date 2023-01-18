// Aufgabenstellungen:
// 1.) Fülle ein um 90° gedrehtes Array temps_rot[4][16]
// 2.) ändere read_all_irfield so ab, dass die Werte nicht kopiert werden müssen


void read_all_irfield (int32_t temps[16][4])
{
  const int32_t data[16][4] = {
      { 1,  2,  3,  4}, { 5,  6,  7,  8}, { 9, 10, 11, 12}, {13, 14, 15, 16},
      { 1,  2,  3,  4}, { 5,  6,  7,  8}, { 9, 10, 11, 12}, {13, 14, 15, 16},
      { 1,  2,  3,  4}, { 5,  6,  7,  8}, { 9, 10, 11, 12}, {13, 14, 15, 16},
      { 1,  2,  3,  4}, { 5,  6,  7,  8}, { 9, 10, 11, 12}, {13, 14, 15, 16}};

  for (int8_t i = 0; i < 16; ++i)
    for (int8_t j = 0; j < 4; ++j)
      temps[i][j] = data[i][j];

}


void setup() {
  Serial.begin(9600);

  int32_t temps[16][4];
    
  read_all_irfield (temps);
  for (int8_t i = 0; i < 16; ++i)
  {
    for (int8_t j = 0; j < 4; ++j)       
    {
      Serial.print(temps[i][j]);
      Serial.print("  ");
    }
    Serial.println();
  }
}

void loop()
{
}
