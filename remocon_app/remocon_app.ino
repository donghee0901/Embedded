#include "dotmatrix.h"

// row0, row1, ..., row7, col0, col1, ..., col7
char pin_num_dot[16] = {4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19};

char pin_num_dot_74595[11] = {4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14};

char numbers[10][8] = {
  {0x00, 0x38, 0x44, 0x4C, 0x54, 0x64, 0x44, 0x38},
  {0x00, 0x10, 0x30, 0x50, 0x10, 0x10, 0x10, 0x7c},
  {0x00, 0x38, 0x44, 0x04, 0x08, 0x10, 0x20, 0x7c},
  {0x00, 0x38, 0x44, 0x04, 0x18, 0x04, 0x44, 0x38},
  {0x00, 0x08, 0x18, 0x28, 0x48, 0x7C, 0x08, 0x08},
  {0x00, 0x7C, 0x40, 0x78, 0x04, 0x04, 0x44, 0x38 },
  {0x00, 0x38, 0x40, 0x40, 0x78, 0x44, 0x44, 0x38},
  {0x00, 0x7C, 0x04, 0x08, 0x10, 0x20, 0x20, 0x20},
  {0x00, 0x38, 0x44, 0x44, 0x38, 0x44, 0x44, 0x38},
  {0x00, 0x38, 0x44, 0x44, 0x3C, 0x04, 0x44, 0x38}
};

char dot_number[8] = {0x00, 0x38, 0x44, 0x04, 0x08, 0x10, 0x20, 0x7c};

void setup()
{
  Serial.begin(9600);

  dotmatirx_init_74595(pin_num_dot_74595);

}
unsigned long c_millis = 0;
unsigned long c_micros = 0;
unsigned long p_millis = 0;
int num = 0;
char in_num = 0;
void loop()
{
  in_num = 0;
  c_millis = millis();
  c_micros = micros();
  //  if (c_millis - p_millis > 1000)
  //  {
  //    p_millis = c_millis;
  //    num++;
  //    if (num == 10)num = 0;
  //  }
  //  //  set_num_millis(dot_number, c_millis);
  //  set_num_74595_millis(numbers[num], c_millis);

  //    dot_led_74595_toggle_delay(10);

  if (Serial.available())
  {
    int in_data = Serial.read();
    in_num = in_data - '0'; 
    Serial.printf("%d\n", in_num);
    led_pwm_value(in_num, 99);
  }
  dot_led_74595_pwm(in_num, c_micros, c_millis);
}

//#include "dotmatrix.h"
//
//unsigned char row[] = {4, 5, 6, 7, 8, 9, 10, 11};
//unsigned char column[] = {12, 13, 14, 15, 16, 17, 18, 19};
//
//unsigned char numbers[10][8] = {
//  {0x00, 0x38, 0x44, 0x4C, 0x54, 0x64, 0x44, 0x38},
//  {0x00, 0x10, 0x30, 0x50, 0x10, 0x10, 0x10, 0x7c},
//  {0x00, 0x38, 0x44, 0x04, 0x08, 0x10, 0x20, 0x7c},
//  {0x00, 0x38, 0x44, 0x04, 0x18, 0x04, 0x44, 0x38},
//  {0x00, 0x08, 0x18, 0x28, 0x48, 0x7C, 0x08, 0x08},
//  {0x00, 0x7C, 0x40, 0x78, 0x04, 0x04, 0x44, 0x38},
//  {0x00, 0x38, 0x40, 0x40, 0x78, 0x44, 0x44, 0x38},
//  {0x00, 0x7C, 0x04, 0x08, 0x10, 0x20, 0x20, 0x20},
//  {0x00, 0x38, 0x44, 0x44, 0x38, 0x44, 0x44, 0x38},
//  {0x00, 0x38, 0x44, 0x44, 0x3C, 0x04, 0x44, 0x38},
//};
//
//void setup() {
//  Serial.begin(9600);
//  //dot_metrix_init(row, column);
//  dot_metrix_init_74595(row, 13, 12, 14);
//}
//unsigned long main_current_millis = 0;
//unsigned char current_index = 0;
//unsigned long main_previous_millis = 0;
//unsigned long main_current_micros = 0;
//
//int in_num = 0;
//void loop() {
//  main_current_millis = millis();
//  main_current_micros = micros();
//  //
//  //dot_led_74595_pwm(20, main_current_micros, main_current_millis);
//  //
//  //if(main_current_millis - main_previous_millis > 5000){
//  //  main_previous_millis = main_current_millis;
//  //  dot_led_pwm_value(20, 99);
//  //}
//  //set_dot_num_74595_millis(numbers[current_index], main_current_millis);
//  //set_num_delay(numbers[2]);
//  //set_num_74595_delay(numbers[2]);
//  //for(int i = 0; i < 64; i++) dot_led_74595_toggle(i);
//  //dot_led_74595_pwm(in_num, main_current_micros, main_current_millis);
//  //if(Serial.available()){
//  //  int in_data = Serial.read();
//  //  in_num = in_data - '0';
//  //  Serial.printf("%d\n", in_num);
//  //  dot_led_pwm_value(in_num, 99);
//  //}
//  
//  //set_dot_num_74595_millis(numbers[2], main_current_millis);
//  set_dot_num_74595_millis_pwm(8, numbers[2], main_current_micros, main_current_millis);
//}
