// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MCTerrainDemo/Core/EnumClass.h"
#include "MCTerrainDemo/Core/ChunkMeshData.h"

constexpr size_t MaxBlockWidth = 16;
constexpr size_t MaxBlockHeight = 16;

using BlockData = TPair<uint64, EBlockTYpe>;

class MCTERRAINDEMO_API Chunk
{
private:
	TArray<BlockData> Blocks;
public:
	explicit Chunk(int32 X, int32 Y, FVector2d Position);
	~Chunk();
	// chunk索引
	const FIntPoint Index = {0, 0};
	// chunk位置
	FVector2d ChunkPosition;
	// chunk 网格数据
	FChunkMeshData MeshData;
	// chunk地形密度[-1.f, 1.f]
	float BlockDensity[MaxBlockWidth][MaxBlockWidth][MaxBlockHeight];
};
