// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MCTerrainDemo/Core/EnumClass.h"
#include "MCTerrainDemo/Core/ChunkMeshData.h"

constexpr size_t MaxBlockWidth = 16;
constexpr size_t MaxBlockHeight = 16;

constexpr int32 BlockSize = 50;
constexpr int32 BlockSizeHalf = BlockSize/2;

class MCTERRAINDEMO_API Chunk
{
private:
	// uint64: 压缩后的block的相对坐标; 世界坐标使用GerBlockWorldPosition获取
	TMap<uint64, EBlockType> Blocks;

	// 压缩与解压block相对坐标
	uint64 Index(const int32 X, const int32 Y, const int32 Z) const;
	uint64 Index(const FIntVector& Vec) const;
	FIntVector UnIndex(const uint64 Index) const;
public:
	explicit Chunk(int32 X, int32 Y, FVector2d Position);
	~Chunk();
	
	// chunk索引
	const FIntPoint ChunkIndex = {0, 0};
	// chunk的世界位置
	FVector2d ChunkWorldPosition;
	// chunk 网格数据
	FChunkMeshData MeshData;

	TMap<uint64, EBlockType>* GetBlockData();
	EBlockType GetBlock(const int X, const int Y, const int Z);
	
	FVector GetBlockWorldPosition(const int X, const int Y, const int Z) const;
	FVector GetBlockWorldPosition(uint64 DataIndex) const;
	
	// 向chunk数据中加入block, XYZ: 对应的数组下标
	void AddBlock2Data(EBlockType BlockType, const int X, const int Y, const int Z);
	// chunk地形密度[-1.f, 1.f]
	float BlockDensity[MaxBlockWidth][MaxBlockWidth][MaxBlockHeight];
};
