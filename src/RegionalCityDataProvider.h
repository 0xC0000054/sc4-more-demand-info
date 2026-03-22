/*
 * This file is part of sc4-more-demand-info, a DLL Plugin for SimCity 4
 * that provides more game variables with RCI demand information.
 *
 * Copyright (C) 2024, 2026 Nicholas Hayes
 *
 * sc4-more-building-styles is free software: you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation, either version 3 of
 * the License, or (at your option) any later version.
 *
 * sc4-more-building-styles is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with sc4-more-building-styles.
 * If not, see <http://www.gnu.org/licenses/>.
 */

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
