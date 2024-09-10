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


class MCTERRAINDEMO_API NoiseTool
{
private:
	inline static int32 Perm[256] = {
	  251, 72, 117, 203, 66, 160, 157, 188, 94, 56, 178, 237, 33, 221, 77,
	  49, 18, 153, 107, 4, 81, 166, 248, 95, 35, 59, 93, 113, 65, 126, 190,
	  202, 54, 79, 39, 149, 16, 211, 37, 46, 6, 61, 51, 42, 84, 163, 139,
	  9, 21, 47, 69, 179, 75, 43, 3, 136, 111, 219, 131, 206, 223, 86, 98,
	  173, 23, 5, 74, 83, 57, 123, 85, 31, 230, 2, 183, 63, 82, 13, 62,
	  218, 229, 58, 242, 169, 234, 127, 70, 215, 96, 89, 20, 71, 90, 210,
	  241, 22, 29, 171, 68, 55, 36, 78, 17, 235, 101, 52, 73, 45, 102,
	  104, 200, 8, 25, 34, 40, 60, 192, 209, 189, 91, 48, 176, 26, 222,
	  214, 116, 245, 7, 97, 41, 30, 53, 88, 227, 87, 12, 140, 207, 112,
	  232, 24, 50, 208, 99, 220, 119, 38, 152, 243, 194, 150, 19, 92,
	  175, 155, 180, 177, 76, 228, 14, 225, 44, 198, 64, 80, 201, 146,
	  144, 1, 154, 133, 216, 142, 110, 132, 141, 252, 239, 67, 170, 212,
	  124, 138, 236, 28, 143, 109, 137, 165, 174, 224, 55, 158, 106, 195,
	  244, 16, 197, 159, 186, 115, 121, 148, 118, 105, 162, 125, 32,
	  193, 100, 15, 255, 134, 90, 27, 196, 103, 145, 10, 108, 184, 156,
	  250, 161, 11, 240, 122, 187, 168, 182, 0, 185, 167, 204, 129,
	  164, 191, 249, 231, 120, 172, 135, 213, 18, 72, 117, 203, 66, 160,
	  157, 188, 94, 56, 178, 237, 33};
	void RandomPermWithSeed(int32 Seed);
	void RandomPerm();
	static float Grad(const FVector2d& Position2d, const FVector2d& Vertex);
	static float Grad3d(float X, float Y, float Z, int Hash);
	static float Grad3d(const FVector3d& Position3d, const FVector3d& Vertex);
	static int32 Hash11(const int32 Value);
	static int32 Hash21(const FVector2d& Vector);
	static int32 Hash31(const FVector3d& Vector);
	static float Fade(const float T);
public:
	static void PreHandlePerlinNoise2d(float X, float Y, const int32 CrystalSize);
	static void PreHandlePerlinNoise2d(const FVector2d& Position2d, const int32 CrystalSize);
	static float HandlePerlinNoise3d(float X, float Y, float Z, const int32 CrystalSize);
	static void PreHandlePerlinNoise3d(float X, float Y, float Z, const int32 CrystalSize);
	static void PreHandlePerlinNoise3d(const FVector3d& Position3d, const int32 CrystalSize);
	static float PerlinNoise2d(const FVector2d& Pos);
	static float PerlinNoise3d(float X, float Y, float Z);
	static float PerlinNoise3d(const FVector3d& Pos);
	// 计算倍频噪声值
	static float Fbm(const FVector2d&, int Octave);
	static float Fbm(float X, float Y, int Octave);
	static float Fbm(const FVector3d&, int Octave);
	static float Fbm(float X, float Y, float Z, int Octave);
	// 将三维坐标压缩为一维uint64整数
	static uint64 Index(const int32 X, const int32 Y, const int32 Z=0);
	// 将一维uint64整数解压为三维坐标
	static FVector UnIndex(uint64 Index);
	NoiseTool() = delete;
	~NoiseTool() = delete;
};
