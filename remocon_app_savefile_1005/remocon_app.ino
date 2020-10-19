#include "servo.h"
#define SERVO_PORT 4
#define SERVO_PORT_COUNT 2

char servo_port[SERVO_PORT_COUNT] = {5, 4};

void setup()
{
  //  servo_init(SERVO_PORT);
  servo_init_many(servo_port, SERVO_PORT_COUNT);
}
int servo_porision = 0;
unsigned long c_micros = 0;
unsigned long c_millis = 0;
unsigned long p_millis1 = 0;
unsigned long p_millis2 = 0;
int servo_degree = 0; // servo_degree : 0 ~ 180
unsigned char servo_duty_ptr[SERVO_PORT_COUNT] = {0};
int servo_duty1 = 22;  // servo_duty : 22 ~ 720

int servo_duty2 = 22;  // servo_duty : 22 ~ 72

void loop()
{
  //  servo_position(servo_porision);
  //  servo_porision++;
  //  if (servo_porision == 180) servo_porision = 0;
  c_micros = micros();
  c_millis = millis();

  if (c_millis - p_millis1 > 50)
  {
    p_millis1 = c_millis;
    //    servo_degree++;
    //    if(servo_degree > 180) servo_degree = 0;
    //    servo_duty = (int)((700 + (int)((float)(180 - servo_degree) / 180.0f) * 1600) / 32 + 0.5);

    servo_duty_ptr[0]++;
    if (servo_duty_ptr[0] == 72)servo_duty_ptr[0] = 22;

    //    servo_degree++;
    //    if (servo_degree == 72)servo_degree = 22;
  }
  if (c_millis - p_millis2 > 100)
  {
    p_millis2 = c_millis;

    servo_duty_ptr[1]++;
    if (servo_duty_ptr[1] == 72)servo_duty_ptr[1] = 22;
  }
  //  int duty = (int)((700 + (int)((float)(180 - degree) / 180.0f) * 1600) / 32 + 0.5);
  //  servo_degree : 22 ~ 72
//  servo_position_micros(servo_duty, c_micros);
  servo_position_micros_many(servo_duty_ptr, c_micros);
}
