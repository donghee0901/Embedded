#ifndef CHAR_LCD_H // define 안되있으면, define 하라.
#define CHAR_LCD_H

#include "Arduino.h"

void char_lcd_init_8bit(char *pin);
void char_lcd_inst_8bit(unsigned char inst);
void char_lcd_data_8bit(unsigned char data);

void char_lcd_init_4bit(char *pin);
void char_lcd_inst_4bit(unsigned char inst);
void char_lcd_inst_4bit_high(unsigned char inst_high);
void char_lcd_inst_4bit_low(unsigned char inst_low);
void char_lcd_data_4bit(unsigned char data);
void char_lcd_data_4bit_high(unsigned char data_high);
void char_lcd_data_4bit_low(unsigned char data_low);

#endif
