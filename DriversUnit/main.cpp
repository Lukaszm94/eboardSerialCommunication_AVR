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
#include "thermometer.h"
#include "uart.h"
#include "../common/uartSender.h"
#include "../common/myString.h"
#include "../common/packet.h"
#include "../common/sFloat.h"


#define LED_PIN 5

#define CURRENT_SENSOR_1_PIN 6
#define CURRENT_SENSOR_2_PIN 7

#define CURRENT_SAMPLES_COUNT 10
#define CURRENT_SENSOR_COEFFICIENT_x10 357// V -> A

const int samples = 50;

float convertVoltageToCurrent(float voltage) {
	float curr = (voltage - 2.5)/CURRENT_SENSOR_COEFFICIENT;
	return fabs(curr);
}


ADConverter adc;

float current1;
float current2;

Packet preparePacket()
{
	Packet pack;
	
	
	current1 = convertVoltageToCurrent(adc.getAverageVoltage(CURRENT_SENSOR_1_PIN, samples));
	current2 = convertVoltageToCurrent(adc.getAverageVoltage(CURRENT_SENSOR_2_PIN, samples));
	
	return pack;
}

int main(void)
{
	sei();
	DDRD |= (1<<PD1);
	uart_init(UART_BAUD_SELECT(9600, F_CPU));
	
	uartSender sender;
	Packet pack;
	
	
	
	DDRB |= (1<<LED_PIN);
	while(1)
	{
		pack = preparePacket();
		uart_puts(sender.getPacketCharString(pack));
	}
	return 0;
}


