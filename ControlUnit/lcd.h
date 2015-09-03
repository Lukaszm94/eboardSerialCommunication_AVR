/*
 * lcd.h
 *
 *  Created on: 07-12-2013
 *      Author: Lukasz
 */

#ifndef LCD_H_

#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>

#define LCD_H_


#define LCD_D7PORT B
#define LCD_D7 5
#define LCD_D6PORT B
#define LCD_D6 4
#define LCD_D5PORT B
#define LCD_D5 3
#define LCD_D4PORT B
#define LCD_D4 2

#define LCD_RSPORT B
#define LCD_RS 0

#define LCD_EPORT B
#define LCD_E 1

#define PORT(x) SPORT(x)
#define SPORT(x) (PORT##x)

#define PIN(x) SPIN(x)
#define SPIN(x) (PIN##x)

#define DDR(x) SDDR(x)
#define SDDR(x) (DDR##x)

#define SET_RS PORT(LCD_RSPORT) |= (1<<LCD_RS)
#define CLR_RS PORT(LCD_RSPORT) &= ~(1<<LCD_RS)

#define SET_E PORT(LCD_EPORT) |= (1<<LCD_E)
#define CLR_E PORT(LCD_EPORT) &= ~(1<<LCD_E)

#define LCDclear 0x01
#define LCDhome 0x02


void data_dir_out(void);
void lcd_sendHalf(uint8_t data);
void _lcd_write_byte(unsigned char _data);
void lcd_write_cmd(uint8_t cmd);
void lcd_write_data(unsigned char data);
void lcd_init(void);
void LCD_str (char * str);
void LCD_char (char z);
void LCD_int (int x);
void LCD_clear (void);
void LCD_home (void);
void LCD_goto (unsigned char x, unsigned char y);
void LCD_erase_line(unsigned char y);
void lcd_cursor_visible(char x);


#endif /* LCD_H_ */
