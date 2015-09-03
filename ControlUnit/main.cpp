/*
 * main.cpp
 *
 *  Created on: 7 lip 2015
 *      Author: Lukasz
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include "Debug_atmega328p.h"
#include "lcd.h"

#define serial_packet_min_size 4

char uartGetChar()
{
	while(!uart_available()) {
	_delay_ms(5);
	}
	char received = (uart_getc() & 0x00FF);
	uart_putc(received);
	return received;
}

int uartGetInt()
{
	int number = 0;
	char uartLetter = uartGetChar();
	//uart_puts("Int: ");
	while(uartLetter >= '0' && uartLetter <= '9') {
		number *=10;
		number += (uartLetter - '0');
		uartLetter = uartGetChar();
		uart_putc(uartLetter);
	}
	//uart_puts("Parsing int finished");
	uart_endl();
	return number;
}

void readSerialPacket(int *firstVar, int *secondVar) {
	while(uartGetChar() != 's') {
		_delay_ms(5);
	}
	*firstVar = uartGetInt();
	*secondVar = uartGetInt();
}

void printCurrents(int i1, int i2)
{
	LCD_clear();
	LCD_str("I1: ");
	LCD_int(i1);
	LCD_goto(0,1); //goto second line
	LCD_str("I2: ");
	LCD_int(i2);
}

int main()
{
	int current1 = 2;
	int current2 = 0;
	DDRD |= (1<<1);
	sei();
	lcd_init();
	Debug::init();
	
	while(1)
	{
		if(uart_available() >= serial_packet_min_size)
		{
			readSerialPacket(&current1, &current2);
			printCurrents(current1, current2);
		
		}
		_delay_ms(10);
	}

}


