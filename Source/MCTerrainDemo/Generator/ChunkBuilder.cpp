// Fill out your copyright notice in the Description page of Project Settings.


#include "ChunkBuilder.h"

#include "MCTerrainDemo/Core/MCTerrainGenerationMode.h"

void ChunkBuilder::SpawnStructStarts(Chunk& ChunkInfo)
{
}

void ChunkBuilder::CalculateStructRef(Chunk& ChunkInfo)
{
}

void ChunkBuilder::SpawnBiomes(Chunk& ChunkInfo)
{
	// 温度

	// 湿度

	// 大陆性
	ContinentalnessGenerator::GenerateContinental(ChunkInfo);
	// 侵蚀度

	// 奇异性

	// 确定生物群系

}

void ChunkBuilder::FillBasicTerrain(Chunk& ChunkInfo)
{
	ContinentalnessGenerator::GenerateContinental(ChunkInfo);
	TemperatureGenerator::GenerateTemperature(ChunkInfo);
	HumidityGenerator::GenerateHumidity(ChunkInfo);
	HeightGenerator::GenerateHeight(ChunkInfo);
}

void ChunkBuilder::BrushSurface(Chunk& ChunkInfo)
{
}

void ChunkBuilder::CarveTerrain(Chunk& ChunkInfo)
{
}

void ChunkBuilder::SpawnFeatures(Chunk& ChunkInfo)
{
}

void ChunkBuilder::GenerateChunkMesh(const AGameModeBase* GameMode, Chunk& ChunkInfo)
{
	UWorld* World = GameMode->GetWorld();
	const FTransform NewTrans = FTransform(FRotator::ZeroRotator,ChunkInfo.ChunkWorldPosition);
	// AChunkActor* NewChunkActor = GetWorld()->SpawnActor<AChunkActor>(AChunkActor::StaticClass(), PosInput, FRotator::ZeroRotator);
	auto NewChunkActor = World->SpawnActorDeferred<AChunkActor>(AChunkActor::StaticClass(), NewTrans);
	if (NewChunkActor)
	{
	NewChunkActor->InitChunkActor(&ChunkInfo);
	NewChunkActor->FinishSpawning(NewTrans);
	// NewChunkActor->RenderMesh();
	NewChunkActor->RenderMeshGreedy();
	}
}

void ChunkBuilder::ClearIntermediateData()
{
	ContinentalnessGenerator::ClearMap();
}

void ChunkBuilder::DeleteChunkMesh(const AGameModeBase* GameMode, Chunk& ChunkInfo)
{
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Green, FString::Printf(TEXT("Deleting...")));
	if (ChunkInfo.Mesh.IsValid())
	{
		ChunkInfo.Mesh->ConditionalBeginDestroy();
		ChunkInfo.Mesh == nullptr;
	}
}
