// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MCTerrainDemo/Core/ChunkActor.h"
#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MCTerrainGenerationMode.generated.h"

constexpr int32 DrawDistance = 3;

UCLASS()
class MCTERRAINDEMO_API AMCTerrainGenerationMode : public AGameModeBase
{
	GENERATED_BODY()
public:
	// // 同步锁
	// static inline FCriticalSection CriticalSection;
	// 世界中心位置
	FVector WorldCenterLocation = FVector(0, 0, 0);
	FIntVector PlayerWorldLocation = FIntVector(0, 0, 0);
	// world中的所有chunk
	TMap<uint64,Chunk> Chunks;
	// 用于显示的chunk
	TSet<Chunk*> Chunks2Display;
	// 用于显示的chunk actor
	TArray<TWeakObjectPtr<AActor>> ChunkActors2Display;
	// 更新chunk
	void UpdateChunks();
	// 加载输入chunk的数据信息 (密度等)
	Chunk* LoadChunk(int x, int y, const FVector& PosInput);
public:
	UFUNCTION(BlueprintCallable, Category="TestFunc")
	void TestGenerateWorld();
	UFUNCTION(BlueprintCallable, Category="TestFunc")
	TArray<FIntPoint> GetAllChunks();
	// UFUNCTION(BlueprintCallable, Category="TestFunc")
	// FIntPoint GetPlayerLocatedChunkIndex();
};

// class FGenerateChunkAsyncTask : public FNonAbandonableTask
// {
// 	friend class FAutoDeleteAsyncTask<FGenerateChunkAsyncTask>;
// public:
// 	// 创建ChunkInfo所需参数
// 	FIntPoint ChunkIndex;
// 	FVector PosInput;
// 	AMCTerrainGenerationMode* TerrainGenerationMode;
// 	
// 	FGenerateChunkAsyncTask(const FIntPoint& ChunkIndex, const FVector& PosInput, AMCTerrainGenerationMode* TerrainGenerationMode);
// 	~FGenerateChunkAsyncTask() = default;
//
// 	void DoWork();
// 	
// 	FORCEINLINE TStatId GetStatId() const 
// 	{
// 		RETURN_QUICK_DECLARE_CYCLE_STAT(FGenerateChunkAsyncTask, STATGROUP_ThreadPoolAsyncTasks);
// 	}
// };