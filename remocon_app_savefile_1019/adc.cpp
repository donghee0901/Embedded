#include "adc.h"

void adc_init(char ref)
{
  if(ref == REF_AREF)
  {
    ADMUX = 0x00;
    ADCSRA = 0x87;
  }
  else if(ref == REF_AVCC)
  {
    ADMUX = 0x40;
    ADCSRA = 0x87;
  }
}

unsigned short analog_read(char channel)
{
  ADMUX &= ~0x0F;
  ADMUX |= channel;

  ADCSRA |= 0x40;

  while(!(ADCSRA & 0x10));
  unsigned short adc_value = ADC;

  return adc_value;  
}

void adc_init1(char ref, char pre_scale)
{
  if(ref == REF_AREF)
  {
    ADMUX = 0x00;
  }
  else if(ref == REF_AVCC)
  {
    ADMUX = 0x40;
  }
  ADCSRA &= ~0x07;
  ADCSRA = 0x87;
  ADCSRA |= pre_scale;
}
