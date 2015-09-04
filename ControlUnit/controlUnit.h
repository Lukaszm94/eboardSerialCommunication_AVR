#ifndef CONTROLUNIT_H
#define CONTROLUNIT_H

#include "../common/timer0.h"
#include "../common/packet.h"

#define BATTERY_LOAD_UPDATE_PERIOD_MS INTERRUPT_PERIOD_MS
#define LCD_UPDATE_PERIOD_MS 500
#define MILIAMPEROSECONDS_TO_MILIAMPEROHOURS 1.0/(60*60)

#define THERMOMETERS_COUNT 6 //also defined in sensorsManager.h, including it just for one define is pointless


class ControlUnit
{
public:
	ControlUnit()
	{
		batteryLoad = 0;
		lcdUpdateTimer = 0;
		latestPacket = NULL;
		temperaturesOk = true;
		highestTemperature = 20;
		highestTemperatureIndex = 0;
	}
	
	void init()
	{
		lcd_init();
	}

	void update()
	{
		batteryLoadUpdate();
		lcdUpdateTimer += INTERRUPT_PERIOD_MS;
		if(lcdUpdateTimer == LCD_UPDATE_PERIOD_MS) {
			lcdUpdateTimer = 0;
			lcdUpdate();
		}
	}
	
	void onNewPacketReceived(Packet *pack)
	{
		latestPacket = pack;
		analyzeNewPacket = true;
	}


private:
	void lcdUpdate()
	{
		if(latestPacket == NULL) {
			return;
		}
		if(analyzeNewPacket) {
			analyzeNewPacket = false;
			analyzePacket();
;		}
		
		LCD_clear();
		LCD_goto(0,0);
	}
	
	void batteryLoadUpdate()
	{
		if(latestPacket == NULL) {
			return;
		}
		float totalCurrent = latestPacket->Ia.toFloat() + latestPacket->Ib.toFloat();
		batteryLoad += (totalCurrent * BATTERY_LOAD_UPDATE_PERIOD_MS + 0.5)*MILIAMPEROSECONDS_TO_MILIAMPEROHOURS; //since dt is in ms, we get load in mAs, multimply that by 1/60*60 to get mAh
		
	}
	
	void analyzePacket()
	{
		//int temperatures[]
		//TODO
	}
	
	unsigned long batteryLoad; //in mAh
	unsigned long lcdUpdateTimer;
	bool analyzeNewPacket;
	Packet *latestPacket;
	
	int highestTemperature;
	int highestTemperatureIndex;
	bool temperaturesOk;
};

#endif