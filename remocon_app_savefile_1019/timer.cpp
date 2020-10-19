//#include "timer.h"
//
//void timer2_ovf_init(char prescale)
//{
//  TCCR2A = 0x00;
//  if(prescale == 8) TCCR2B = 0x02;
//
//  TCNT2 = 256 - 64;
//  TIMSK2 = 0x01;
//}
//
//ISR(TIMER2_OVF_vect)
//{
//  if (servo_count_lib == 625) {
//      servo_count_lib = 0;
//      for (int i = 0; i < g_servo_port_count; i++)
//      {
//        digitalWrite(g_servo_port_many[i], HIGH);
//      }
//    }
//    for (int i = 0; i < g_servo_port_count; i++) {
//      if (servo_count_lib == duty_servo_lib[i])
//      {
//        digitalWrite(g_servo_port_many[i], LOW);
//      }
//    }
//
//    servo_count_lib++;
//  }
//}
