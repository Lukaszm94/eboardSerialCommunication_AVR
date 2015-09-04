/*
 * main.cpp
 *
 *  Created on: 7 lip 2015
 *      Author: Lukasz
 */

#include <avr/io.h>
#include <avr/interrupt.h>

#include "uart.h"
#include "lcd.h"
#include "controlUnit.h"
#include "../common/packet.h"
#include "../common/debug.h"
#include "../common/sFloat.h"
#include "../common/myString.h"
#include "../common/uartReceiver.h"
#include "../common/timer0.h"


char uartGetChar()
{
	char c = uart_getc() & 0x00FF;
	return c;
}

void printReceivedPacket(Packet pack)
{
	Debug::println("Received packet:");
	Debug::print("Ia: ");
	Debug::print(pack.Ia.toString());
	Debug::print(", Ib: ");
	Debug::print(pack.Ib.toString());
	Debug::print(", Ta: ");
	Debug::print(pack.Ta.toString());
	Debug::print(", Tb: ");
	Debug::print(pack.Tb.toString());
	Debug::print(", Tc: ");
	Debug::print(pack.Tc.toString());
	Debug::print(", Td: ");
	Debug::print(pack.Td.toString());
	Debug::print(", Te: ");
	Debug::print(pack.Te.toString());
	Debug::print(", Tf: ");
	Debug::println(pack.Tf.toString());
}


void displayPacket(Packet pack)
{
	LCD_clear();
	LCD_goto(0,0);
	LCD_str("Ia");
	LCD_int(pack.Ia.getInteger());
	LCD_str("Ib");
	LCD_int(pack.Ib.getInteger());
	LCD_str("Ta");
	LCD_int(pack.Ta.getInteger());
	LCD_str("Tb");
	LCD_int(pack.Tb.getInteger());
	LCD_goto(0,1); //second line
	LCD_str("Tc");
	LCD_int(pack.Tc.getInteger());
	LCD_str("Td");
	LCD_int(pack.Td.getInteger());
	LCD_str("Te");
	LCD_int(pack.Te.getInteger());
	LCD_str("Tf");
	LCD_int(pack.Tf.getInteger());
}

Timer0 timer;
volatile bool interruptFlag = false;

int main()
{
	DDRD |= (1<<PD1);
	sei();
	Debug::init();
	
	uartReceiver rx;
	Packet receivedPacket;
	ControlUnit CU;
	
	CU.init();
	timer.init();
	
	while(1)
	{
		if(interruptFlag) {
			interruptFlag = false;
			CU.update();
		}
		if(uart_available())
		{
			rx.receiveNewChar(uartGetChar());
			while(uart_available()) {
				rx.receiveNewChar(uartGetChar());
			}
			if(rx.parseBuffer()) {
				receivedPacket = rx.getPacket();
				rx.clear();
				printReceivedPacket(receivedPacket);
				CU.onNewPacketReceived(&receivedPacket);
			}
		}
	}

}


ISR(TIMER0_COMPA_vect)
{
	interruptFlag = true;
}

