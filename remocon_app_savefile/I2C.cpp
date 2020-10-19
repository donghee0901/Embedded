#include "I2C.h"

#define SCL 19
#define SDA 18

void i2c_init()
{
  pinMode(SCL, OUTPUT);
  pinMode(SDA, OUTPUT);

  digitalWrite(SCL, HIGH);
  digitalWrite(SDA, HIGH);
  //  DDRC |= 0x01 << SDA;
  //  DDRC |= 0x01 << SCL; //PC4 : SDA, PC5 : SCL
  //
  //  PORTC |= 0x01 << SDA;
  //  PORTC |= 0x01 << SCL;
}

void i2c_start()
{
  digitalWrite(SDA, LOW);
  digitalWrite(SCL, LOW);

  //  PORTC &= ~(0x01 << SDA); // SDA LOW -- start
  //  PORTC &= ~(0x01 << SCL); // SCL LOW
}

void i2c_stop()
{
  digitalWrite(SDA, LOW);
  digitalWrite(SCL, HIGH);
  digitalWrite(SDA, HIGH);


  //  PORTC &= ~(0x01 << SDA); // SDA LOW
  //  PORTC |= (0x01 << SCL);  // SCL HIGH
  //  PORTC |= (0x01 << SDA);  // SDA HIGH -- stop
}

void data_8bit_set(char data)
{
  for (int i = 0; i < 8; i++) {
    if (data & 0x01 << (7 - i)) {
      digitalWrite(SDA, HIGH);
    }
    else {
      digitalWrite(SDA, LOW);
    }
    digitalWrite(SCL, HIGH);
    digitalWrite(SCL, LOW);
  }
}

void i2c_ack()
{
  digitalWrite(SCL, HIGH);
  digitalWrite(SCL, LOW);
}

void i2c_byte_write(char addr, char data)
{
  i2c_start();
  data_8bit_set(addr << 1);
  i2c_ack();
  data_8bit_set(data);
  i2c_ack();
  i2c_stop();
}
