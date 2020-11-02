#include "dotmatrix.h"


char *dot_pin;

void dotmatirx_init(char *pin_num)
{
  dot_pin = pin_num;

  for (int i = 0; i < 16; i++)pinMode(dot_pin[i], OUTPUT);
}

void set_line(char line_num, char value)
{
  for (int i = 0; i < 8; i++) {
    if (value & (0x01 << i)) digitalWrite(dot_pin[i + 8], LOW);
    else digitalWrite(dot_pin[i + 8], HIGH);
  }

  digitalWrite(dot_pin[line_num], HIGH);
}

char dot_row_num = 0;
void set_num_delay(char *dot_num)
{
  // all off
  for (int i = 0; i < 8; i++) digitalWrite(dot_pin[i], LOW);

  // one column value set
  for (int i = 0; i < 8; i++)
  {
    if (dot_num[dot_row_num] & (0x80 >> i)) digitalWrite(dot_pin[i + 8], LOW);
    else digitalWrite(dot_pin[i + 8], HIGH);
  }
  // onew row power on
  digitalWrite(dot_pin[dot_row_num], HIGH);
  dot_row_num++;
  if (dot_row_num == 8) dot_row_num = 0;
  // delay
  delay(1);
}
unsigned long pre_dot_millis = 0;
void set_num_millis(char *dot_num, unsigned long dot_curr_millis)
{
  if (dot_curr_millis - pre_dot_millis >= 1)
  {
    pre_dot_millis = dot_curr_millis;
    // all off
    for (int i = 0; i < 8; i++) digitalWrite(dot_pin[i], LOW);

    // one column value set
    for (int i = 0; i < 8; i++)
    {
      if (dot_num[dot_row_num] & (0x80 >> i)) digitalWrite(dot_pin[i + 8], LOW);
      else digitalWrite(dot_pin[i + 8], HIGH);
    }
    // onew row power on
    digitalWrite(dot_pin[dot_row_num], HIGH);
    dot_row_num++;
    if (dot_row_num == 8) dot_row_num = 0;
  }
}

//==============================================================================

char clock_74595_pin;
char data_74595_pin;
char latch_74595_pin;

void dotmatirx_init_74595(char *pin_num)
{
  dot_pin = pin_num;
  data_74595_pin = dot_pin[8];
  clock_74595_pin = dot_pin[9];
  latch_74595_pin = dot_pin[10];

  for (int i = 0; i < 11; i++)pinMode(dot_pin[i], OUTPUT);
}

void set_74595_value(char value)
{
  for (int i = 0; i < 8; i++) {
    if (value & (0x01 << i)) digitalWrite(data_74595_pin, LOW);
    else digitalWrite(data_74595_pin, HIGH);

    digitalWrite(clock_74595_pin, HIGH);
    digitalWrite(clock_74595_pin, LOW);
  }

  digitalWrite(latch_74595_pin, HIGH);
  digitalWrite(latch_74595_pin, LOW);
}

void set_line_74595(char line_num, char value)
{
  //colume data
  set_74595_value(value);
  //row power on
  digitalWrite(dot_pin[line_num], HIGH);
}

void set_num_74595_delay(char *dot_num)
{
  // all off
  for (int i = 0; i < 8; i++) digitalWrite(dot_pin[i], LOW);

  // one column value set
  set_74595_value(dot_num[dot_row_num]);
  // onew row power on
  digitalWrite(dot_pin[dot_row_num], HIGH);
  dot_row_num++;
  if (dot_row_num == 8) dot_row_num = 0;
  // delay
  delay(1);
}

void set_num_74595_millis(char *dot_num, unsigned long dot_curr_millis)
{
  if (dot_curr_millis - pre_dot_millis >= 1)
  {
    pre_dot_millis = dot_curr_millis;
    // all off
    for (int i = 0; i < 8; i++) digitalWrite(dot_pin[i], LOW);

    // one column value set
    set_74595_value(dot_num[dot_row_num]);
    // onew row power on
    digitalWrite(dot_pin[dot_row_num], HIGH);
    dot_row_num++;
    if (dot_row_num == 8) dot_row_num = 0;
  }
}

