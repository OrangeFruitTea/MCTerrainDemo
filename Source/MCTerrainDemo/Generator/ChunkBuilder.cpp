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

void ChunkBuilder::GenerateChunkMesh(UWorld* World, Chunk& ChunkInfo)
{
	const FTransform NewTrans = FTransform(FRotator::ZeroRotator,ChunkInfo.ChunkWorldPosition);
	// AChunkActor* NewChunkActor = GetWorld()->SpawnActor<AChunkActor>(AChunkActor::StaticClass(), PosInput, FRotator::ZeroRotator);
	auto NewChunkActor = World->SpawnActorDeferred<AChunkActor>(AChunkActor::StaticClass(), NewTrans);
	if (NewChunkActor)
	{
	NewChunkActor->InitChunkActor(&ChunkInfo);
	NewChunkActor->FinishSpawning(NewTrans);
	// NewChunkActor->SetActorLocationAndRotation(NewChunk.ChunkWorldPosition, FRotator::ZeroRotator);
	// GEngine->AddOnScreenDebugMessage(-1, 115.f, FColor::Green, FString::Printf(TEXT("Chunk Position: (%f, %f)"), Pos.X, Pos.Y));
	// NewChunkActor->RenderMesh();
	NewChunkActor->RenderMeshGreedy();
	}
}

void ChunkBuilder::DeleteChunkMesh(UWorld* World, Chunk& ChunkInfo)
{
}
