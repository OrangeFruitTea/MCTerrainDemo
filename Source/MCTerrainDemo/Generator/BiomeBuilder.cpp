// Fill out your copyright notice in the Description page of Project Settings.


#include "BiomeBuilder.h"


bool BiomeBuilder::InitializeBiomeSelector()
{
	BiomeSelector[GetIndex(1,1,1)] = EBiomeMainWorld::SpecialTerrain;
	BiomeSelector[GetIndex(1,1,2)] = EBiomeMainWorld::Ocean;
	BiomeSelector[GetIndex(1,1,3)] = EBiomeMainWorld::Ocean;
	BiomeSelector[GetIndex(1,1,1)] = EBiomeMainWorld::None;
	BiomeSelector[GetIndex(1,1,1)] = EBiomeMainWorld::None;
	if (!BiomeSelector.IsEmpty()) return true;
	return false;
}

int BiomeBuilder::CheckIntervalsTemperature(const float Value)
{
	// _ASSERT(-1 <= Value && Value <= 1, "Temperature value must between -1 to 1");
	if (-1 <= Value && Value < -0.45) return 1;
	if (-0.45 <= Value && Value < -0.15) return 2;
	if (-0.15 <= Value && Value < 0.2) return 3;
	if (0.2 <= Value && Value < 0.55) return 4;
	// if ( 0.55 <= Value && Value <= 1) return 5;
	else return 5;
}

int BiomeBuilder::CheckIntervalsHumidity(const float Value)
{
	// _ASSERT(-1 <= Value && Value <= 1, "Humidity value must between -1 to 1");
	if (-1 <= Value && Value < -0.35) return 1;
	if (-0.35 <= Value && Value < -0.1) return 2;
	if (-0.1 <= Value && Value < 0.1) return 3;
	if (0.1 <= Value && Value < 0.3) return 4;
	// if ( 0.55 <= Value && Value <= 1) return 5;
	else return 5;
}

int BiomeBuilder::CheckIntervalsContinental(const float Value)
{
	if (Value < -1.05) return 1;						// special terrain
	if (-1.05 <= Value && Value < -0.455) return 2;		// deep ocean
	if (-0.455 <= Value && Value < -0.19) return 3;		// ocean
	if (0.19 <= Value && Value < -0.11) return 4;		// seashore
	if (-0.11 <= Value && Value < 0.03) return 5;		// semi-inland
	if (0.03 <= Value && Value < 0.3) return 6;			// inland
	else return 7;										// deep inland
}

uint64 BiomeBuilder::CheckIntervals(float Temperature, float Humidity, float Continental)
{
	const int TemperatureRange = CheckIntervalsTemperature(Temperature);
	const int HumidityRange = CheckIntervalsHumidity(Humidity);
	const int ContinentalRange = CheckIntervalsContinental(Continental);
	return GetIndex(TemperatureRange,HumidityRange,ContinentalRange);
}

EBiomeMainWorld BiomeBuilder::GetBiomeMainWorldHandle(uint64 ParamIndex)
{
	if (InitializeBiomeSelector() && BiomeSelector.Contains(ParamIndex))
	{
		return BiomeSelector[ParamIndex];
	} else {
		return EBiomeMainWorld::None;
	}
}

EBiomeMainWorld BiomeBuilder::GetBiomeMainWorldByWorldLocation(FIntVector WorldLocation)
{
	const float Temperature = TemperatureGenerator::GetWorldBlockTemperature(WorldLocation);
	const float Humidity = HumidityGenerator::GetWorldBlockHumidity(WorldLocation);
	const float Continental = ContinentalnessGenerator::GetWorldBlockContinental(WorldLocation);
	return GetBiomeMainWorldHandle(CheckIntervals(Temperature, Humidity, Continental));
}

EBiomeMainWorld BiomeBuilder::GetBiomeMainWorldByRelativeLocation(const Chunk& Chunk, int X, int Y, int Z)
{
	const float Temperature = TemperatureGenerator::GetRelativeBlockTemperature(Chunk, X, Y, Z);
	const float Humidity = HumidityGenerator::GetRelativeBlockHumidity(Chunk, X, Y, Z);
	const float Continental = ContinentalnessGenerator::GetRelativeBlockContinental(Chunk, X, Y, Z);
	return GetBiomeMainWorldHandle(CheckIntervals(Temperature, Humidity, Continental));
}
