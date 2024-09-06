// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

static FVector2d GGradientVector2d[8] = {FVector2d(0,1), FVector2d(0,-1), FVector2d(1,0), FVector2d(-1,0),
										 FVector2d(1,1), FVector2d(1,-1), FVector2d(-1,1), FVector2d(-1,-1)};
static FVector2d CrystalVertex[4];
static FVector3d CrystalVertex3d[8];
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
	static float Grad3d(const FVector3d& Position3d, const FVector3d& Vertex);
	static int32 Hash11(const int32 Value);
	static int32 Hash21(const FVector2d& Vector);
	static int32 Hash31(const FVector3d& Vector);
public:
	static void PreHandlePerlinNoise2d(const FVector2d& Position2d, const int32 CrystalSize);
	static void PreHandlePerlinNoise3d(const FVector3d& Position3d, const int32 CrystalSize);
	static float PerlinNoise2d(const FVector2d& Pos);
	static float PerlinNoise3d(const FVector3d& Pos);
	// 将三维坐标压缩为一维uint64整数
	static uint64 Index(const int32 X, const int32 Y, const int32 Z);
	// 将一维uint64整数解压为三维坐标
	static FVector UnIndex(uint64 Index);
	NoiseTool() = delete;
	~NoiseTool() = delete;
};
