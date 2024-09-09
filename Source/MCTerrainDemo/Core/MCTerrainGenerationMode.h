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
	// 世界中心位置
	FVector2d WorldCenterLocation = FVector2d(0, 0);
	// world中的所有chunk
	TMap<uint64,Chunk> Chunks;
	// 更新chunk
	void UpdateChunks();
	// 加载输入chunk的数据信息 (密度等)
	static void LoadChunk(Chunk& Chunk);
	// 根据chunk的数据信息生成chunk中的方块
	void GenerateChunk(const Chunk& Chunk) const;
	// 生成单个方块
	void TestCreateBlock(const FVector3d& Pos) const;
public:
	UFUNCTION(BlueprintCallable, Category="TestFunc")
	void TestGenerateWorld();
};
