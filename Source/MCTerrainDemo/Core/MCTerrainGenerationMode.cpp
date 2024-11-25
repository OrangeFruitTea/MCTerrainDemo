// Fill out your copyright notice in the Description page of Project Settings.


#include "MCTerrainGenerationMode.h"

#include "MCTerrainDemo/Core/LocationCastLibrary.h"
#include "MCTerrainDemo/Tool/IndexTool.h"
#include "MCTerrainDemo/Generator/ChunkBuilder.h"

void AMCTerrainGenerationMode::UpdateChunks()
{
	PlayerWorldLocation = ULocationCastLibrary::GetPlayerWorldLocation(this);
	// 当前玩家所处的区块Index
	const FIntPoint PlayerLocatedChunkIndex = ULocationCastLibrary::GetPlayerLocatedChunkIndex(this);
	for (int i = -DrawDistance; i <= DrawDistance; i++)
	for (int j = -DrawDistance; j <= DrawDistance; j++)
	{
		const FIntPoint ChunkIndex(PlayerLocatedChunkIndex.X + i, PlayerLocatedChunkIndex.Y + j);
		const FVector PosInput = ULocationCastLibrary::ChunkIndexToChunkInfoLocation(ChunkIndex.X, ChunkIndex.Y);
		// (new FAutoDeleteAsyncTask<FGenerateChunkAsyncTask>(ChunkIndex, PosInput, this))->StartBackgroundTask();
		// 根据ChunkIndex判断是否已经生成Chunk
		if (Chunks.Contains(IndexTool::Index(ChunkIndex.X, ChunkIndex.Y))) continue;
		
		Chunk* NewChunk = LoadChunk(ChunkIndex.X,ChunkIndex.Y,PosInput);
		NewChunk->SetChunkCalculateLevel(ECalculateLevel::Active);
		Chunks2Display.Emplace(NewChunk);
	}
	// for (auto SpawnedChunk : Chunks2Display)
	// {
	// 	if (!(PlayerLocatedChunkIndex.X - 1 <= SpawnedChunk->ChunkIndex.X && SpawnedChunk->ChunkIndex.X <= PlayerLocatedChunkIndex.X + 1 &&
	// 		PlayerLocatedChunkIndex.Y - 1 <= SpawnedChunk->ChunkIndex.Y && SpawnedChunk->ChunkIndex.Y <= PlayerLocatedChunkIndex.Y + 1))
	// 	{
	// 		SpawnedChunk->SetChunkCalculateLevel(ECalculateLevel::Deleted);
	// 	} 
	// }
	// for (auto It =  Chunks2Display.CreateConstIterator(); It; ++It)
	// {
	// 	Chunk* PendingKillChunk = *It;
	// 	if (PendingKillChunk->GetChunkCalculateLevel() == ECalculateLevel::Deleted)
	// 	{
	// 		ChunkBuilder::DeleteChunkMesh(this, *PendingKillChunk);
	// 		Chunks2Display.Remove(PendingKillChunk);
	// 		delete PendingKillChunk;
	// 	}
	// }
}

Chunk* AMCTerrainGenerationMode::LoadChunk(int x, int y, const FVector& PosInput)
{
	uint64 Index = IndexTool::Index(x, y);
	// chunk信息载入至Info中
	Chunks.Emplace(Index, Chunk(x, y, PosInput));
	Chunk& NewChunk = Chunks[Index];
	// 数据生成
	ChunkBuilder::FillBasicTerrain(NewChunk);
	ChunkBuilder::GenerateChunkMesh(this, NewChunk);
	ChunkBuilder::ClearIntermediateData();
	return &NewChunk;
}

void AMCTerrainGenerationMode::TestGenerateWorld()
{
	UpdateChunks();
}

TArray<FIntPoint> AMCTerrainGenerationMode::GetAllChunks()
{
	TArray<FIntPoint> Vec;
	for (auto Chunk : Chunks)
	{
		Vec.Emplace(Chunk.Value.ChunkIndex);
	}
	return Vec;
}
//
// FGenerateChunkAsyncTask::FGenerateChunkAsyncTask(const FIntPoint& ChunkIndex, const FVector& PosInput,
// 	AMCTerrainGenerationMode* TerrainGenerationMode)
// 	: ChunkIndex(ChunkIndex),
// 	  PosInput(PosInput),
// 	  TerrainGenerationMode(TerrainGenerationMode)
// {
// }
//
// void FGenerateChunkAsyncTask::DoWork()
// {
// 	uint64 Index = IndexTool::Index(ChunkIndex.X, ChunkIndex.Y);
// 	// 同步锁
// 	FScopeLock ScopeLock(&TerrainGenerationMode->CriticalSection);
// 	if (!TerrainGenerationMode->Chunks.Contains(Index))
// 	{
// 		TerrainGenerationMode->Chunks.Emplace(Index, Chunk(ChunkIndex.X, ChunkIndex.Y, PosInput));
// 		Chunk& NewChunk = TerrainGenerationMode->Chunks[Index];
// 		ChunkBuilder::FillBasicTerrain(NewChunk);
// 	}
// }
