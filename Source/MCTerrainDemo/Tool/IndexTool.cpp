// Fill out your copyright notice in the Description page of Project Settings.


#include "MCTerrainDemo/Tool/IndexTool.h"

uint64 IndexTool::Index(const int32 X,const int32 Y, const int32 Z)
{
	constexpr int32 Offset = 16384;
	return (static_cast<uint64>(X+Offset)<<40 | static_cast<uint64>(Y+Offset)<<20 | static_cast<uint64>(Z+Offset));
}

uint64 IndexTool::Index(const FIntVector& Vec)
{
	return Index(Vec.X, Vec.Y, Vec.Z);
}

uint64 IndexTool::Index(const FVector2d& Vec)
{
	return Index(Vec.X, Vec.Y);
}

FIntVector IndexTool::UnIndex(uint64 Index)
{
	const int32 Offset = 16384;
	return FIntVector(
		int32(Index>>40)-Offset,
		int32((Index>>20)&0xFFFFF)-Offset,
		int32(Index&0xFFFFF)-Offset);
	
}

int32 IndexTool::Hash11(const int32 Value)
{
	constexpr uint32 Multiplier = 0x9E3779B9;
	uint32 UnValue = static_cast<uint32>(Value);
	const bool IsNegative = Value < 0;
	// 使用位运算混合结果
	uint32 hash = UnValue * Multiplier;
	hash ^= hash >> 16;
	hash *= 0x6C07A965;
	hash ^= hash >> 3;
	// 如果原始值是负数，通过XOR操作添加一个模式来区分哈希值
	if (IsNegative)
		hash ^= 0x80000000; // XOR操作一个模式，确保负数和正数的哈希值不同
	return hash;
}

int32 IndexTool::Hash21(const FVector2d& Vector)
{
	return (0x9E3779B9* static_cast<int32>(Vector.X) + static_cast<int32>(Vector.Y)) % 1024;
}

int32 IndexTool::Hash21WithSeed(int Seed, int X, int Y)
{
	int32 Hash = Seed ^ X ^ Y;
	Hash *= 0x27d4eb2d;
	return Hash;
}

int32 IndexTool::Hash31(const FVector3d& Vector)
{
	return (0x9E3779B9* static_cast<int32>(Vector.X) + 0x6C078965* static_cast<int32>(Vector.Y) + static_cast<int32>(Vector.Z)) % 1024;
}

int32 IndexTool::Hash31WithSeed(int Seed, int X, int Y, int Z)
{
	int32 Hash = Seed ^ X ^ Y ^ Z;
	Hash *= 0x27d4eb2d;
	return Hash;
}