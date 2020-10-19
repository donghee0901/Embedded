#include "test.h"
#include "remocon.h"
#include "ultrasonic.h"
#include "I2C.h"

#define REMOCON_PIN 2
#define ULTRASONIC_ECHO_PIN 3
#define ULTRASONIC_TRIGGER_PIN 4

unsigned long c_millis;
unsigned long p_millis_ultra;
unsigned long p_millis_I2C;

float ultrasonic_dist = 0;

char remocon_number = 0;

int I2C_toggle = 0;

extern int test_count;
void setup()
{
  Serial.begin(9600);
  remocon_init(REMOCON_PIN);
  ultrasonic_init(ULTRASONIC_ECHO_PIN, ULTRASONIC_TRIGGER_PIN);
  i2c_init();
}
void loop()
{
  c_millis = millis();
  if (remocon_callback(&remocon_number))
  {
    int_callback_flag_clear();
    Serial.println(remocon_number);
  }
  if (c_millis - p_millis_ultra > 1000)
  {
    p_millis_ultra = c_millis;
    ultrasonic_trigger();
  }
  if (ultrasonic_callback(&ultrasonic_dist))
  {
    ultrasonic_callback_flag_clear();
    Serial.println(ultrasonic_dist);
  }
  if (c_millis - p_millis_I2C > 1000)
  {
    p_millis_I2C = c_millis;
    if (I2C_toggle == 0) {
      I2C_toggle = 1;
      i2c_byte_write(0x27, 0x08);
    }
    else {
      I2C_toggle = 0;
      i2c_byte_write(0x27, 0x00);
    }
  }
}
