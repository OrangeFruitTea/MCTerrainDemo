// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

static FVector2d GGradientVector2d[8] = {FVector2d(0,1), FVector2d(0,-1), FVector2d(1,0), FVector2d(-1,0),
								FVector2d(1,1), FVector2d(1,-1), FVector2d(-1,1), FVector2d(-1,-1)};
static FVector2d CrystalVertex[4];
/**
 * 
 */
class MCTERRAINDEMO_API NoiseTool
{
private:
	static int64_t Hash11(const int64_t value);
	static int64_t Hash21(const FVector2d Vector);
public:
	static void PreHandlePerlinNoise2d(FVector2d Position2d, int32 CrystalSize);
	NoiseTool() = delete;
	~NoiseTool() = delete;
};
