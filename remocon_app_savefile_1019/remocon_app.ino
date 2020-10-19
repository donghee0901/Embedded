
int duty = 1;
unsigned int duty_count = 0;
unsigned int count = 0;

void setup()
{
  pinMode(13, OUTPUT);
  
  TCCR2A = 0x00;
  TCCR2B = 0x02;
//  OCR2A = 80;
//  TCNT2 = 255-80;

  
  TCCR2A = 0x03;
  TCCR2B = 0x04;
  OCR2A = 80;
  TCNT2 = 255-80;
  TIMSK2 = 0x01;
}

void loop()
{
  
}

/*ISR(TIMER2_COMPA_vect)
{
  count++;
  duty_count++;
  if (duty_count == duty)
  {
    digitalWrite(13, LOW);
  }
  if (duty_count == 100)
  {
    duty_count = 0;
    digitalWrite(13, HIGH);
  }

  if(count == 250)
  {
    count = 0;
    duty++;
    if(duty == 100)duty = 1;
  }
}*/

/*ISR(TIMER2_OVF_vect)
{
  TCNT2 = 255-80;
  count++;
  duty_count++;
  if (duty_count == duty)
  {
    digitalWrite(13, LOW);
  }
  if (duty_count == 100)
  {
    duty_count = 0;
    digitalWrite(13, HIGH);
  }

  if(count == 250)
  {
    count = 0;
    duty++;
    if(duty == 100)duty = 1;
  }
}*/

ISR(TIMER2_COMPA_vect)
{
  count++;
  duty_count++;
  if (duty_count == duty)
  {
    digitalWrite(13, LOW);
  }
  if (duty_count == 100)
  {
    duty_count = 0;
    digitalWrite(13, HIGH);
  }

  if(count == 250)
  {
    count = 0;
    duty++;
    if(duty == 100)duty = 1;
  }
}

ISR(TIMER2_OVF_vect)
{
  TCNT2 = 255-80;
  count++;
  duty_count++;
  if (duty_count == duty)
  {
    digitalWrite(13, LOW);
  }
  if (duty_count == 100)
  {
    duty_count = 0;
    digitalWrite(13, HIGH);
  }

  if(count == 250)
  {
    count = 0;
    duty++;
    if(duty == 100)duty = 1;
  }
}
