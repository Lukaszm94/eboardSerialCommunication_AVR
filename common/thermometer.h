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
	Thermometer(float mvToCelsiusCoefficient_ = 0, float offset_ = 0) //offset in mv is subtracted from reading
	{
		mvToCelsiusCoefficient = mvToCelsiusCoefficient_;
		temperatureC = 20.0;
		offset = offset_;
	}
	
	void setCoefficient(float mvToCelsiusCoefficient_)
	{
		mvToCelsiusCoefficient = mvToCelsiusCoefficient_;
	}
	float getTemperature()
	{
		return temperatureC;
	}
	void insertNewReading(uint16_t newReadingMv)
	{
		temperatureC = convertRawADCToTemp(newReadingMv);
	}
private:
	float convertRawADCToTemp(uint16_t rawMv)
	{
		float temp = (rawMv - offset)*mvToCelsiusCoefficient;
	}

	
	

	float temperatureC;
	float offset;
	float mvToCelsiusCoefficient;
};


#endif /* THERMOMETER_H_ */
