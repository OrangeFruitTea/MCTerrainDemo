// Fill out your copyright notice in the Description page of Project Settings.


#include "MCTerrainGenerationMode.h"
#include "MCTerrainDemo/Generator/HeightGenerator.h"
#include "MCTerrainDemo/Tool/NoiseTool.h"

void AMCTerrainGenerationMode::UpdateChunks()
{
	for (int i = 0; i < WorldRadius-3; i++)
	for (int j = 0; j < WorldRadius+5; j++)
	{
		FVector2d ChunkPosition = FVector2d(WorldCenterLocation.X+i*MaxBlockWidth, WorldCenterLocation.Y+j*MaxBlockWidth);
		FVector3d PosInput = FVector3d(ChunkPosition.X, ChunkPosition.Y, 10);
		uint64 Index = NoiseTool::Index(ChunkPosition.X, ChunkPosition.Y);
		if (!Chunks.Contains(Index))
		{
			Chunks.Emplace(Index, Chunk(i, j, ChunkPosition));
			Chunk& NewChunk = Chunks[Index];
			HeightGenerator::GenerateDensity(NewChunk);
			AChunkActor* NewChunkActor = GetWorld()->SpawnActor<AChunkActor>(AChunkActor::StaticClass());
			NewChunkActor->InitChunkActor(&NewChunk);
			NewChunkActor->SetActorLocation(PosInput);
			// GEngine->AddOnScreenDebugMessage(-1, 115.f, FColor::Green, FString::Printf(TEXT("Chunk Position: (%f, %f)"), Pos.X, Pos.Y));
			ChunkActors2Display.Emplace(NewChunkActor);
			// LoadChunk(NewChunk);
			// DisplayChunk(NewChunk);
			NewChunkActor->RenderMesh();
		}
	}
}

void AMCTerrainGenerationMode::LoadChunk(Chunk& Chunk)
{
	HeightGenerator::GenerateDensity(Chunk);
}

void AMCTerrainGenerationMode::TestGenerateWorld()
{
	UpdateChunks();
}
