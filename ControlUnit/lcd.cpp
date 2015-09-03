/*
 * lcd.c
 *
 *  Created on: 06-12-2013
 *      Author: Lukasz
 */


#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include "lcd.h"



void data_dir_out(void)
{
	DDR(LCD_D7PORT) |= (1<<LCD_D7);
	DDR(LCD_D6PORT) |= (1<<LCD_D6);
	DDR(LCD_D5PORT) |= (1<<LCD_D5);
	DDR(LCD_D4PORT) |= (1<<LCD_D4);

	DDR(LCD_RSPORT) |= (1<<LCD_RS);
	DDR(LCD_EPORT) |= (1<<LCD_E);
}

void lcd_sendHalf(uint8_t data)
{
	if (data&(1<<0)) PORT(LCD_D4PORT) |= (1<<LCD_D4);
		else PORT(LCD_D4PORT) &=~(1<<LCD_D4);
	if (data&(1<<1)) PORT(LCD_D5PORT) |= (1<<LCD_D5);
		else PORT(LCD_D5PORT) &=~(1<<LCD_D5);
	if (data&(1<<2)) PORT(LCD_D6PORT) |= (1<<LCD_D6);
		else PORT(LCD_D6PORT) &=~(1<<LCD_D6);
	if (data&(1<<3)) PORT(LCD_D7PORT) |= (1<<LCD_D7);
		else PORT(LCD_D7PORT) &=~(1<<LCD_D7);
}

void _lcd_write_byte(unsigned char _data)
{
	data_dir_out();
	SET_E;
	lcd_sendHalf(_data>>4);
	CLR_E;

	SET_E;
	lcd_sendHalf(_data);
	CLR_E;
	_delay_us(150);
}

void lcd_write_cmd(uint8_t cmd)
{
	CLR_RS;
	_lcd_write_byte(cmd);
}

void lcd_write_data(unsigned char data)
{
	SET_RS;
	_lcd_write_byte(data);
}

void lcd_init(void)
{
	data_dir_out();

	CLR_RS;
	CLR_E;
	_delay_ms(20); //1

	lcd_write_cmd(0x03);//2
	_delay_ms(5);//3

	lcd_write_cmd(0x03);//4
	_delay_us(1000);//5

	lcd_write_cmd(0x03);//6
	_delay_us(1000);

	lcd_write_cmd (0x02);
	lcd_write_cmd (0x28); //function set
	lcd_write_cmd (0x08); //display off
	LCD_clear();
	lcd_write_cmd (0x06); //entry mode set
	lcd_write_cmd (0x0f); //display on
}

void LCD_str (char * str)
{
	while(*str)
	{
		lcd_write_data(*str);
		str++;
	}
}
void LCD_char (char z)
{
	lcd_write_data(z);
}

void LCD_int (int x)
{	char tab[10];
	itoa(x,tab,10);
	LCD_str(tab);
}

void LCD_clear (void)
{
	lcd_write_cmd(LCDclear);
	_delay_ms(2);
}

void LCD_home (void)
{
	lcd_write_cmd(LCDhome);
	_delay_ms(2);
}

void LCD_goto (unsigned char x, unsigned char y)
{
	lcd_write_cmd(0x80 | (x+ (0x40 * y)));
}

void LCD_erase_line(unsigned char y)
{
	uint8_t x=0;
	while(x<16)
	{
		lcd_write_cmd(0x80 | (x+ (0x40 * y)));
		lcd_write_data(0x20);
		x++;
	}
	lcd_write_cmd(0x80|(0x40*y));
}

void lcd_cursor_visible(char x)
{
	if(x)
		LCD_goto(0,0);
	else
		LCD_goto(20,0);
}




