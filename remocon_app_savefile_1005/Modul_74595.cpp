#include "Modul_74595.h"

unsigned char clk_pin_74595;
unsigned char data_pin_74595;
unsigned char latch_pin_74595;

unsigned char data_74595 = 0;


void init_74595(unsigned char clk_pin, unsigned char data_pin, unsigned char latch_pin)
{
  clk_pin_74595 = clk_pin;
  data_pin_74595 = data_pin;
  latch_pin_74595 = latch_pin;

  pinMode(clk_pin_74595, OUTPUT);
  pinMode(data_pin_74595, OUTPUT);
  pinMode(latch_pin_74595, OUTPUT);
}

void set_data_74595(unsigned char data)
{
  shift_out(data);
  digitalWrite(latch_pin_74595, HIGH);
  digitalWrite(latch_pin_74595, LOW);
}

void shift_out(unsigned char data)
{
  for (int i = 0; i < 8; i++) {
    if (data & (0x80 >> i)) {
      digitalWrite(data_pin_74595, HIGH);
    }
    else {
      digitalWrite(data_pin_74595, LOW);
    }
    digitalWrite(clk_pin_74595, HIGH);
    digitalWrite(clk_pin_74595, LOW);
  }
}

unsigned long p_millis_74595 = 0;
unsigned long p_micros_74595 = 0;
unsigned char count_74595 = 0;
unsigned char duty_74595 = 1;

void pwm_74595(unsigned long c_millis, unsigned long c_micros, unsigned char pwm_pin, unsigned char cycle_74595)
{
  if (c_micros - p_micros_74595 > 100) {
    p_micros_74595 = c_micros;
    if (count_74595 == 100)
    {
      data_74595 |= 0x01 << pwm_pin;
      set_data_74595(data_74595);
    }
    else if(count_74595 == duty_74595)
    {
      data_74595 &= ~(0x01 << pwm_pin);
      set_data_74595(data_74595);
    }
    count_74595++;
  }
  if(c_millis - p_millis_74595 > cycle_74595){
    p_millis_74595 = c_millis;
    duty_74595++;
    if(duty_74595 == 99)
    {
      duty_74595 = 1;
    }
  }
}

void init_lcd_74595(unsigned char clk_pin, unsigned char data_pin, unsigned char latch_pin)
{
  clk_pin_74595 = clk_pin;
  data_pin_74595 = data_pin;
  latch_pin_74595 = latch_pin;

  pinMode(clk_pin_74595, OUTPUT);
  pinMode(data_pin_74595, OUTPUT);
  pinMode(latch_pin_74595, OUTPUT);
  
  data_74595 |= 0x01;
  set_data_74595(data_74595);
  data_74595 |= 0x02;
  set_data_74595(data_74595);

  lcd_inst_8bit_74595(0x30);
  lcd_inst_8bit_74595(0x30);
  lcd_inst_8bit_74595(0x30);
  lcd_inst_8bit_74595(0x28);

  lcd_inst_4bit_74595(0x28);
  lcd_inst_4bit_74595(0x06);
  lcd_inst_4bit_74595(0x0c);
  lcd_inst_4bit_74595(0x80);
  lcd_inst_4bit_74595(0x01);

  delay(10);
}

void lcd_inst_4bit_74595(unsigned char inst)
{
  lcd_inst_4bit_high_74595(inst);
  lcd_inst_4bit_low_74595(inst);
}

void lcd_inst_4bit_high_74595(unsigned char inst_high) {
  //RS LOW
  data_74595 &= ~0x01;
  set_data_74595(data_74595);
  
  data_74595 &= ~0xF0;
  data_74595 |= (inst_high & 0xF0);
  set_data_74595(data_74595);
  
  data_74595 |= 0x04;
  set_data_74595(data_74595);
  
  data_74595 &= ~0x04;
  set_data_74595(data_74595);
  
  data_74595 |= 0x01;
  set_data_74595(data_74595);

  delayMicroseconds(50); // delay 50us
}
void lcd_inst_4bit_low_74595(unsigned char inst_low) {
  //RS LOW
  data_74595 &= ~0x01;
  set_data_74595(data_74595);

  data_74595 &= ~0xF0;
  data_74595 |= ((inst_low & 0x0F) << 4);
  set_data_74595(data_74595);
  
  data_74595 |= 0x04;
  set_data_74595(data_74595);
  
  data_74595 &= ~0x04;
  set_data_74595(data_74595);
  
  data_74595 |= 0x01;
  set_data_74595(data_74595);

  delayMicroseconds(50); // delay 50us
}

//---------------------------------------------------------------------------------

void lcd_data_4bit_74595(unsigned char data)
{
  lcd_data_4bit_high_74595(data);
  lcd_data_4bit_low_74595(data);
}

void lcd_data_4bit_high_74595(unsigned char data_high) {
  data_74595 &= ~0xF0;
  data_74595 |= (data_high & 0xF0);
  set_data_74595(data_74595);
  
  data_74595 |= 0x04;
  set_data_74595(data_74595);
  
  data_74595 &= ~0x04;
  set_data_74595(data_74595);

  delayMicroseconds(50); // delay 50us
}
void lcd_data_4bit_low_74595(unsigned char data_low) {
  data_74595 &= ~0xF0;
  data_74595 |= ((data_low & 0x0F) << 4);
  set_data_74595(data_74595);
  
  data_74595 |= 0x04;
  set_data_74595(data_74595);
  
  data_74595 &= ~0x04;
  set_data_74595(data_74595);

  delayMicroseconds(50); // delay 50us
}

//---------------------------------------------------------------------------------

  void lcd_inst_8bit_74595(unsigned char inst) {
  
  data_74595 &= ~0x01;
  set_data_74595(data_74595);

  data_74595 &= ~0xF0;
  data_74595 |= (inst & 0xF0);
  set_data_74595(data_74595);
  
  data_74595 |= 0x04;
  set_data_74595(data_74595);
  
  data_74595 &= ~0x04;
  set_data_74595(data_74595);
  
  data_74595 |= 0x01;
  set_data_74595(data_74595);

  delayMicroseconds(50); // delay 50us
}