//===================================================================

char col_value_74595 = 0;
char row_num;
char col_num;
void dot_led_74595_toggle_delay(char led_num)
{
  row_num = led_num / 8;
  col_num = led_num % 8;

  digitalWrite(dot_pin[row_num], HIGH);
  col_value_74595 &= ~(0x01 << col_num);
  set_74595_value(col_value_74595);
  delay(1000);
  col_value_74595 |= 0x01 << col_num;
  set_74595_value(col_value_74595);
  delay(1000);
}

unsigned long pre_led_micros = 0;
unsigned long pre_led_millis = 0;
int led_pwm_count = 0;
int led_pwm_duty = 99;

void dot_led_74595_pwm(char led_num, unsigned long cur_led_micros, unsigned long cur_led_millis)
{
  row_num = led_num / 8;
  col_num = led_num % 8;

  if (cur_led_micros - pre_led_micros > 100)
  {
    pre_led_micros = cur_led_micros;

    if (led_pwm_duty > 0 && led_pwm_count == 100)
    {
      col_value_74595 |= (0x01 << col_num);
      set_74595_value(col_value_74595);
      led_pwm_count = 0;
    }
    else if (led_pwm_count == led_pwm_duty)
    {
      col_value_74595 &= ~(0x01 << col_num);
      set_74595_value(col_value_74595);
    }
    led_pwm_count++;
  }
  if (cur_led_millis - pre_led_millis > 10)
  {
    pre_led_millis = cur_led_millis;

    if (led_pwm_duty >= 1)led_pwm_duty--;
  }
  digitalWrite(dot_pin[row_num], HIGH);
}

void led_pwm_value(char led_num, char value)
{
  row_num = led_num / 8;
  col_num = led_num % 8;

  led_pwm_duty = value;
}


//==============================================================

int led_pwm_duty1 = 99;
void dot_led_74595_millis_pwm(char led_num, char *dot_num, unsigned long cur_led_micros, unsigned long cur_led_millis)
{
  row_num = led_num / 8;
  col_num = led_num % 8;

  if (cur_led_micros - pre_led_micros > 100)
  {
    pre_led_micros = cur_led_micros;

    for(int i = 0; i < 8; i++) 
      digitalWrite(dot_pin[i+8], LOW);
    digitalWrite(dot_pin[row_num], HIGH);
    
    if (led_pwm_count == 100)
    {
      dot_num[0] |= 0x80;
      if (dot_row_num == 0)
        set_74595_value(dot_num[0]);
    }
    else if (led_pwm_count == led_pwm_duty)
    {
      dot_num[0] &= ~0x80;
      if (dot_row_num == 0)
        set_74595_value(dot_num[0]);
    }
    led_pwm_count++;
  }
  if (cur_led_millis - pre_led_millis > 10)
  {
    pre_led_millis = cur_led_millis;

    led_pwm_duty1--;
    if (led_pwm_duty1 == 1)led_pwm_duty1 = 99;
  }
}


