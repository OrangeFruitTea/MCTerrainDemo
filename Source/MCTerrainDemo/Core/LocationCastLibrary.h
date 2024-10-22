// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Chunk.h"
#include "Kismet/GameplayStatics.h"
#include "LocationCastLibrary.generated.h"

/**
 * 
 */
UCLASS()
class MCTERRAINDEMO_API ULocationCastLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
private:
	static APawn* GetPlayerPawn(const UWorld* World, const int Index = 0);
public:
	static FVector ChunkIndexToChunkInfoLocation(int32 X, int32 Y);
	UFUNCTION(BlueprintCallable, Category="LocationCast")
	static FIntVector BlockRelativeToWorldLocation(FIntPoint ChunkIndex, int X, int Y, int Z);
	UFUNCTION(BlueprintCallable, Category="LocationCast")
	static FIntVector EngineToWorldLocation(FVector EngineLocation);
	UFUNCTION(BlueprintCallable, Category="LocationCast")
	static FVector WorldToEngineLocation(FIntVector WorldLocation);
	UFUNCTION(BlueprintCallable, Category="LocationCast")
	static FIntPoint WorldToChunkIndex(FIntVector WorldLocation);
	UFUNCTION(BlueprintCallable, Category="LocationCast")
	static FIntVector GetPlayerWorldLocation(const AGameModeBase* GameMode, const int Index = 0);
	UFUNCTION(BlueprintCallable, Category="LocationCast")
	static FIntPoint GetPlayerLocatedChunkIndex(const AGameModeBase* GameMode, const int Index = 0);
	
};