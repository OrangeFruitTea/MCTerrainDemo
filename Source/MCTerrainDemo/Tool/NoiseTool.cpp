// Fill out your copyright notice in the Description page of Project Settings.


#include "NoiseTool.h"


float NoiseTool::Grad(const FVector2d& Position2d, const FVector2d& Vertex)
{
	return FVector2d::DotProduct(Position2d, Vertex);
}

int64_t NoiseTool::Hash11(const int64_t Value)
{
	constexpr uint64_t Multiplier = 0x9E3779B97F4A7C15;
	uint64_t UnValue = static_cast<uint64_t>(Value);
	const bool IsNegative = Value < 0;
	// 使用位运算混合结果
	uint64_t hash = UnValue * Multiplier;
	hash ^= hash >> 32;
	hash *= 0x6C078965B58C4E61;
	hash ^= hash >> 27;
	// 如果原始值是负数，通过XOR操作添加一个模式来区分哈希值
	if (IsNegative)
		hash ^= 0x8000000000000000; // XOR操作一个模式，确保负数和正数的哈希值不同
	return hash;
}

int64_t NoiseTool::Hash21(const FVector2d& Vector)
{
	return (0x9E3779B97F4A7C15 * static_cast<int64_t>(Vector.X) + static_cast<int64_t>(Vector.Y)) % 1024;
}

int64_t NoiseTool::Hash31(const FVector3d& Vector)
{
	return (0x9E3779B97F4A7C15 * static_cast<int64_t>(Vector.X) + 0x6C078965B58C4E61 * static_cast<int64_t>(Vector.Y) + static_cast<int64_t>(Vector.Z)) % 1024;
}

void NoiseTool::PreHandlePerlinNoise2d(const FVector2d& Position2d, const int32 CrystalSize)
{
	// 根据给定点世界坐标与晶格大小确定给定点所在的晶格
	// Pi: 所在晶格的左下顶点的虚拟坐标
	const FVector2d PosInCrystal = FVector2d(Position2d.X / CrystalSize, Position2d.Y / CrystalSize);
	const FVector2d Pi = FVector2d(floor(PosInCrystal.X), floor(PosInCrystal.Y));
	const FVector2d Vertex[4] = {Pi, FVector2d(Pi.X+1, Pi.Y), FVector2d(Pi.X, Pi.Y+1), FVector2d(Pi.X+1, Pi.Y+1)};

	// 根据晶格顶点坐标赋予随机梯度
	int64_t Index = 0;
	for(int i = 0; i < 4; i++)
	{
		Index = Hash21(Vertex[i]) % 8;
		CrystalVertex[i] = GGradientVector2d[Index];
	}
}

void NoiseTool::PreHandlePerlinNoise3d(const FVector3d& Position3d, const int32 CrystalSize)
{
	const FVector3d PosInCrystal = FVector3d(Position3d.X / CrystalSize, Position3d.Y / CrystalSize, Position3d.Z / CrystalSize);
	const FVector3d Pi = FVector3d(floor(PosInCrystal.X), floor(PosInCrystal.Y), floor(PosInCrystal.Z));
	const FVector3d Vertex[8] = {Pi, FVector3d(Pi.X+1, Pi.Y, Pi.Z), FVector3d(Pi.X, Pi.Y+1, Pi.Z),FVector3d(Pi.X, Pi.Y, Pi.Z+1),
								FVector3d(Pi.X+1, Pi.Y+1, Pi.Z),FVector3d(Pi.X+1, Pi.Y, Pi.Z+1),FVector3d(Pi.X, Pi.Y+1, Pi.Z+1),FVector3d(Pi.X+1, Pi.Y+1, Pi.Z+1)};

}

float NoiseTool::PerlinNoise2d(const FVector2d Pos)
{
	// 各晶格顶点梯度与距离作点积
	return FMath::Clamp<float>(
		FMath::Lerp(
			FMath::Lerp(Grad(Pos, CrystalVertex[0]), Grad(Pos, CrystalVertex[1]), Pos.X),
			FMath::Lerp(Grad(Pos, CrystalVertex[2]), Grad(Pos, CrystalVertex[3]), Pos.X),
			Pos.Y),
			-1, 1);
}
