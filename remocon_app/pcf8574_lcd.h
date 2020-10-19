#ifndef PCF8574_LCD_H
#define PCF8574_LCD_H

#include "Arduino.h"


void pcf8574_lcd_init();
void pcf8574_lcd_backlight_on_off(char on_off);
void pcf8574_lcd_backlight_pwm(unsigned long c_millis, unsigned long c_micros, int pwm_cycle);
void pcf8574_lcd_inst_4bit(char inst);
void pcf8574_lcd_inst_4bit_high(unsigned char inst_high) ;
void pcf8574_lcd_inst_4bit_low(unsigned char inst_low) ;
void pcf8574_lcd_data_4bit(char data);
void pcf8574_lcd_data_4bit_high(unsigned char data_high) ;
void pcf8574_lcd_data_4bit_low(unsigned char data_low) ;
void pcf8574_lcd_inst_8bit(unsigned char inst) ;

#endif
