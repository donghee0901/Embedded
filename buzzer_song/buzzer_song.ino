#define C4 1911
#define D4 1702
#define E4 1516
#define F4 1431
#define G4 1275
#define A4 1136
#define B4 1012

#define SCHOOL_LEN 23

int note_arr[7] = {C4,D4,E4,F4,G4,A4,B4};

int school_tang_tang[SCHOOL_LEN] = {G4,G4,A4,A4,G4,G4,E4,G4,G4,E4,E4,D4,G4,G4,A4,A4,G4,G4,E4,G4,E4,D4,E4,C4};
int school_tang_tang_len[SCHOOL_LEN] = {500,500,500,500,500,500,1000,500,500,500,500,2000,500,500,500,500,500,500,1000,500,500,500,500,2000};
int school_tang_tang_delay[SCHOOL_LEN] = {50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,5000};

unsigned long c_micros = 0;
unsigned long p_micros = 0;
unsigned long c_millis = 0;
unsigned long p_millis = 0;
unsigned long p_millis1 = 0;
int toggle = 0;
int note_index = 0;
int play_on = 1;

void setup()
{
  pinMode(3, OUTPUT);
}
void loop()
{
  c_micros = micros();
  c_millis = millis();

  if(play_on == 1)
  {
    if(c_micros - p_micros > school_tang_tang[note_index])
    {
      p_micros = c_micros;
      if(toggle == 0)
      {
        toggle = 1;
        digitalWrite(3, HIGH);
      }
      else 
      {
        toggle = 0;
        digitalWrite(3, LOW);
      }
    }
  }
  
  if(c_millis - p_millis > school_tang_tang_len[note_index] + school_tang_tang_delay[note_index])
  {
    p_millis = c_millis;
    p_millis1 = c_millis;

    play_on = 1;

    note_index++;
    if(note_index == SCHOOL_LEN)note_index = 0;
  }
  if(play_on == 1)
  {
    if(c_millis - p_millis1 > school_tang_tang_len[note_index])
    {
      p_millis1 = c_millis;

      play_on = 0;
      digitalWrite(3, LOW);
      toggle = 0;
    }
  }
}
