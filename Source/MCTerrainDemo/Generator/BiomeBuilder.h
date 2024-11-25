// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ContinentalnessGenerator.h"
#include "HumidityGenerator.h"
#include "TemperatureGenerator.h"
#include "MCTerrainDemo/Tool/IndexTool.h"
#include "MCTerrainDemo/Core/EnumClass.h"

class MCTERRAINDEMO_API BiomeBuilder
{
private:
	// 储存生物群系选择的映射表
	static inline TMap<uint64, EBiomeMainWorld> BiomeSelector;
	static bool InitializeBiomeSelector();
	static uint64 inline GetIndex(int TemperatureRange, int HumidityRange, int ContinentalRange)
	{
		return IndexTool::Index(TemperatureRange, HumidityRange, ContinentalRange);
	}
	static int CheckIntervalsTemperature(const float Value);
	static int CheckIntervalsHumidity(const float Value);
	static int CheckIntervalsContinental(const float Value);
	static uint64 CheckIntervals(float Temperature, float Humidity, float Continental);
	static EBiomeMainWorld GetBiomeMainWorldHandle(uint64 ParamIndex);
	
public:
	static EBiomeMainWorld GetBiomeMainWorldByWorldLocation(FIntVector WorldLocation);
	static EBiomeMainWorld GetBiomeMainWorldByRelativeLocation(const Chunk& Chunk, int X, int Y, int Z);
	BiomeBuilder()=delete;
	~BiomeBuilder()=delete;
};
