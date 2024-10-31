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
class MCTERRAINDEMO_API HumidityGenerator
{
private:
	static inline FastNoiseLite* NoiseLite = new FastNoiseLite(1472);
	static inline TMap<uint64, float> HumidityMap;
public:
	static void SetSeed(const int32 Seed);
	static float GetWorldBlockHumidity(int WorldX, int WorldY, int WorldZ);
	static float GetRelativeBlockHumidity(const Chunk& Chunk, int X, int Y, int Z);
	static void GenerateHumidity(const Chunk& Chunk);
	static float GetHumidityByIndex(int X, int Y, int Z);
	static void ClearMap();
	HumidityGenerator()=delete;
	~HumidityGenerator()=delete;
};
