#include "pcf8574_lcd.h"
#include "I2C.h"
#include "char_lcd.h"

#define SCL 19
#define SDA 18

char pcf8574_lcd = 0;

void pcf8574_lcd_init()
{
  i2c_init(SCL, SDA);

  pcf8574_lcd |= 0x01;
  i2c_8bit_data_write(0x27, pcf8574_lcd);
  pcf8574_lcd |= 0x02;
  i2c_8bit_data_write(0x27, pcf8574_lcd);

  pcf8574_lcd_inst_8bit(0x30);
  pcf8574_lcd_inst_8bit(0x30);
  pcf8574_lcd_inst_8bit(0x30);
  pcf8574_lcd_inst_8bit(0x28);

  pcf8574_lcd_inst_4bit(0x28);
  pcf8574_lcd_inst_4bit(0x06);
  pcf8574_lcd_inst_4bit(0x0c);
  pcf8574_lcd_inst_4bit(0x80);
  pcf8574_lcd_inst_4bit(0x01);

  delay(10);
}

void pcf8574_lcd_backlight_on_off(char on_off)
{
  if (on_off == 1)
  {
    pcf8574_lcd |= 0x08;
    i2c_8bit_data_write(0x27, pcf8574_lcd);
  }
  else
  {
    pcf8574_lcd &= ~0x08;
    i2c_8bit_data_write(0x27, pcf8574_lcd);
  }
}

unsigned long p_millis_8574 = 0;
unsigned long p_micros_8574 = 0;
unsigned char pcf8574_lcd_pwm_count = 0;
unsigned char pcf8574_lcd_pwm_duty = 10;


void pcf8574_lcd_backlight_pwm(unsigned long c_millis, unsigned long c_micros, int pwm_cycle)
{
  if (c_micros - p_micros_8574 > 100)
  {
    p_micros_8574 = c_micros;

    if (pcf8574_lcd_pwm_count == 100) {
      pcf8574_lcd_pwm_count = 0;
      pcf8574_lcd_backlight_on_off(1);
    }
    else if (pcf8574_lcd_pwm_count == pcf8574_lcd_pwm_duty)
    {
      pcf8574_lcd_backlight_on_off(0);
    }
    pcf8574_lcd_pwm_count++;
  }

  if (c_millis - p_millis_8574 > pwm_cycle)
  {
    p_millis_8574 = c_millis;

    pcf8574_lcd_pwm_duty++;
    if (pcf8574_lcd_pwm_duty == 99)
    {
      pcf8574_lcd_pwm_duty = 1;
    }
  }
}

//-----------------------------------------------------------------------------------------------------

void pcf8574_lcd_inst_4bit(char inst)
{
  pcf8574_lcd_inst_4bit_high(inst);
  pcf8574_lcd_inst_4bit_low(inst);
}

void pcf8574_lcd_inst_4bit_high(unsigned char inst_high) {
  //RS LOW
  pcf8574_lcd &= ~0x01;
  i2c_8bit_data_write(0x27, pcf8574_lcd);
  
  pcf8574_lcd &= ~0xF0;
  pcf8574_lcd |= (inst_high & 0xF0);
  i2c_8bit_data_write(0x27, pcf8574_lcd);
  
  pcf8574_lcd |= 0x04;
  i2c_8bit_data_write(0x27, pcf8574_lcd);
  
  pcf8574_lcd &= ~0x04;
  i2c_8bit_data_write(0x27, pcf8574_lcd);
  
  pcf8574_lcd |= 0x01;
  i2c_8bit_data_write(0x27, pcf8574_lcd);

  delayMicroseconds(50); // delay 50us
}
void pcf8574_lcd_inst_4bit_low(unsigned char inst_low) {
  //RS LOW
  pcf8574_lcd &= ~0x01;
  i2c_8bit_data_write(0x27, pcf8574_lcd);

  pcf8574_lcd &= ~0xF0;
  pcf8574_lcd |= ((inst_low & 0x0F) << 4);
  i2c_8bit_data_write(0x27, pcf8574_lcd);
  
  pcf8574_lcd |= 0x04;
  i2c_8bit_data_write(0x27, pcf8574_lcd);
  
  pcf8574_lcd &= ~0x04;
  i2c_8bit_data_write(0x27, pcf8574_lcd);
  
  pcf8574_lcd |= 0x01;
  i2c_8bit_data_write(0x27, pcf8574_lcd);

  delayMicroseconds(50); // delay 50us
}

//---------------------------------------------------------------------------------

void pcf8574_lcd_data_4bit(char data)
{
  pcf8574_lcd_inst_4bit_high(data);
  pcf8574_lcd_inst_4bit_low(data);
}

void pcf8574_lcd_data_4bit_high(unsigned char data_high) {
  pcf8574_lcd &= ~0xF0;
  pcf8574_lcd |= (data_high & 0xF0);
  i2c_8bit_data_write(0x27, pcf8574_lcd);
  
  pcf8574_lcd |= 0x04;
  i2c_8bit_data_write(0x27, pcf8574_lcd);
  
  pcf8574_lcd &= ~0x04;
  i2c_8bit_data_write(0x27, pcf8574_lcd);

  delayMicroseconds(50); // delay 50us
}
void pcf8574_lcd_data_4bit_low(unsigned char data_low) {
  pcf8574_lcd &= ~0xF0;
  pcf8574_lcd |= ((data_low & 0x0F) << 4);
  i2c_8bit_data_write(0x27, pcf8574_lcd);
  
  pcf8574_lcd |= 0x04;
  i2c_8bit_data_write(0x27, pcf8574_lcd);
  
  pcf8574_lcd &= ~0x04;
  i2c_8bit_data_write(0x27, pcf8574_lcd);

  delayMicroseconds(50); // delay 50us
}

//---------------------------------------------------------------------------------

void pcf8574_lcd_inst_8bit(unsigned char inst) {
  
  pcf8574_lcd &= ~0x01;
  i2c_8bit_data_write(0x27, pcf8574_lcd);

  pcf8574_lcd |= (inst & 0xF0);
  i2c_8bit_data_write(0x27, pcf8574_lcd);
  
  pcf8574_lcd |= 0x04;
  i2c_8bit_data_write(0x27, pcf8574_lcd);
  
  pcf8574_lcd &= ~0x04;
  i2c_8bit_data_write(0x27, pcf8574_lcd);
  
  pcf8574_lcd |= 0x01;
  i2c_8bit_data_write(0x27, pcf8574_lcd);

  delayMicroseconds(50); // delay 50us
}
