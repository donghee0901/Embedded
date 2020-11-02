#include "keymatrix.h"

#define ROW_PTR 0
#define COL_PTR 4

char *keymatrix_pin;
char curr_column;
char flag_row[4][4] = {0};
char onClick = 0;
unsigned long p_millis = 0;

void keymatrix_init(char *pin_num)
{
  keymatrix_pin = pin_num;

  for (int i = 0; i < 4; i++)
  {
    pinMode(keymatrix_pin[i], INPUT); // Row1 ~ Row4
    pinMode(keymatrix_pin[i + 4], OUTPUT); // Col1 ~ Col4
  }
}

char keymatrix_input_delay(char *in_value)
{
  char key_input = 0;
  // 1. all column off : LOW
  for (int i = 0; i < 4; i++) digitalWrite(keymatrix_pin[COL_PTR + i], LOW);

  // 2. one column on : HIGH
  digitalWrite(keymatrix_pin[COL_PTR + curr_column], HIGH);

  // 3. Row read
  for (int i = 0; i < 4; i++) {
    key_input = digitalRead(keymatrix_pin[ROW_PTR + i]);

    if (key_input == 1 && flag_row[i][curr_column] == 0 && onClick == 0) {
      flag_row[i][curr_column] = 1;
      onClick = 1;
      *in_value = key_input + curr_column + (i * 4);
      //      Serial.printf("in_value = %d\n", *in_value);
    }
    else if (key_input == 0 && flag_row[i][curr_column] == 1 && onClick == 1)
    {
      flag_row[i][curr_column] = 0;
      onClick = 0;
      *in_value = 0;
    }
  }


  // 4. delay
  curr_column++;
  if (curr_column == 4)curr_column = 0;

  delay(10);
}

char keymatrix_input_millis(char *in_value, unsigned long c_millis)
{
  if (p_millis - c_millis > 10)
  {
    p_millis = c_millis;
    char key_input = 0;
    // 1. all column off : LOW
    for (int i = 0; i < 4; i++) digitalWrite(keymatrix_pin[COL_PTR + i], LOW);

    // 2. one column on : HIGH
    digitalWrite(keymatrix_pin[COL_PTR + curr_column], HIGH);

    // 3. Row read
    for (int i = 0; i < 4; i++) {
      key_input = digitalRead(keymatrix_pin[ROW_PTR + i]);

      if (key_input == 1 && flag_row[i][curr_column] == 0 && onClick == 0) {
        flag_row[i][curr_column] = 1;
        onClick = 1;
        *in_value = key_input + curr_column + (i * 4);
        //      Serial.printf("in_value = %d\n", *in_value);
      }
      else if (key_input == 0 && flag_row[i][curr_column] == 1 && onClick == 1)
      {
        flag_row[i][curr_column] = 0;
        onClick = 0;
        *in_value = 0;
      }
    }
    
    // 4. delay
    curr_column++;
    if (curr_column == 4)curr_column = 0;
  }
}
