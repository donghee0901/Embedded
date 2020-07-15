void setup()
{
  Serial.begin(9600);

  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);

  pinMode(9, INPUT);
  pinMode(10, INPUT);
  pinMode(11, INPUT);
  pinMode(12, INPUT);
  

}

int in_key = 0;
char key_toggle[4] = {0};
int in_key2 = 0;
char key_toggle2[4] = {0};
char toggle1 = 0;
char toggle2 = 0;

void loop()
{
  for(int i=0;i<4;i++)
  {
    digitalWrite(5 + i, HIGH);

    in_key = digitalRead(9);
    if(in_key == 1)
    {
      if(key_toggle[i] == 0 && toggle1 == 0){
        Serial.print("SW");
        Serial.print(i+1);
        Serial.println(" down");
        key_toggle[i] = 1;
        toggle1 = 1;
      }
    }
    else
    {
      if(key_toggle[i] == 1 && toggle1 == 1){
        Serial.print("SW");
        Serial.print(i+1);
        Serial.println(" up");
        key_toggle[i] = 0;
        toggle1 = 0;
      }
    }

    in_key2 = digitalRead(10);
    if(in_key2 == 1)
    {
      if(key_toggle2[i] == 0 && toggle2 == 0){
        Serial.print("SW");
        Serial.print(i+5);
        Serial.println(" down");
        key_toggle2[i] = 1;
        toggle2 = 1;
      }
    }
    else
    {
      if(key_toggle2[i] == 1 && toggle2 == 1){
        Serial.print("SW");
        Serial.print(i+5);
        Serial.println(" up");
        key_toggle2[i] = 0;
        toggle2 = 0;
      }
    }

    digitalWrite(5 + i, LOW);
    delay(10);
  }
  

}
