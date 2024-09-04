// Fill out your copyright notice in the Description page of Project Settings.


#include "HeightGenerator.h"
#include "MCTerrainDemo/Tool/NoiseTool.h"

void HeightGenerator::GenerateDensity(Chunk& Chunk)
{
	// 创建三维变量
	FVector3d Pos = FVector3d(Chunk.ChunkPosition.X, Chunk.ChunkPosition.Y, 0);
	// 噪声晶格大小
	int32 CrystalSize[3] = {4,16,64};
	// 噪声权重
	float Weight[3] = {0.12f,0.222,0.66f};
	// 噪声振幅
	float MaxHeight[3] = {100.f, 100.f, 100.f};
	// 叠加三次噪声作为区块密度
	for (int T = 0; T < 3; T++)
	{
		// 预处理柏林噪声
		
	}
	
}
