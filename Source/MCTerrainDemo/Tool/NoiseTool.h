// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

static FVector2d GGradientVector2d[8] = {FVector2d(0,1), FVector2d(0,-1), FVector2d(1,0), FVector2d(-1,0),
										 FVector2d(1,1), FVector2d(1,-1), FVector2d(-1,1), FVector2d(-1,-1)};
static FVector2d CrystalVertex[4];
static FVector3d GGradientVector3d[12] = {FVector3d(1,1,0), FVector3d(-1,1,0),FVector3d(1,-1,0),FVector3d(-1,-1,0),
										 FVector3d(1,0,1),FVector3d(-1,0,1),FVector3d(1,0,-1),FVector3d(-1,0,-1),
										 FVector3d(0,1,1),FVector3d(0,-1,1),FVector3d(0,1,-1),FVector3d(0,-1,-1)};
/**
 * 
 */
class MCTERRAINDEMO_API NoiseTool
{
private:
	static float Grad(const FVector2d& Position2d, const FVector2d& Vertex);
	static int64_t Hash11(const int64_t Value);
	static int64_t Hash21(const FVector2d& Vector);
	static int64_t Hash31(const FVector3d& Vector);
public:
	static void PreHandlePerlinNoise2d(const FVector2d& Position2d, const int32 CrystalSize);
	static void PreHandlePerlinNoise3d(const FVector3d& Position3d, const int32 CrystalSize);
	static float PerlinNoise2d(const FVector2d Pos);
	NoiseTool() = delete;
	~NoiseTool() = delete;
};
