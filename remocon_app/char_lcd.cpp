#include "char_lcd.h"

//이곳은 라이브러리
//이친구도 define이 아니라 나중에 받아서 처리

char RS;
char RW;
char E;
char DB[8];

void char_lcd_init_8bit(char *pin) {
  RS = pin[0];
  RW = pin[1];
  E = pin[2];

  for (int i = 0; i < 8; i++)
  {
    DB[i] = pin[i + 3];
  }

  for (int i = 0; i < 11; i++) {
    pinMode(pin[i], OUTPUT); // 전체 핀 OUTPUT설정
  }
  digitalWrite(RS, HIGH);
  digitalWrite(RW, LOW);

  char_lcd_inst_8bit(0x30);
  char_lcd_inst_8bit(0x30);
  char_lcd_inst_8bit(0x30);
  char_lcd_inst_8bit(0x38);
  char_lcd_inst_8bit(0x06);
  char_lcd_inst_8bit(0x0c);
  char_lcd_inst_8bit(0x80);
  char_lcd_inst_8bit(0x01);

  delay(10); //clear 명령어 실행시간을 맞추기 위함. ( 0x01 )

}
void char_lcd_init_4bit(char *pin) {
  RS = pin[0];
  RW = pin[1];
  E = pin[2];

  for (int i = 0; i < 4; i++)
  {
    DB[i] = pin[i + 3];
  }

  for (int i = 0; i < 7; i++) {
    pinMode(pin[i], OUTPUT); // 전체 핀 OUTPUT설정
  }
  digitalWrite(RS, HIGH);
  digitalWrite(RW, LOW);

  char_lcd_inst_8bit(0x30);
  char_lcd_inst_8bit(0x30);
  char_lcd_inst_8bit(0x30);
  char_lcd_inst_8bit(0x28);

  char_lcd_inst_4bit(0x28);
  char_lcd_inst_4bit(0x06);
  char_lcd_inst_4bit(0x0c);
  char_lcd_inst_4bit(0x80);
  char_lcd_inst_4bit(0x01);

  delay(10); //clear 명령어 실행시간을 맞추기 위함. ( 0x01 )

}
void char_lcd_inst_8bit(unsigned char inst) {
  digitalWrite(RS, LOW);

  for (int i = 0; i < 8; i++ ) {
    if (inst & (0x01 << i )) {
      digitalWrite(DB[i], HIGH);
    } else {
      digitalWrite(DB[i], LOW);
    }
  }

  digitalWrite(E, HIGH);
  digitalWrite(E, LOW);

  digitalWrite(RS, HIGH);

  delayMicroseconds(50); // delay 50us
}

void char_lcd_inst_4bit(unsigned char inst) {
  char_lcd_inst_4bit_high(inst);
  char_lcd_inst_4bit_low(inst);
}

void char_lcd_inst_4bit_high(unsigned char inst_high) {
  digitalWrite(RS, LOW);

  for (int i = 0; i < 4; i++ ) {
    if (inst_high & (0x10 << i)) {
      digitalWrite(DB[i], HIGH);
    } else {
      digitalWrite(DB[i], LOW);
    }
  }

  digitalWrite(E, HIGH);
  digitalWrite(E, LOW);

  digitalWrite(RS, HIGH);

  delayMicroseconds(50); // delay 50us
}

void char_lcd_inst_4bit_low(unsigned char inst_low) {
  digitalWrite(RS, LOW);

  for (int i = 0; i < 4; i++ ) {
    if (inst_low & (0x01 << i)) {
      digitalWrite(DB[i], HIGH);
    } else {
      digitalWrite(DB[i], LOW);
    }
  }

  digitalWrite(E, HIGH);
  digitalWrite(E, LOW);

  digitalWrite(RS, HIGH);

  delayMicroseconds(50); // delay 50us
}

void char_lcd_data_8bit(unsigned char data) {

  for (int i = 0; i < 8; i++ ) {
    if (data & (0x01 << i )) {
      digitalWrite(DB[i], HIGH);
    } else {
      digitalWrite(DB[i], LOW);
    }
  }

  digitalWrite(E, HIGH);
  digitalWrite(E, LOW);


  delayMicroseconds(50); // delay 50us
}

void char_lcd_data_4bit(unsigned char data) {
  char_lcd_inst_4bit_high(data);
  char_lcd_inst_4bit_low(data);
}

void char_lcd_data_4bit_high(unsigned char data_high) {
  for (int i = 0; i < 4; i++ ) {
    if (data_high & (0x10 << i)) {
      digitalWrite(DB[i], HIGH);
    } else {
      digitalWrite(DB[i], LOW);
    }
  }

  digitalWrite(E, HIGH);
  digitalWrite(E, LOW);

  delayMicroseconds(50); // delay 50us
}

void char_lcd_data_4bit_low(unsigned char data_low) {
  for (int i = 0; i < 4; i++ ) {
    if (data_low & (0x01 << i)) {
      digitalWrite(DB[i], HIGH);
    } else {
      digitalWrite(DB[i], LOW);
    }
  }

  digitalWrite(E, HIGH);
  digitalWrite(E, LOW);

  delayMicroseconds(50); // delay 50us
}
