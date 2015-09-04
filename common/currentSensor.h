#ifndef CURRENTSENSOR_H
#define CURRENTSENSOR_H

#include "sensorInterface.h"

#define ACS709_CONVERSION_COEFFICIENT 35.714 // A/V
#define ACS709_OFFSET 2.5 // V

class CurrentSensor : public Sensor
{
public:
	static float offset;
	static float VToACoefficient;
	
	void insertNewReading(float readV)
	{
		measuredValue = convertRawADCToTemp(readV);
	}
	
private:
	float convertRawADCToTemp(float rawV)
	{
		if(rawV < offset) {
			rawV = offset;
		}
		float temp = (rawV - offset)*VToACoefficient;
		return temp;
	}

};

float CurrentSensor::VToACoefficient = ACS709_CONVERSION_COEFFICIENT;
float CurrentSensor::offset = ACS709_OFFSET;
#endif