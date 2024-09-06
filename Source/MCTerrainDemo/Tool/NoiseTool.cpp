// Fill out your copyright notice in the Description page of Project Settings.


#include "NoiseTool.h"

FVector2d GlobalOffset = {};
FVector GlobalOffset3d = {};


float NoiseTool::Grad(const FVector2d& Position2d, const FVector2d& Vertex)
{
	return FVector2d::DotProduct(Position2d, Vertex);
}

float NoiseTool::Grad3d(const FVector3d& Position3d, const FVector3d& Vertex)
{
	return FVector3d::DotProduct(Position3d, Vertex);
}

int32 NoiseTool::Hash11(const int32 Value)
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

int32 NoiseTool::Hash21(const FVector2d& Vector)
{
	return (0x9E3779B9* static_cast<int32>(Vector.X) + static_cast<int32>(Vector.Y)) % 1024;
}

int32 NoiseTool::Hash31(const FVector3d& Vector)
{
	return (0x9E3779B9* static_cast<int32>(Vector.X) + 0x6C078965* static_cast<int32>(Vector.Y) + static_cast<int32>(Vector.Z)) % 1024;
}

void NoiseTool::PreHandlePerlinNoise2d(const FVector2d& Position2d, const int32 CrystalSize)
{
	// 根据给定点世界坐标与晶格大小确定给定点所在的晶格
	// Pi: 所在晶格的左下顶点的虚拟坐标
	const FVector2d PosInCrystal = FVector2d(Position2d.X / CrystalSize, Position2d.Y / CrystalSize);
	const FVector2d Pi = FVector2d(floor(PosInCrystal.X), floor(PosInCrystal.Y));
	const FVector2d Vertex[4] = {Pi, FVector2d(Pi.X+1, Pi.Y), FVector2d(Pi.X, Pi.Y+1), FVector2d(Pi.X+1, Pi.Y+1)};
	// 根据晶格顶点坐标赋予随机梯度
	int32 Index = 0;
	for(int i = 0; i < 4; i++)
	{
		Index = Hash21(Vertex[i]) % 8;
		CrystalVertex[i] = GGradientVector2d[Index];
	}
	// 更新区块的全局偏移
	GlobalOffset = (Position2d / CrystalSize);
}

void NoiseTool::PreHandlePerlinNoise3d(const FVector3d& Position3d, const int32 CrystalSize)
{
	const FVector3d PosInCrystal = FVector3d(Position3d.X / CrystalSize, Position3d.Y / CrystalSize, Position3d.Z / CrystalSize);
	const FVector3d Pi = FVector3d(floor(PosInCrystal.X), floor(PosInCrystal.Y), floor(PosInCrystal.Z));
	const FVector3d Vertex[8] = {Pi, FVector3d(Pi.X+1, Pi.Y, Pi.Z), FVector3d(Pi.X, Pi.Y+1, Pi.Z),FVector3d(Pi.X, Pi.Y, Pi.Z+1),
								FVector3d(Pi.X+1, Pi.Y+1, Pi.Z),FVector3d(Pi.X+1, Pi.Y, Pi.Z+1),FVector3d(Pi.X, Pi.Y+1, Pi.Z+1),FVector3d(Pi.X+1, Pi.Y+1, Pi.Z+1)};
	int32 Index = 0;
	for(int i = 0; i < 8; i++)
	{
		Index = Hash31(Vertex[i]) % 12;
		CrystalVertex3d[i] = GGradientVector3d[Index];
	}
	GlobalOffset3d = (Position3d-Pi*CrystalSize)/ CrystalSize;
}

float NoiseTool::PerlinNoise2d(const FVector2d& Pos)
{
	// 各晶格顶点梯度与距离作点积
	return FMath::Clamp<float>(
		FMath::Lerp(
			FMath::Lerp(Grad(Pos, CrystalVertex[0]), Grad(Pos, CrystalVertex[1]), Pos.X),
			FMath::Lerp(Grad(Pos, CrystalVertex[2]), Grad(Pos, CrystalVertex[3]), Pos.X),
			Pos.Y),
			-1, 1);
}

float NoiseTool::PerlinNoise3d(const FVector3d& Position)
{
	FVector3d Pos = Position + GlobalOffset3d;
	return FMath::Clamp<float>(
		FMath::Lerp(
			FMath::Lerp(
				FMath::Lerp(Grad3d(Pos, CrystalVertex3d[0]), Grad3d(Pos, CrystalVertex3d[1]), Pos.X),
				FMath::Lerp(Grad3d(Pos, CrystalVertex3d[2]), Grad3d(Pos, CrystalVertex3d[3]), Pos.X),
				Pos.Y),
			FMath::Lerp(
				FMath::Lerp(Grad3d(Pos, CrystalVertex3d[4]), Grad3d(Pos, CrystalVertex3d[5]), Pos.X),
				FMath::Lerp(Grad3d(Pos, CrystalVertex3d[6]), Grad3d(Pos, CrystalVertex3d[7]), Pos.X),
				Pos.Y),
			Pos.Z),
			-1, 1);
}

uint64 NoiseTool::Index(const int32 X,const int32 Y, const int32 Z)
{
	constexpr int32 Offset = 16384;
	return (static_cast<uint64>(X+Offset)<<40 | static_cast<uint64>(Y+Offset)<<20 | static_cast<uint64>(Z+Offset));
}

FVector NoiseTool::UnIndex(uint64 Index)
{
	const int32 Offset = 16384;
	return FVector(
		int32(Index>>40)-Offset,
		int32((Index>>20)&0xFFFFF)-Offset,
		int32(Index&0xFFFFF)-Offset);
	
}
