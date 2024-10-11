// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MCTerrainDemo/Tool/FastNoiseLite.h"
#include "MCTerrainDemo/Core/Chunk.h"

class FastNoiseLite;

class MCTERRAINDEMO_API HeightGenerator
{
private:
	static inline int32 DefaultHeight = 16;
public:
	inline static FastNoiseLite* NoiseLite = new FastNoiseLite(246);
	static void GenerateHeight(Chunk& Chunk);
	static void GenerateDensity(Chunk& Chunk);
	// static float GenerateDensity(const FVector Position);
	HeightGenerator()=delete;
	~HeightGenerator()=delete;
};
