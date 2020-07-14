#define INPUT_ROW 2
#define OUTPUT_COLUME_1 9
#define OUTPUT_COLUME_2 10
#define OUTPUT_COLUME_3 11
#define OUTPUT_COLUME_4 12
#define BUTTUN_NUMBER 4

int toggle = 0;
int toggle_down[4] = {0,0,0,0};
int toggle_arr[16] = {OUTPUT_COLUME_1,OUTPUT_COLUME_2,OUTPUT_COLUME_3,OUTPUT_COLUME_4,5,6,7,8,9,10,11,12,13,14,15,16};
int in_value = 0;

void setup()
{
  Serial.begin(9600);

  pinMode(INPUT_ROW, INPUT);
  for(int i=0;i<BUTTUN_NUMBER;i++){
    pinMode(toggle_arr[i], OUTPUT);
  }
}


void loop()
{
  
  toggle++;
  if(toggle >= 4)toggle = 0;

  for(int i=0;i<BUTTUN_NUMBER;i++){
    digitalWrite(toggle_arr[i], LOW);
  }

  digitalWrite(toggle_arr[toggle], HIGH);


  in_value = digitalRead(INPUT_ROW);

  if(in_value == 1)
  {
    if(toggle_down[toggle] == 0)
    {
      Serial.print(toggle + 1);
      Serial.println("down");
      toggle_down[toggle] = 1;
    }
  }
  else
  {
    if(toggle_down[toggle] == 1)
    {
      Serial.print(toggle + 1);
      Serial.println("up");
      toggle_down[toggle] = 0;
    }
  }

  delay(10);
}
