// Written and owned by Lukasz Dziedziczak. Copywrite 2025


#include "Game/SurvivalScifi_SaveGame.h"

void USurvivalScifi_SaveGame::AdvanceHours(int HoursToAdvance)
{
	// advance save slot hour, day if needed
	for (int h = 0; h < HoursToAdvance; h++)
	{
		WorldData.Hour++;
		if (WorldData.Hour >= 24)
		{
			WorldData.Hour = 0;
			WorldData.Day++;
		}
	}

	// add extra hour to clear remaining time in minute
	WorldData.SecondsLeftInHour = 0;
	WorldData.Hour++;
}
