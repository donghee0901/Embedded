#ifndef KEYMATRIX_H
#define KEYMATRIX_H

#include "Arduino.h"

void keymatrix_init(char *pin_num);
char keymatrix_input_delay(char *in_value);
char keymatrix_input_millis(char *in_value, unsigned long c_millis);

#endif
