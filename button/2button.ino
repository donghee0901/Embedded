#define INPUT_ROW 2
#define OUTPUT_COLUME_1 11
#define OUTPUT_COLUME_2 12

void setup()
{
  Serial.begin(9600);

  pinMode(INPUT_ROW, INPUT);
  pinMode(OUTPUT_COLUME_1, OUTPUT);
  pinMode(OUTPUT_COLUME_2, OUTPUT);
}

int toggle = 0;
int toggle_1 = 0;
int in_value = 0;
void loop()
{
  
  in_value = digitalRead(INPUT_ROW);

  if(in_value == 0){
    if(toggle == 1){
      digitalWrite(OUTPUT_COLUME_1, HIGH);
      digitalWrite(OUTPUT_COLUME_2, LOW);
      toggle = 0;
    }
    else{
      digitalWrite(OUTPUT_COLUME_1, LOW);
      digitalWrite(OUTPUT_COLUME_2, HIGH);
      toggle = 1;
    }
  }
  if(in_value == 1 && toggle == 0 && toggle_1 != 0)
  {
    Serial.println("down1");
    toggle_1 = 0;
  }
  else if(in_value == 1 && toggle == 1 && toggle_1 != 1)
  {
    Serial.println("down2");
    toggle_1 = 1;
  }
  else if(in_value == 0 && toggle_1 != 2)
  {
    Serial.println("up");
    toggle_1 = 2;
  }

  delay(10);
}
