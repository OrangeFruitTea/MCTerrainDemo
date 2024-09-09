// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MCTerrainDemo/Tool/NoiseTool.h"
#include "MCTerrainDemo/Core/Chunk.h"

using BlockData = TPair<uint64, int32>;

class MCTERRAINDEMO_API GlobalInfo
{
private:
	// 全局方块列表
	TMap<uint64, int32> GlobalBlocks;
	TArray<BlockData> Blocks2Display;
public:
	GlobalInfo();
	~GlobalInfo();

	// 添加方块
	void AddBlock(const FVector& Pos, int32 BlockID);
	// 删除方块
	void RemoveBlock(const FVector& Pos);
	// 查找方块
	int32* FindBlock(const FVector& Pos);
	// 获取待显示方块列表
	TArray<BlockData>& GetBlocks2Display();
};
