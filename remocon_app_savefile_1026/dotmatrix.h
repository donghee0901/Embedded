#ifndef DOTMATRIX_H
#define DOTMATRIX_H

#include "Arduino.h"

void dotmatirx_init(char *pin_num);
void set_line(char line_num, char value);
void set_num_delay(char *dot_num);
void set_num_millis(char *dot_num, unsigned long dot_curr_millis);


void dotmatirx_init_74595(char *pin_num);
void set_74595_value(char value);
void set_line_74595(char line_num, char value);
void set_num_74595_delay(char *dot_num);
void set_num_74595_millis(char *dot_num, unsigned long dot_curr_millis);
void dot_led_74595_toggle_delay(char led_num);
void dot_led_74595_pwm(char led_num, unsigned long cur_led_micors, unsigned long cur_led_millis);
void led_pwm_value(char led_num, char value);
void dot_led_74595_millis_pwm(char led_num,char *dot_num, unsigned long cur_led_micros, unsigned long cur_led_millis);

#endif

//#ifndef DOT_METRIX_H
//#define DOT_METRIX_H
//
//#include "Arduino.h"
//void dot_metrix_init(unsigned char * row_pins, unsigned char * col_pins);
//void set_line(unsigned char line_num, unsigned char value);
//void set_num_delay(unsigned char * dot_num);
//void set_num_millis(unsigned char * dot_num, unsigned long current_millis);
//void set_74595_value(unsigned char value);
//void dot_metrix_init_74595(unsigned char * row_pins, unsigned char clk, unsigned char data, unsigned char latch);
//void set_line_74595(unsigned char line_num, unsigned char value);
//void set_num_74595_delay(unsigned char * dot_num);
//void set_dot_num_74595_millis(unsigned char * dot_num, unsigned long current_millis);
//void dot_led_74595_toggle(unsigned char led_num);
//void dot_led_74595_pwm(unsigned char led_num, unsigned long current_micros, unsigned long current_millis);
//
//void dot_led_pwm_value(unsigned char led_num, unsigned char value);
//void set_dot_num_74595_millis_pwm(unsigned char led_num, unsigned char * dot_num, unsigned long current_micros, unsigned long current_millis);
//
//#endif
