#ifndef ULTRASONIC_H
#define ULTRASONIC_H

void ultrasonic_init(char int_pin_num, char trigger_pin_num);
char ultrasonic_callback(float *distance);
void ultrasonic_callback_flag_clear();
void ultrasonic_trigger();
void ultrasonic_ISR();

#endif
