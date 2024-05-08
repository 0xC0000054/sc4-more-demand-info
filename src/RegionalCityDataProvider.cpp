//////////////////////////////////////////////////////////////////////////
//
// This file is part of sc4-more-demand-info, a DLL Plugin for SimCity 4
// that provides more game variables with RCI demand information.
//
// Copyright (c) 2024 Nicholas Hayes
//
// This file is licensed under terms of the MIT License.
// See LICENSE.txt for more information.
//
//////////////////////////////////////////////////////////////////////////

#include "RegionalCityDataProvider.h"
#include "cIGZMessage2Standard.h"
#include "cISC4App.h"
#include "cISC4Region.h"
#include "cISC4RegionalCity.h"
#include "GZServPtrs.h"

RegionalCityDataProvider::RegionalCityDataProvider()
	: regionPopulationTotals{},
	  currentCityPopulationTotals{},
	  regionalCityPopulationTotals{}
{
}

const PopulationTotals& RegionalCityDataProvider::GetRegionTotalPopulation() const
{
	return regionPopulationTotals;
}

void RegionalCityDataProvider::PostCityInit()
{
	UpdateRegionalCityPopulationTotals();
	UpdateCurrentCityPopulationTotals();
	UpdateRegionPopulationTotals();
}

void RegionalCityDataProvider::PostSave()
{
	UpdateCurrentCityPopulationTotals();
	UpdateRegionPopulationTotals();
}

void RegionalCityDataProvider::UpdateRegionPopulationTotals()
{
	regionPopulationTotals.res1Pop = currentCityPopulationTotals.res1Pop + regionalCityPopulationTotals.res1Pop;
	regionPopulationTotals.res2Pop = currentCityPopulationTotals.res2Pop + regionalCityPopulationTotals.res2Pop;
	regionPopulationTotals.res3Pop = currentCityPopulationTotals.res3Pop + regionalCityPopulationTotals.res3Pop;
	regionPopulationTotals.cs1Pop = currentCityPopulationTotals.cs1Pop + regionalCityPopulationTotals.cs1Pop;
	regionPopulationTotals.cs2Pop = currentCityPopulationTotals.cs2Pop + regionalCityPopulationTotals.cs2Pop;
	regionPopulationTotals.cs3Pop = currentCityPopulationTotals.cs3Pop + regionalCityPopulationTotals.cs3Pop;
	regionPopulationTotals.co2Pop = currentCityPopulationTotals.co2Pop + regionalCityPopulationTotals.co2Pop;
	regionPopulationTotals.co3Pop = currentCityPopulationTotals.co3Pop + regionalCityPopulationTotals.co3Pop;
	regionPopulationTotals.irPop = currentCityPopulationTotals.irPop + regionalCityPopulationTotals.irPop;
	regionPopulationTotals.idPop = currentCityPopulationTotals.idPop + regionalCityPopulationTotals.idPop;
	regionPopulationTotals.imPop = currentCityPopulationTotals.imPop + regionalCityPopulationTotals.imPop;
	regionPopulationTotals.ihtPop = currentCityPopulationTotals.ihtPop + regionalCityPopulationTotals.ihtPop;
}

void RegionalCityDataProvider::UpdateCurrentCityPopulationTotals()
{
	cISC4AppPtr pSC4App;

	if (pSC4App)
	{
		cISC4RegionalCity* pRegionalCity = pSC4App->GetRegionalCity();

		if (pRegionalCity)
		{
			currentCityPopulationTotals.res1Pop = pRegionalCity->GetPopulation(0x1010);
			currentCityPopulationTotals.res2Pop = pRegionalCity->GetPopulation(0x1020);
			currentCityPopulationTotals.res3Pop = pRegionalCity->GetPopulation(0x1030);
			currentCityPopulationTotals.cs1Pop = pRegionalCity->GetPopulation(0x3110);
			currentCityPopulationTotals.cs2Pop = pRegionalCity->GetPopulation(0x3120);
			currentCityPopulationTotals.cs3Pop = pRegionalCity->GetPopulation(0x3130);
			currentCityPopulationTotals.co2Pop = pRegionalCity->GetPopulation(0x3320);
			currentCityPopulationTotals.co3Pop = pRegionalCity->GetPopulation(0x3330);
			currentCityPopulationTotals.irPop = pRegionalCity->GetPopulation(0x4100);
			currentCityPopulationTotals.idPop = pRegionalCity->GetPopulation(0x4200);
			currentCityPopulationTotals.imPop = pRegionalCity->GetPopulation(0x4300);
			currentCityPopulationTotals.ihtPop = pRegionalCity->GetPopulation(0x4400);
		}
	}
}

void RegionalCityDataProvider::UpdateRegionalCityPopulationTotals()
{
	cISC4AppPtr pSC4App;

	if (pSC4App)
	{
		cISC4Region* pRegion = pSC4App->GetRegion();
		cISC4RegionalCity* pRegionalCity = pSC4App->GetRegionalCity();

		if (pRegion && pRegionalCity)
		{
			int32_t currentCityX = 0;
			int32_t currentCityZ = 0;

			pRegionalCity->GetPosition(currentCityX, currentCityZ);

			eastl::vector<cISC4Region::cLocation> cityLocations;

			pRegion->GetCityLocations(cityLocations);

			size_t count = cityLocations.size();

			if (count > 0)
			{
				for (size_t i = 0; i < count; i++)
				{
					const cISC4Region::cLocation& location = cityLocations[i];

					if (location.x == currentCityX && location.z == currentCityZ)
					{
						// The current city values are handled separately.
						continue;
					}

					// The city pointer should not be released.

					cISC4RegionalCity** ppRegionalCity = pRegion->GetCity(location.x, location.z);

					if (ppRegionalCity && *ppRegionalCity)
					{
						cISC4RegionalCity* pRegionalCity = *ppRegionalCity;

						if (pRegionalCity->GetEstablished())
						{
							regionalCityPopulationTotals.res1Pop += pRegionalCity->GetPopulation(0x1010);
							regionalCityPopulationTotals.res2Pop += pRegionalCity->GetPopulation(0x1020);
							regionalCityPopulationTotals.res3Pop += pRegionalCity->GetPopulation(0x1030);
							regionalCityPopulationTotals.cs1Pop += pRegionalCity->GetPopulation(0x3110);
							regionalCityPopulationTotals.cs2Pop += pRegionalCity->GetPopulation(0x3120);
							regionalCityPopulationTotals.cs3Pop += pRegionalCity->GetPopulation(0x3130);
							regionalCityPopulationTotals.co2Pop += pRegionalCity->GetPopulation(0x3320);
							regionalCityPopulationTotals.co3Pop += pRegionalCity->GetPopulation(0x3330);
							regionalCityPopulationTotals.irPop += pRegionalCity->GetPopulation(0x4100);
							regionalCityPopulationTotals.idPop += pRegionalCity->GetPopulation(0x4200);
							regionalCityPopulationTotals.imPop += pRegionalCity->GetPopulation(0x4300);
							regionalCityPopulationTotals.ihtPop += pRegionalCity->GetPopulation(0x4400);
						}
					}
				}
			}
		}
	}
}
