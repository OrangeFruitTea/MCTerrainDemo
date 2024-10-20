// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MCTerrainDemo/Core/Chunk.h"
#include "MCTerrainDemo/Tool/FastNoiseLite.h"

class FastNoiseLite;

/**
 * 
 */

class MCTERRAINDEMO_API ContinentalnessGenerator
{
private:
	static inline UCurveFloat* ContinentalCurve = nullptr;
	static inline FastNoiseLite* NoiseLite = new FastNoiseLite();
	static bool LoadCurve();
public:
	static void SetSeed(const int32 Seed);
	static void GenerateContinental(Chunk& Chunk);
	static void ClearContinental(Chunk& Chunk);
	static float GetCrvValue(float Key);
	ContinentalnessGenerator()=delete;
	~ContinentalnessGenerator()=delete;
};
