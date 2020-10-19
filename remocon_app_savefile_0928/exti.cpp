#include "exti.h"

void (*isr_func_ptr_0)();
void (*isr_func_ptr_1)();

void exti_init(char int_num, char mode, void (*isr_ptr)())
{
  char int_pin_num = 2 + int_num;

  if (int_num == 0)
    isr_func_ptr_0 = isr_ptr;
  else if (int_num == 1)
    isr_func_ptr_1 = isr_ptr;
  else {
    Serial.println("Please use 0 or 1 interrupt number !!");
    return;
  }


  //pinMode(int_pin_num, INPUT);
  DDRD &= ~(0x01 << int_pin_num);

  //attachInterrupt(0, remoconISR, FALLING);
  EICRA |= mode << (int_num * 2);
  EIMSK |= 0x01 << int_num;
}

SIGNAL(INT0_vect)
{
  isr_func_ptr_0();
}
SIGNAL(INT1_vect)
{
  isr_func_ptr_1();
}
