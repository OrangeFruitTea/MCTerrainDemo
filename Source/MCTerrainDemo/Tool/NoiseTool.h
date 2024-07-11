// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class MCTERRAINDEMO_API NoiseTool
{
private:
	static FVector2d CrystalVertex[4];
public:
	static void PreHandlePerlinNoise2d(FVector2d Position2d, int32 CrystalSize);
	NoiseTool() = delete;
	~NoiseTool() = delete;
};
