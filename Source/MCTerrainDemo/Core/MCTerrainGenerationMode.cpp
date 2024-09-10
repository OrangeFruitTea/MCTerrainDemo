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
			DisplayChunk(NewChunk);
		}
	}
}

void AMCTerrainGenerationMode::LoadChunk(Chunk& Chunk)
{
	HeightGenerator::GenerateDensity(Chunk);
}

void AMCTerrainGenerationMode::DisplayChunk(const Chunk& Chunk) 
{
	// 将地形方块添加至GlobalInfo中
	for (int i = 0; i < MaxBlockWidth; i++)
	for(int j = 0; j < MaxBlockWidth; j++)
	for (int k = 0; k < MaxBlockHeight; k++)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Block Density: %f"), Chunk.BlockDensity[i][j][k]));
		if (Chunk.BlockDensity[i][j][k] > 0.7f)
		{
			// 将方块信息导入GlobalInfo中
			FVector3d Pos = FVector3d(Chunk.ChunkPosition.X*16+i, Chunk.ChunkPosition.Y*16+j, k);
			Info.AddBlock(Pos, 1);
		}		
	}
	// 根据待显示方块列表生成方块
	auto& Blocks2Display = Info.GetBlocks2Display();
	// GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("DisplayBlockSize: %d"), Blocks2Display.Num()));
	for (const auto& Block : Blocks2Display)
	{
		FVector BlockPosition = NoiseTool::UnIndex(Block.Key);
		const int32 dx[6] = {1,-1,0,0,0,0};
		const int32 dy[6] = {0,0,1,-1,0,0};
		const int32 dz[6] = {0,0,0,0,1,-1};
		for (int d = 0; d < 6; d++)
		{
			FVector Pos = FVector(BlockPosition.X+dx[d],BlockPosition.Y+dy[d],BlockPosition.Z+dz[d]);
			auto Neighboor  = Info.FindBlock(Pos);
			bool NeedCreate = false;
			if (!Neighboor)
			{
				NeedCreate = true;
			}
			if (NeedCreate)
			{
				TestCreateBlock(BlockPosition, 1);
				break;
			}
		}
		
	}	
}

void AMCTerrainGenerationMode::TestCreateBlock(const FVector3d& Pos, int32 BlockID) const
{
		GetWorld()->SpawnActor<ABlock>(Pos*100, FRotator::ZeroRotator);
}

void AMCTerrainGenerationMode::TestGenerateWorld()
{
	UpdateChunks();
}
