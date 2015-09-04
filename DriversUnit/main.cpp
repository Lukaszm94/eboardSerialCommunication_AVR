/*
 * main.cpp
 *
 *  Created on: 7 lip 2015
 *      Author: Lukasz
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <math.h>
#include "adconverter.h"
#include "uart.h"
#include "../common/uartSender.h"
#include "../common/myString.h"
#include "../common/packet.h"
#include "../common/sFloat.h"
#include "../common/thermometer.h"
#include "../common/currentSensor.h"
#include "../common/sensorsManager.h"


#define LED_PIN 5



extern "C" void __cxa_pure_virtual(void);

SensorManager sensorsManager;
CurrentSensor currentSensors[CURRENT_SENSORS_COUNT];
Thermometer thermometers[THERMOMETERS_COUNT];

void initializeSensors()
{
	for(int i=0; i < THERMOMETERS_COUNT; i++) {
		sensorsManager.addSensor(&(thermometers[i]));
	}
	
	for(int i=0; i < CURRENT_SENSORS_COUNT; i++) {
		sensorsManager.addSensor(&(currentSensors[i]));
	}
}


Packet preparePacket()
{
	Packet pack;

	pack.Ta = sFloat(sensorsManager.getSingleReading(0));
	pack.Tb = sFloat(sensorsManager.getSingleReading(1));
	pack.Tc = sFloat(sensorsManager.getSingleReading(2));
	pack.Td = sFloat(sensorsManager.getSingleReading(3));
	pack.Te = sFloat(sensorsManager.getSingleReading(4));
	pack.Tf = sFloat(sensorsManager.getSingleReading(5));
	pack.Ia = sFloat(sensorsManager.getSingleReading(6));
	pack.Ib = sFloat(sensorsManager.getSingleReading(7));
	
	return pack;
}

int main(void)
{
	sei();
	DDRD |= (1<<PD1);
	uart_init(UART_BAUD_SELECT(9600, F_CPU));
	ADConverter::init();
	initializeSensors();
	uartSender sender;
	Packet pack;
	
	
	
	DDRB |= (1<<LED_PIN);
	while(1)
	{
		sensorsManager.readAll();
		pack = preparePacket();
		uart_puts(sender.getPacketCharString(pack));
		uart_endl();
		_delay_ms(1000);
	}
	return 0;
}

void __cxa_pure_virtual(void)
{
	//this should theoretically never be called
};



