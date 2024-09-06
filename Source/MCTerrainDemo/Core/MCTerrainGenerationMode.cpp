// Fill out your copyright notice in the Description page of Project Settings.


#include "MCTerrainGenerationMode.h"

#include "MCTerrainDemo/Block.h"
#include "MCTerrainDemo/Tool/NoiseTool.h"

void AMCTerrainGenerationMode::UpdateChunks()
{
	for (int i = 0; i < WorldRadius; i++)
	for (int j = 0; j < WorldRadius; j++)
	{
		FVector2d ChunkPosition = FVector2d(WorldCenterLocation.X+i, WorldCenterLocation.Y+j);
		uint64 Index = NoiseTool::Index(ChunkPosition.X, ChunkPosition.Y);
		if (!Chunks.Contains(Index))
		{
			Chunks.Emplace(Index, Chunk(ChunkPosition));
			Chunk& NewChunk = Chunks[Index];
			LoadChunk(NewChunk);
			GenerateChunk(NewChunk);
		}
	}
}

void AMCTerrainGenerationMode::LoadChunk(Chunk& Chunk)
{
	HeightGenerator::GenerateDensity(Chunk);
}

void AMCTerrainGenerationMode::GenerateChunk(const Chunk& Chunk) const
{
	for (int i = 0; i < MaxBlockWidth; i++)
	for(int j = 0; j < MaxBlockWidth; j++)
	for (int k = 0; k < MaxBlockHeight; k++)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Block Density: %f"), Chunk.BlockDensity[i][j][k]));
		if (Chunk.BlockDensity[i][j][k] > 0.7f)
		{
			// 生成方块
			FVector3d Pos = FVector3d(Chunk.ChunkPosition.X*16+i, Chunk.ChunkPosition.Y*16+j, k);
			TestCreateBlock(Pos);
		}		
	}
}

void AMCTerrainGenerationMode::TestCreateBlock(const FVector3d& Pos) const
{
	GetWorld()->SpawnActor<ABlock>(Pos*100, FRotator::ZeroRotator);
}

void AMCTerrainGenerationMode::TestGenerateWorld()
{
	UpdateChunks();
}
