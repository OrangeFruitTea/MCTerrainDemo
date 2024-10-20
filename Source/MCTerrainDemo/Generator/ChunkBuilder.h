// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MCTerrainDemo/Core/Chunk.h"
#include "MCTerrainDemo/Core/ChunkActor.h"
#include "ContinentalnessGenerator.h"
#include "HeightGenerator.h"

/**
 * 
 */
class MCTERRAINDEMO_API ChunkBuilder
{
	// TMap<int, TFunction<void(Chunk&)>> BuildSteps;
public:
	ChunkBuilder()=delete;
	~ChunkBuilder()=delete;
	// chunk加载相关
	// 生成结构范围
	static void SpawnStructStarts(Chunk& ChunkInfo);
	// 计算结构引用
	static void CalculateStructRef(Chunk& ChunkInfo);
	// 计算生物群系
	static void SpawnBiomes(Chunk& ChunkInfo);
	// 填充初始地形
	static void FillBasicTerrain(Chunk& ChunkInfo);
	// 应用表面规则
	static void BrushSurface(Chunk& ChunkInfo);
	// 地形雕刻
	static void CarveTerrain(Chunk& ChunkInfo);
	// 地物生成
	static void SpawnFeatures(Chunk& ChunkInfo);
	// 生成网格
	static void GenerateChunkMesh(UWorld* World, Chunk& ChunkInfo);
	// 生成初始实体
};
