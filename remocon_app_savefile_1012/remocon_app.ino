#include "gpio.h"
#include "fnd.h"

// FND A,B,C,D,E,F,G,DP
char fnd_pin[8] = {4, 5, 6, 7, 8, 9, 10, 11};
// FND A,B,C,D,E,F,G,DP,Common1,Common2,Common3,Common4
char fnd_pin2[12] = {4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};


void setup()
{
  Serial.begin(9600);
  //  pinMode(13, OUTPUT);
  //  pin_mode(13, OUTPUT);

  //  fnd_init_1(fnd_pin, C_CATHODE);
  fnd_init(4, fnd_pin2, C_ANODE);

}
int fndNumber = 0;
unsigned long c_millis = 0;
unsigned long p_millis = 0;

void loop()
{
  c_millis = millis();

  if (c_millis - p_millis > 50)
  {
    p_millis = c_millis;
    if (fndNumber == 10000)fndNumber = 0;
    fndNumber++;
  }
  fnd_num_millis(c_millis, fndNumber);
  //  for (int i = 0; i < 10; i++)
  //  {
  //    fnd_num_2(20 + i);
  //    delay(1000);
  //  }

  //  int in_value = digital_read(2);
  //  Serial.printf("in_value = %d\n", in_value);
  //  delay(100);

  //  //  digitalWrite(13,HIGH);
  //  //  PORTB |= 0x20;
  //  digital_write(13, HIGH);
  //  delay(1000);
  //  //  digitalWrite(13,LOW);
  //  digital_write(13, LOW);
  //  delay(1000);
}
