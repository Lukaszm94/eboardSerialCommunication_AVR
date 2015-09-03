/*
 * thermometer.h
 *
 *  Created on: 19 lip 2015
 *      Author: LukaszSSD
 */

#ifndef THERMOMETER_H_
#define THERMOMETER_H_

#define LM35_CONVERSION_RATIO 0.01 //V -> C

class Thermometer
{
public:
	Thermometer(float conversionRatio)
	{
		conversionRatioFromVoltsToCelsius = conversionRatio;
		temperatureC = 20.0;
	}
	float getTemperature()
	{
		return temperatureC;
	}
	void insertNewReading(float newReading)
	{
		temperatureC = convertRawADCToTemp(newReading);
	}
private:
	float convertVoltsToTemperature(float voltage)
	{
		return voltage*conversionRatioFromVoltsToCelsius;
	}

	float temperatureC;
	float conversionRatioFromVoltsToCelsius;
};


#endif /* THERMOMETER_H_ */
