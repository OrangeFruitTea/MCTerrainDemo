// Fill out your copyright notice in the Description page of Project Settings.


#include "MCTerrainGenerationMode.h"

#include "Kismet/GameplayStatics.h"
#include "MCTerrainDemo/Generator/HeightGenerator.h"
#include "MCTerrainDemo/Generator/ContinentalnessGenerator.h"
#include "MCTerrainDemo/Tool/IndexTool.h"
#include "MCTerrainDemo/Generator/ChunkBuilder.h"

void AMCTerrainGenerationMode::UpdateChunks()
{
	const APlayerController* Controller = UGameplayStatics::GetPlayerController(this, 0);
	if (Controller != nullptr)
	{
		const APawn* Pawn = Controller->GetPawn();
		if (Pawn != nullptr)
		{
			PlayerWorldLocation = static_cast<FIntVector>(Pawn->GetActorLocation() / 100.f);
		}
	}
	// 当前玩家所处的区块Index
	const FIntPoint ChunkIndex = {PlayerWorldLocation.X / MaxBlockWidth, PlayerWorldLocation.Y / MaxBlockWidth};
	for (int i = -DrawDistance; i <= DrawDistance; i++)
	for (int j = -DrawDistance; j <= DrawDistance; j++)
	{
		// const FVector PosInput = FVector(MaxBlockWidth*(i)+(WorldCenterLocation.X), MaxBlockWidth*(j)+(WorldCenterLocation.Y), 0.0f);
		const FVector PosInput = FVector(MaxBlockWidth*(i+ChunkIndex.X), MaxBlockWidth*(j+ChunkIndex.Y), 0.0f);
		Chunk* NewChunk = LoadChunk(ChunkIndex.X + i,ChunkIndex.Y + j,PosInput);
		if (NewChunk)
		{
			// SpawnChunkActor(*NewChunk);
			ChunkBuilder::GenerateChunkMesh(GetWorld(), *NewChunk);
		}
	}
}

Chunk* AMCTerrainGenerationMode::LoadChunk(int x, int y, const FVector& PosInput)
{
	// 根据ChunkIndex判断是否已经生成Chunk
	uint64 Index = IndexTool::Index(x, y);
	if (!Chunks.Contains(Index))
	{
		// chunk信息载入至Info中
		Chunks.Emplace(Index, Chunk(x, y, PosInput));
		// GEngine->AddOnScreenDebugMessage(-1, 115.f, FColor::Green, FString::Printf(TEXT("Chunk Number: (%f, %f)"), PosInput.X, PosInput.Y));
		Chunk& NewChunk = Chunks[Index];

		// 数据生成
		ContinentalnessGenerator::GenerateContinental(NewChunk);
		// HeightGenerator::GenerateDensity(NewChunk);
		HeightGenerator::GenerateHeight(NewChunk);

		return &NewChunk;
	}
	return nullptr;
}

// void AMCTerrainGenerationMode::SpawnChunkActor(Chunk& NewChunk)
// {
// 	const FTransform NewTrans = FTransform(FRotator::ZeroRotator,NewChunk.ChunkWorldPosition);
// 	// AChunkActor* NewChunkActor = GetWorld()->SpawnActor<AChunkActor>(AChunkActor::StaticClass(), PosInput, FRotator::ZeroRotator);
// 	auto NewChunkActor = GetWorld()->SpawnActorDeferred<AChunkActor>(AChunkActor::StaticClass(), NewTrans);
// 	if (NewChunkActor)
// 	{
// 	NewChunkActor->InitChunkActor(&NewChunk);
// 	NewChunkActor->FinishSpawning(NewTrans);
// 	// NewChunkActor->SetActorLocationAndRotation(NewChunk.ChunkWorldPosition, FRotator::ZeroRotator);
// 	// GEngine->AddOnScreenDebugMessage(-1, 115.f, FColor::Green, FString::Printf(TEXT("Chunk Position: (%f, %f)"), Pos.X, Pos.Y));
// 	ChunkActors2Display.Emplace(NewChunkActor);
// 	// NewChunkActor->RenderMesh();
// 	NewChunkActor->RenderMeshGreedy();
// 	}
// }

void AMCTerrainGenerationMode::TestGenerateWorld()
{
	UpdateChunks();
}
