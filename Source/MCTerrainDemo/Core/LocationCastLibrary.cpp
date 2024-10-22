// Fill out your copyright notice in the Description page of Project Settings.


#include "LocationCastLibrary.h"

#include "GameFramework/GameModeBase.h"

APawn* ULocationCastLibrary::GetPlayerPawn(const UWorld* World, const int Index)
{
	const APlayerController* Controller = UGameplayStatics::GetPlayerController(World, Index);
	if (Controller)
	{
		return Controller->GetPawn();
	}
	return nullptr;
}

FVector ULocationCastLibrary::ChunkIndexToChunkInfoLocation(int32 X, int32 Y)
{
	return FVector(MaxBlockWidth * X, MaxBlockWidth * Y, 0.0f);
}

FIntVector ULocationCastLibrary::BlockRelativeToWorldLocation(FIntPoint ChunkIndex, int X, int Y, int Z)
{
	return FIntVector(ChunkIndex.X * MaxBlockWidth + X, ChunkIndex.Y * MaxBlockWidth + Y, Z);
}

FIntVector ULocationCastLibrary::EngineToWorldLocation(FVector EngineLocation)
{
	return static_cast<FIntVector>(EngineLocation / (BlockSize * 2));
}

FVector ULocationCastLibrary::WorldToEngineLocation(FIntVector WorldLocation)
{
	return static_cast<FVector>(WorldLocation * (BlockSize * 2));
}

FIntPoint ULocationCastLibrary::WorldToChunkIndex(FIntVector WorldLocation)
{
	int X = WorldLocation.X / MaxBlockWidth;
	if (WorldLocation.X < 0) X -= 1;
	int Y = WorldLocation.Y / MaxBlockWidth;
	if (WorldLocation.Y < 0) Y -= 1;
	return FIntPoint{X,Y};
}

FIntVector ULocationCastLibrary::GetPlayerWorldLocation(const AGameModeBase* GameMode, const int Index)
{
	const UWorld* World = GameMode->GetWorld();
	const APawn* Pawn = GetPlayerPawn(World, Index);
	return EngineToWorldLocation(Pawn->GetActorLocation());
}

FIntPoint ULocationCastLibrary::GetPlayerLocatedChunkIndex(const AGameModeBase* GameMode, const int Index)
{
	return WorldToChunkIndex(GetPlayerWorldLocation(GameMode, Index));
}


