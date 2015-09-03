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


#define LED_PIN 5

#define CURRENT_SENSOR_1_CHANNEL 6
#define CURRENT_SENSOR_2_CHANNEL 7

#define CURRENT_SAMPLES_COUNT 10
#define CURRENT_SENSOR_COEFFICIENT_x10 357// V -> A

#define TEMP_M1_CHANNEL 0
#define TEMP_M2_CHANNEL 1
#define TEMP_D1_CHANNEL 2
#define TEMP_D2_CHANNEL 3
#define TEMP_I1_CHANNEL 4
#define TEMP_I2_CHANNEL 5

#define THERMOMETER_SAMPLES_COUNT 5
#define LM35_MV_TO_C_COEFF 0.1 //degC per mV
#define THERMOMETERS_COUNT 6

const int samples = 50;


float current1;
float current2;
Thermometer thermometers[THERMOMETERS_COUNT];

void initializeSensors()
{
	for(int i=0; i < THERMOMETERS_COUNT; i++) {
		thermometers[i].setCoefficient(LM35_MV_TO_C_COEFF);
	}
}

void readTemperatures()
{
	for(int i=0; i < THERMOMETERS_COUNT; i++) {
		thermometers[i].insertNewReading(ADConverter::getAverageVoltage(i, THERMOMETER_SAMPLES_COUNT) * 1000);
	}
}

Packet preparePacket()
{
	Packet pack;
	
	
	//current1 = convertVoltageToCurrent(adc.getAverageVoltage(CURRENT_SENSOR_1_PIN, samples));
	//current2 = convertVoltageToCurrent(adc.getAverageVoltage(CURRENT_SENSOR_2_PIN, samples));
	
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
		pack = preparePacket();
		uart_puts(sender.getPacketCharString(pack));
	}
	return 0;
}


