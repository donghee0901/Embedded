#define DATA 4
#define CLK 5
#define LATCH 6

#define ROW_0 12

char num[8] = {0x00, 0x38, 0x44, 0x04, 0x08, 0x10, 0x20, 0x7c};

void setup()
{
  for(int i=0;i<3;i++)
  {
    pinMode(i+4, OUTPUT);
  }
  for(int i=0;i<8;i++)
  {
    pinMode(ROW_0+i, OUTPUT);
    digitalWrite(ROW_0+i,LOW);
  }

}
void loop()
{
  for(int i=0;i<8;i++)
  {
    set_column(num[i]);
    digitalWrite(ROW_0+i, HIGH);
    delayMicroseconds(100);
    digitalWrite(ROW_0+i, LOW);
  }
}
void set_column(char dot_data)
{
  for(int i=0;i<8;i++)
  {
    if(dot_data & (0x80 >> i))
    {
      digitalWrite(DATA, LOW);
    }
    else
    {
      digitalWrite(DATA, HIGH);
    }
    digitalWrite(CLK, HIGH);
    digitalWrite(CLK, LOW);
  }
  digitalWrite(LATCH, HIGH);
  digitalWrite(LATCH, LOW);
}
