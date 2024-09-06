// Fill out your copyright notice in the Description page of Project Settings.


#include "MCTerrainGenerationMode.h"

#include "MCTerrainDemo/Block.h"

void AMCTerrainGenerationMode::UpdateChunk(Chunk* Chunk)
{
}

void AMCTerrainGenerationMode::LoadChunk(Chunk* Chunk)
{
	HeightGenerator::GenerateDensity(Chunk);
}

void AMCTerrainGenerationMode::GenerateChunk(const Chunk* Chunk) const
{
	for (int i = 0; i < MaxBlockWidth; i++)
	for(int j = 0; j < MaxBlockWidth; j++)
	for (int k = 0; k < MaxBlockHeight; k++)
	{
		if (Chunk->BlockDensity[i][j][k] > 0.f)
		{
			// 生成方块
			FVector3d Pos = FVector3d(Chunk->ChunkPosition.X*16+i, Chunk->ChunkPosition.Y*16+j, k);
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
	LoadChunk(TestChunk);
	GenerateChunk(TestChunk);
}
