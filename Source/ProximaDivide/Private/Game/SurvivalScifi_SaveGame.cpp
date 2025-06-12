// Written and owned by Lukasz Dziedziczak. Copywrite 2025


#include "Game/SurvivalScifi_SaveGame.h"

void USurvivalScifi_SaveGame::AdvanceHours(int HoursToAdvance)
{
	if (HoursToAdvance <= 0) return;

	if (TimeData.Day == 0)
	{
		TimeData.Day = 1;
		TimeData.Hour = 8;
		TimeData.SecondsLeftInHour = 0;
	}

	else
	{
		// advance save slot hour, day if needed
		for (int h = 0; h < HoursToAdvance; h++)
		{
			TimeData.Hour++;
			if (TimeData.Hour >= 24)
			{
				TimeData.Hour = 0;
				TimeData.Day++;
			}
		}

		// add extra hour to clear remaining time in hour
		TimeData.SecondsLeftInHour = 0;
		TimeData.Hour++;
	}
}
