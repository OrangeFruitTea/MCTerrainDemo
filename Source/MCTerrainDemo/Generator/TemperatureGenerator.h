// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MCTerrainDemo/Tool/FastNoiseLite.h"
#include "MCTerrainDemo/Tool/IndexTool.h"
#include "MCTerrainDemo/Core/Chunk.h"

class FastNoiseLite;

/**
 * 
 */
class MCTERRAINDEMO_API TemperatureGenerator
{
private:
	static inline FastNoiseLite* NoiseLite = new FastNoiseLite(4567);
	static inline TMap<uint64, float> TemperatureMap;
public:
	static void SetSeed(const int32 Seed);
	static float GetWorldBlockTemperature(int WorldX, int WorldY, int WorldZ);
	static float GetRelativeBlockTemperature(const Chunk& Chunk, int X, int Y, int Z);
	static void GenerateTemperature(const Chunk& Chunk);
	static float GetTemperatureByIndex(int X, int Y, int Z=16);
	static void ClearMap();
	TemperatureGenerator()=delete;
	~TemperatureGenerator()=delete;
};