//#include "dotmatrix.h"
//#include "gpio.h"
//unsigned char row_pin[8];
//unsigned char col_pin[8];
//unsigned char dot_num_row = 0;
//
//unsigned char row_pin_74595[8];
//unsigned char dot_clk_74595 = 0;
//unsigned char dot_data_74595 = 0;
//unsigned char dot_latch_74595 = 0;
//
//void dot_metrix_init(unsigned char * row_pins, unsigned char * col_pins) {
//  for(int i = 0; i < 8; i++) pin_mode(row_pin[i] = row_pins[i], OUTPUT);
//  for(int i = 0; i < 8; i++) pin_mode(col_pin[i] = col_pins[i], OUTPUT);
//}
//
//void set_line(unsigned char line_num, unsigned char value) {
//  for(int i = 0; i < 8; i++) {
//    if((value & (0x01 << i))) {
//      digitalWrite(col_pin[i], LOW); // Col은 LOW여야 켜짐.  
//    }else {
//      digitalWrite(col_pin[i], HIGH);
//    }
//  }
//  digitalWrite(row_pin[line_num], HIGH);
//}
//
//void set_num_delay(unsigned char * dot_num) {
//  //1. All off
//  for(int i = 0; i < 8; i ++ ) {
//    digitalWrite(row_pin[i], LOW);
//  }
//  //Set First line value
//  for(int i = 0; i < 8; i ++ ) {
//    if(dot_num[dot_num_row] & (0x80 >> i)) {
//      digitalWrite(col_pin[i], LOW); // Col은 LOW여야 켜짐.  
//    }else {
//      digitalWrite(col_pin[i], HIGH);
//    }
//  }
//  //One row power on
//  digitalWrite(row_pin[dot_num_row], HIGH);
//  dot_num_row++;
//  if(dot_num_row == 8) dot_num_row = 0;
//  delay(1);
//}
//
//unsigned long previous_dot_millis = 0;
//void set_num_millis(unsigned char * dot_num, unsigned long current_millis) {
//  if(current_millis - previous_dot_millis >= 1) {
//    previous_dot_millis = current_millis;
//    //1. All off
//    for(int i = 0; i < 8; i ++ ) {
//      digitalWrite(row_pin[i], LOW);
//    }
//    //Set First line value
//    for(int i = 0; i < 8; i ++ ) {
//      if(dot_num[dot_num_row] & (0x80 >> i)) {
//        digitalWrite(col_pin[i], LOW); // Col은 LOW여야 켜짐.  
//      }else {
//        digitalWrite(col_pin[i], HIGH);
//      }
//    }
//    //One row power on
//    digitalWrite(row_pin[dot_num_row], HIGH);
//    dot_num_row++;
//    if(dot_num_row == 8) dot_num_row = 0;
//  }
//}
//void dot_metrix_init_74595(unsigned char * row_pins, unsigned char clk, unsigned char data, unsigned char latch) {
//  pinMode(dot_clk_74595 = clk, OUTPUT);
//  pinMode(dot_data_74595 = data, OUTPUT);
//  pinMode(dot_latch_74595 = latch, OUTPUT);
//  for(int i = 0; i < 8; i++) 
//    pinMode(row_pin_74595[i] = row_pins[i], OUTPUT);
//}
//void set_74595_value(unsigned char value) {
//  //Column data
//  for(int i = 0; i < 8; i++) {
//    if(value & (0x01 << i)) {
//      digitalWrite(dot_data_74595, LOW); // Col은 LOW여야 켜짐.  
//    }else {
//      digitalWrite(dot_data_74595, HIGH);
//    }
//    digitalWrite(dot_clk_74595, HIGH);
//    digitalWrite(dot_clk_74595, LOW);
//  }
//  digitalWrite(dot_latch_74595, HIGH);
//  digitalWrite(dot_latch_74595, LOW); 
//}
//void set_line_74595(unsigned char line_num, unsigned char value) {
//  set_74595_value(value);
//  digitalWrite(row_pin_74595[line_num], HIGH);
//}
//
//void set_num_74595_delay(unsigned char * dot_num) {
//  //1. All off
//  for(int i = 0; i < 8; i ++) {
//    digitalWrite(row_pin_74595[i], LOW);
//  }
//  //Set First line value
//  set_74595_value(dot_num[dot_num_row]);
//  //One row power on
//  digitalWrite(row_pin_74595[dot_num_row], HIGH);
//  dot_num_row++;
//  if(dot_num_row == 8) dot_num_row = 0;
//  delay(1);
//}
//void set_dot_num_74595_millis(unsigned char * dot_num, unsigned long current_millis) {
//  if(current_millis - previous_dot_millis >= 1) {
//    previous_dot_millis = current_millis;
//    //1. All off
//    for(int i = 0; i < 8; i ++ ) {
//      digitalWrite(row_pin_74595[i], LOW);
//    }
//    //Set First line value  
//    set_74595_value(dot_num[dot_num_row]);
//    //One row power on
//    digitalWrite(row_pin_74595[dot_num_row], HIGH);
//    dot_num_row++;
//    if(dot_num_row == 8) dot_num_row = 0;
//  }
//}
//unsigned char col_value = 0;
//void dot_led_74595_toggle(unsigned char led_num) {
//  unsigned char row = led_num / 8;
//  unsigned char col = led_num % 8;
//  
//  for(int i = 0; i < 8; i++) 
//    digitalWrite(row_pin_74595[i], LOW);
//  
//  digitalWrite(row_pin_74595[row], HIGH);
//  col_value |= 0x01 << col;
//  set_74595_value(col_value);
//  col_value &= ~(0x01 << col);
//  delay(300);
//  set_74595_value(col_value);
//  delay(300);
//}
//unsigned long previous_dot_micros = 0;
//unsigned char dot_duty = 99;
//unsigned char dot_count = 0;
//
//unsigned char d_row = 0, d_col = 0;
//
//void dot_led_74595_pwm(unsigned char led_num, unsigned long current_micros, unsigned long current_millis) {
//  if(current_millis - previous_dot_millis > 10) {
//    previous_dot_millis = current_millis;
//    if(dot_duty > 2) dot_duty --;
//  }
//  if(current_micros - previous_dot_micros > 100) {
//    previous_dot_micros = current_micros;
//    
//    for(int i = 0; i < 8; i++) 
//      digitalWrite(row_pin_74595[i], LOW);
//    
//    digitalWrite(row_pin_74595[d_row], HIGH);
//    if(dot_count == 100) {
//      dot_count = 0;
//      col_value |= 0x01 << d_col;
//      set_74595_value(col_value);
//    }else if(dot_count == dot_duty) {
//      col_value &= ~(0x01 << d_col);
//      set_74595_value(col_value);
//    }
//    dot_count++;
//  }
//}
//
//void dot_led_pwm_value(unsigned char led_num, unsigned char value){
//  d_row = led_num / 8;
//  d_col = led_num % 8;
//  dot_duty = value;
//}
//
//void set_dot_num_74595_millis_pwm(unsigned char led_num, unsigned char * dot_num, unsigned long current_micros, unsigned long current_millis) {
//  //My own number print.
//  
//  //My owm position
//  d_row = led_num / 8;
//  d_col = led_num % 8;
//  
//  if(current_millis - previous_dot_millis >= 10) {
//    previous_dot_millis = current_millis;
//    dot_duty --;
//    if(dot_duty == 0) dot_duty = 99;
//  }
//  if(current_micros - previous_dot_micros > 100) {
//    previous_dot_micros = current_micros;
//    //1. All off
//    for(int i = 0; i < 8; i ++ ) {
//      digitalWrite(row_pin_74595[i], LOW);
//    }
//    if(dot_count == 100) {
//        dot_count = 0;
//        dot_num[d_row] |= 0x01 << d_col;
//        //set_74595_value(dot_num[d_row]);
//    }else if(dot_count == dot_duty) {
//        dot_num[d_row] &= ~(0x01 << d_col);
//        //set_74595_value(dot_num[d_row]);
//    }
//    dot_count++;
//    //Set First line value  
//    set_74595_value(dot_num[dot_num_row]);
//    //One row power on
//    digitalWrite(row_pin_74595[dot_num_row], HIGH);
//    dot_num_row++;
//    if(dot_num_row == 8 ) dot_num_row = 0;
//    
//  }
//}
