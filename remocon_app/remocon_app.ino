#include "keymatrix.h"

// 4x4 key matrix pin : Row1, Row2, Row3, Row4, Col1, Col2, Col3, Col4
char keymatrix_pin_main[8] = {2, 3, 4, 5, 6, 7, 8, 9};

unsigned long c_millis = 0;
unsigned long c_micros = 0;

int pwm_count;
int pwm_duty = 1;


void setup()
{
  Serial.begin(9600);
  keymatrix_init(keymatrix_pin_main);
  pinMode(13, OUTPUT);
}

unsigned long p_micros_pwm;

void loop()
{
  char key_in = 0;

  c_millis = millis();
  c_micros = micros();
  keymatrix_input_millis(&key_in, c_millis);
  //  keymatrix_input_delay(&key_in);


  if (key_in != 0) {
    Serial.printf("key_in = %d\n", key_in);
    pwm_duty = key_in;
  }

  if (p_micros_pwm - c_micros > 100)
  {
    p_micros_pwm = c_micros;

    if (pwm_count == 100)
    {
      pwm_count = 0;
      digitalWrite(13, HIGH);
    }
    else if (pwm_count == pwm_duty * 5)
    {
      digitalWrite(13, LOW);
    }

    pwm_count++;
  }
}
