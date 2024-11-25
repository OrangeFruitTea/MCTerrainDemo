// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MCTerrainDemo/Core/Chunk.h"
#include "MCTerrainDemo/Tool/IndexTool.h"
#include "MCTerrainDemo/Tool/FastNoiseLite.h"

class FastNoiseLite;

/**
 * 
 */

class MCTERRAINDEMO_API ContinentalnessGenerator
{
private:
	static inline UCurveFloat* ContinentalCurve = nullptr;
	static inline FastNoiseLite* NoiseLite = new FastNoiseLite(9531);
	static inline TMap<uint64, float> ContinentalMap;
	static bool LoadCurve();
public:
	static void SetSeed(const int32 Seed);
	static float GetWorldBlockContinental(int WorldX, int WorldY, int WorldZ);
	static float GetWorldBlockContinental(FIntVector WorldLocation);
	static float GetRelativeBlockContinental(const Chunk& Chunk, int X, int Y, int Z);
	static void GenerateContinental(const Chunk& Chunk);
	static float GetContinentalByIndex(int X, int Y, int Z=DefaultTestValue);
	static void ClearMap();
	static float GetCrvValue(float Key);
	ContinentalnessGenerator()=delete;
	~ContinentalnessGenerator()=delete;
};
