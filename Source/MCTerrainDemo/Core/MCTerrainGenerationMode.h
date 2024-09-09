// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MCTerrainDemo/Generator/HeightGenerator.h"
#include "MCTerrainDemo/Core/GlobalInfo.h"

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
	// 世界数据信息
	GlobalInfo Info;
	// world中的所有chunk
	TMap<uint64,Chunk> Chunks;
	// 用于显示的chunk
	TSet<Chunk*> CHunks2Display;
	// 更新chunk
	void UpdateChunks();
	// 加载输入chunk的数据信息 (密度等)
	static void LoadChunk(Chunk& Chunk);
	// 根据chunk的数据信息显示chunk中的方块
	void DisplayChunk(const Chunk& Chunk);
	// 生成单个方块
	void TestCreateBlock(const FVector3d& Pos, int32 BlockID) const;
public:
	UFUNCTION(BlueprintCallable, Category="TestFunc")
	void TestGenerateWorld();
};
