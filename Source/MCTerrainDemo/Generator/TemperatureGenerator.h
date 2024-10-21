// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MCTerrainDemo/Tool/FastNoiseLite.h"
#include "MCTerrainDemo/Core/Chunk.h"

class FastNoiseLite;

/**
 * 
 */
class MCTERRAINDEMO_API TemperatureGenerator
{
private:
	static inline FastNoiseLite* NoiseLite = new FastNoiseLite();
public:
	static void SetSeed(const int32 Seed);
	static void GenerateTemperature(Chunk& Chunk);
	TemperatureGenerator()=delete;
	~TemperatureGenerator()=delete;
};
