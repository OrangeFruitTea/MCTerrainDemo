// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class MCTERRAINDEMO_API IndexTool
{
public:
	// 二三维坐标解压缩
	static uint64 Index(const int32 x, const int32 y, const int32 z=0);
	static uint64 Index(const FIntVector& Vec);
	static uint64 Index(const FVector2d& Vec);
	FIntVector UnIndex(const uint64 Index);
	// hash函数
	static int32 Hash11(const int32 Value);
	static int32 Hash21(const FVector2d& Vector);
	static int32 Hash21WithSeed(int Seed, int X, int Y);
	static int32 Hash31(const FVector3d& Vector);
	static int32 Hash31WithSeed(int Seed, int X, int Y, int Z);
	IndexTool()=delete;
	~IndexTool()=delete;
};
