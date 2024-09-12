// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MCTerrainDemo/Core/ChunkActor.h"
#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MCTerrainGenerationMode.generated.h"

const int32 WorldRadius = 1;

UCLASS()
class MCTERRAINDEMO_API AMCTerrainGenerationMode : public AGameModeBase
{
	GENERATED_BODY()
protected:
	// 世界中心位置
	FVector2d WorldCenterLocation = FVector2d(0, 0);
	// world中的所有chunk
	TMap<uint64,Chunk> Chunks;
	// 用于显示的chunk
	TSet<Chunk*> Chunks2Display;
	// 用于显示的chunk actor
	TArray<TWeakObjectPtr<AChunkActor>> ChunkActors2Display;
	// 更新chunk
	void UpdateChunks();
	// 加载输入chunk的数据信息 (密度等)
	static void LoadChunk(Chunk& Chunk);
public:
	UFUNCTION(BlueprintCallable, Category="TestFunc")
	void TestGenerateWorld();
};
