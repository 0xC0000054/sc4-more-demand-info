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

#pragma once
#include <cstdint>

struct PopulationTotals
{
	int64_t res1Pop;
	int64_t res2Pop;
	int64_t res3Pop;
	int64_t cs1Pop;
	int64_t cs2Pop;
	int64_t cs3Pop;
	int64_t co2Pop;
	int64_t co3Pop;
	int64_t irPop;
	int64_t idPop;
	int64_t imPop;
	int64_t ihtPop;
};

class RegionalCityDataProvider
{
public:
	RegionalCityDataProvider();

	const PopulationTotals& GetRegionTotalPopulation() const;

	void PostCityInit();

	void PostSave();

private:
	void UpdateRegionPopulationTotals();

	void UpdateCurrentCityPopulationTotals();

	void UpdateRegionalCityPopulationTotals();

	PopulationTotals regionPopulationTotals;
	PopulationTotals currentCityPopulationTotals;
	PopulationTotals regionalCityPopulationTotals;
};
