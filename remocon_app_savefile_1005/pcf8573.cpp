//#include "i2c.h"
//
//char char_lcd_8bit_data = 0;
//char char_lcd_8bit_inst = 0;
//
//
//void char_lcd_init()
//{
//  // RS low
//  char_lcd_8bit_data = 0;
//  i2c_byte_write(0x27, char_lcd_8bit_data);
//
//  // RW low
//  char_lcd_8bit_data &= ~(0x01 << 1);
//  i2c_byte_write(0x27, char_lcd_8bit_data);
//
//  // data 8bit
//  char_lcd_8bit_data |= 0x30;
//  i2c_byte_write(0x27, char_lcd_8bit_data);
//
//  // E high
//  char_lcd_8bit_data |= (0x01 << 2);
//  i2c_byte_write(0x27, char_lcd_8bit_data);
//
//  // E low
//  char_lcd_8bit_data &= ~(0x01 << 2);
//  i2c_byte_write(0x27, char_lcd_8bit_data);
//
//  // RS high
//  char_lcd_8bit_data |= (0x01 << 0);
//  i2c_byte_write(0x27, char_lcd_8bit_data);
//
//  // RW high
//  char_lcd_8bit_data |= (0x01 << 1);
//  i2c_byte_write(0x27, char_lcd_8bit_data);
//}
