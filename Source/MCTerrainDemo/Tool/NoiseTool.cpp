// Fill out your copyright notice in the Description page of Project Settings.


#include "NoiseTool.h"



void NoiseTool::PreHandlePerlinNoise2d(FVector2d Position2d, int32 CrystalSize)
{
	// 根据给定点世界坐标与晶格大小确定给定点所在的晶格
	// Pi: 所在晶格的左下顶点的虚拟坐标
	const FVector2d PosInCrystal = FVector2d(Position2d.X / CrystalSize, Position2d.Y / CrystalSize);
	const FVector2d Pi = FVector2d(floor(PosInCrystal.X), floor(PosInCrystal.Y));
	FVector2d Vertex[4] = {Pi, FVector2d(Pi.X + 1, Pi.Y), FVector2d(Pi.X, Pi.Y + 1), FVector2d(Pi.X + 1, Pi.Y + 1)};

	// 根据晶格顶点坐标赋予随机梯度
	

	// 
}
