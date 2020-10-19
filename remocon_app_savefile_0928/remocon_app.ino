#include "char_lcd.h"
#include "I2C.h"
#include "pcf8574_lcd.h"
#include "Modul_74595.h"

#define SCL 19
#define SDA 18

#define CLK_74595   14
#define DATA_74595  15
#define LATCH_74595 16

#define PWM_PIN_74595 3
#define CYVLE_PWM_74595 100

char char_lcd_pin_8bit[11] = {3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
char char_lcd_pin_4bit[7] = {3, 4, 5, 10, 11, 12, 13};


void setup()
{
  Serial.begin(9600);
  //char_lcd_init_8bit(char_lcd_pin_8bit);
  //char_lcd_init_4bit(char_lcd_pin_4bit);

  pcf8574_lcd_init();

  init_74595(CLK_74595, DATA_74595, LATCH_74595);
}

unsigned long current_millis = 0;
unsigned long current_micros = 0;
unsigned long previous_millis = 0;

int count_lcd = 0;

void loop()
{
  //char_lcd_data_8bit(0x31);
  //char_lcd_data_4bit(0x31);

  current_millis = millis();
  current_micros = micros();
  //
  //  pcf8574_lcd_backlight_pwm(current_millis, current_micros, 10);
  //
  //  if(current_millis - previous_millis > 1000)
  //  {
  //    previous_millis = current_millis;
  //    pcf8574_lcd_data_4bit(0x31);
  //  }

  //  set_data_74595(0x08);
  //  delay(1000);
  //  set_data_74595(0x00);
  //  delay(1000);

  if (current_millis - previous_millis > 1000)
  {
      previous_millis = current_millis;

      lcd_data_4bit_74595(0x31);
  }

//  pwm_74595(current_millis, current_micros, PWM_PIN_74595, CYVLE_PWM_74595);
}
