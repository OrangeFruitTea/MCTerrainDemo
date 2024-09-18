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
	float MaxHeight[3] = {1.f, .5f, .25f};
		// 预处理柏林噪声
	for (int i = 0; i < MaxBlockWidth; i++)
	for (int j = 0; j < MaxBlockWidth; j++)
	for (int k = 0; k < MaxBlockHeight; k++)
	{
		float Density = 0;
		int Seed = 1357;
		// int Amp = 1.f;
		// 叠加三次噪声作为区块密度
		// for (int T = 0; T < 3; T++)
		// {
		// 	NoiseTool::PreHandlePerlinNoise3d(Chunk.ChunkIndex.X,Chunk.ChunkIndex.Y,1, CrystalSize[T]);
		// 	// FVector PF = FVector(float(i)/MaxBlockWidth/16, float(j)/MaxBlockWidth/16, float(k)/MaxBlockHeight/16); 
		// 	// Chunk.BlockDensity[i][j][k] = 10 * NoiseTool::Fbm(PF, 3);
		// 	FVector3d PF = FVector3d(static_cast<float>(i)/MaxBlockWidth/CrystalSize[T], static_cast<float>(j)/MaxBlockWidth/CrystalSize[T], static_cast<float>(k)/MaxBlockHeight/CrystalSize[T]);
		// 	Density += (NoiseTool::PerlinNoise3d(PF) * Weight[T]) * 10;
		// 	// Density += MaxHeight[T] * Weight[T] * NoiseTool::SinglePerlin(Seed++, Amp*(Chunk.ChunkIndex.X+i*0.9746219f),Amp*(Chunk.ChunkIndex.Y+j*0.9746219f),Amp*(k*0.9746219f));
		// 	// Amp *= 2;
		// }
		for (int T = 0; T < 3; T++)
		{
			// Density += Weight[T] * NoiseLite->SinglePerlin(Seed++, (Chunk.ChunkWorldPosition.X/100+i), (Chunk.ChunkWorldPosition.Y/100+j), (1.75f/2.f+k));
		}
		// Density = FMath::Clamp(Density, -1, 1);
		// GEngine->AddOnScreenDebugMessage(-1, 115.f, FColor::Red, FString::Printf(TEXT("Block Density: (%f)"), Density));
		if (Density >= .0f)
		{
			Chunk.AddBlock2Data(EBlockType::Stone,i,j,k);
		}
	}
}

void HeightGenerator::GenerateHeight(Chunk& Chunk)
{
	for (int x = 0; x < MaxBlockWidth; x++)
	for (int y = 0; y < MaxBlockWidth; y++)
	{
		const auto NoiseValue = NoiseLite->GetNoise(x+Chunk.ChunkWorldPosition.X, y+Chunk.ChunkWorldPosition.Y);
 		// GEngine->AddOnScreenDebugMessage(-1, 115.f, FColor::Red, FString::Printf(TEXT("Block Height: (%f)"), NoiseValue*10));
		// if (NoiseValue >= -0.6f)
		{
			// Chunk.AddBlock2Data(EBlockType::Stone, x,y,NoiseValue*10);
			for (int i = 0; i < NoiseValue*MaxBlockHeight+5; i++)
			{
				Chunk.AddBlock2Data(EBlockType::Stone, x,y,i);
			}
		}
		
	}
}

// void HeightGenerator::GenerateDensity(Chunk& Chunk)
// {
// 	for (int x = 0; x < MaxBlockWidth; x++)
// 	for (int y = 0; y < MaxBlockWidth; y++)
// 	for (int z = 0; z < MaxBlockWidth; z++)
// 	{
// 		const auto NoiseValue = NoiseLite->GetNoise(x+Chunk.ChunkWorldPosition.X, y+Chunk.ChunkWorldPosition.Y, z+Chunk.ChunkWorldPosition.Z);
// 		if (NoiseValue >= 0)
// 		{
// 			Chunk.AddBlock2Data(EBlockType::Stone, x,y,z);
// 		} else
// 		{
// 			Chunk.AddBlock2Data(EBlockType::Air, x,y,z);
// 		}
// 	}
// }
