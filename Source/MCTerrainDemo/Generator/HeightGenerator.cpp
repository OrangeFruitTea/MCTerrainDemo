// Fill out your copyright notice in the Description page of Project Settings.


#include "HeightGenerator.h"
#include "MCTerrainDemo/Tool/NoiseTool.h"

void HeightGenerator::GenerateDensity(Chunk& Chunk)
{
	// 噪声晶格大小
	int32 CrystalSize[3] = {4,16,64};
	// 噪声权重
	float Weight[3] = {0.12f, 0.22f, 0.66f};
	// 噪声振幅
	float MaxHeight[3] = {1.f, 1.f, 1.f};
		// 预处理柏林噪声
	for (int i = 0; i < MaxBlockWidth; i++)
	for (int j = 0; j < MaxBlockWidth; j++)
	for (int k = 0; k < MaxBlockHeight; k++)
	{
		float Density = 0;
		// 叠加三次噪声作为区块密度
		for (int T = 0; T < 3; T++)
		{
			NoiseTool::PreHandlePerlinNoise3d(Chunk.ChunkIndex.X, Chunk.ChunkIndex.Y, 1, CrystalSize[T]);
			// FVector PF = FVector(float(i)/MaxBlockWidth/16, float(j)/MaxBlockWidth/16, float(k)/MaxBlockHeight/16); 
			// Chunk.BlockDensity[i][j][k] = 10 * NoiseTool::Fbm(PF, 3);
			FVector3d PF = FVector3d(static_cast<float>(i)/MaxBlockWidth/CrystalSize[T], static_cast<float>(j)/MaxBlockWidth/CrystalSize[T], static_cast<float>(k)/MaxBlockHeight/CrystalSize[T]);
			Density += (NoiseTool::PerlinNoise3d(PF) * Weight[T]) * 10;
		}
		if (Density >= .8f)
		{
			Chunk.AddBlock2Data(EBlockType::Stone,i,j,k);
		}
	}
}
