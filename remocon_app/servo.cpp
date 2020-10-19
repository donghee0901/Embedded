#include "servo.h"
#define SERVO_NUM 10

// 20ms 주기, 0.7 ~ 2.3

char g_servo_port = 0;
char g_servo_port_many[SERVO_NUM];
int duty_servo_lib[SERVO_NUM];

unsigned long p_micros_servo = 0;
int servo_count_lib = 0;
int g_servo_port_count = 0;

void servo_init(char port)
{
  pinMode(port, OUTPUT);
  g_servo_port = port;
}

void servo_init_many(char* port, int servo_port_count)
{
  g_servo_port_count = servo_port_count;
  for (int i = 0; i < servo_port_count; i++)
  {
    pinMode(port[i], OUTPUT);
    g_servo_port_many[i] = port[i];
  }
}

void servo_position(unsigned char degree)
{
  if (degree > 180)
  {
    degree = 180;
  } else if (degree < 0)
  {
    degree = 0;
  }

  int duty = 700 + (int)(((float)(180 - degree) / 180.0) * 1600);

  digitalWrite(g_servo_port, HIGH);
  delayMicroseconds(duty);
  digitalWrite(g_servo_port, LOW);
  delay(17);
  delayMicroseconds(duty);
}

void servo_position_micros(unsigned char degree, unsigned long c_micros)
{

  if (c_micros - p_micros_servo > 32)
  {
    p_micros_servo = c_micros;
    if (degree > 72)
    {
      degree = 72;
    } else if (degree < 22)
    {
      degree = 22;
    }
    int duty = degree;
    if (servo_count_lib == 625) {
      servo_count_lib = 0;
      digitalWrite(g_servo_port, HIGH);
    }
    else if (servo_count_lib == duty)
    {
      digitalWrite(g_servo_port, LOW);
    }
    servo_count_lib++;
  }
}


void servo_position_micros_many(unsigned char *degree, unsigned long c_micros)
{

  if (c_micros - p_micros_servo > 32)
  {
    p_micros_servo = c_micros;
    for (int i = 0; i < g_servo_port_count; i++)
    {
      if (degree[i] > 72)
      {
        degree[i] = 72;
      } else if (degree[i] < 22)
      {
        degree[i] = 22;
      }
      duty_servo_lib[i] = degree[i];
    }
    if (servo_count_lib == 625) {
      servo_count_lib = 0;
      for (int i = 0; i < g_servo_port_count; i++)
      {
        digitalWrite(g_servo_port_many[i], HIGH);
      }
    }
    for (int i = 0; i < g_servo_port_count; i++) {
      if (servo_count_lib == duty_servo_lib[i])
      {
        digitalWrite(g_servo_port_many[i], LOW);
      }
    }

    servo_count_lib++;
  }
}
