// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MCTerrainDemo/Generator/HeightGenerator.h"

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MCTerrainGenerationMode.generated.h"

const int32 WorldRadius = 3;

UCLASS()
class MCTERRAINDEMO_API AMCTerrainGenerationMode : public AGameModeBase
{
	GENERATED_BODY()
protected:
	Chunk* TestChunk = new Chunk(FVector2d(0, 0));
	TMap<uint64,Chunk> Chunks;
	FVector2d WorldCenterLocation = FVector2d(0, 0);
	void UpdateChunks();
	static void LoadChunk(Chunk& Chunk);
	void GenerateChunk(const Chunk& Chunk) const;
	void TestCreateBlock(const FVector3d& Pos) const;
public:
	UFUNCTION(BlueprintCallable, Category="TestFunc")
	void TestGenerateWorld();
};
