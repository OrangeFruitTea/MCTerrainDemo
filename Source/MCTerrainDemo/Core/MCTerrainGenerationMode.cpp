// Fill out your copyright notice in the Description page of Project Settings.


#include "MCTerrainGenerationMode.h"
#include "MCTerrainDemo/Generator/HeightGenerator.h"
#include "MCTerrainDemo/Tool/NoiseTool.h"

void AMCTerrainGenerationMode::UpdateChunks()
{
	for (int i = -DrawDistance; i <= DrawDistance; i++)
	for (int j = -DrawDistance; j <= DrawDistance; j++)
	{
		FVector PosInput = FVector(MaxBlockWidth*(i)+(WorldCenterLocation.X), MaxBlockWidth*(j)+(WorldCenterLocation.Y), 0.0f);
		uint64 Index = NoiseTool::Index(PosInput.X, PosInput.Y);
		if (!Chunks.Contains(Index))
		{
			Chunks.Emplace(Index, Chunk(i, j, PosInput));
			Chunk& NewChunk = Chunks[Index];
			// HeightGenerator::GenerateDensity(NewChunk);
			HeightGenerator::GenerateHeight(NewChunk);
			AChunkActor* NewChunkActor = GetWorld()->SpawnActor<AChunkActor>(AChunkActor::StaticClass(), PosInput, FRotator::ZeroRotator);
			NewChunkActor->InitChunkActor(&NewChunk);
			// NewChunkActor->SetActorLocationAndRotation(PosInput, FRotator::ZeroRotator);
			// GEngine->AddOnScreenDebugMessage(-1, 115.f, FColor::Green, FString::Printf(TEXT("Chunk Position: (%f, %f)"), Pos.X, Pos.Y));
			ChunkActors2Display.Emplace(NewChunkActor);
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
