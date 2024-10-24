// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MCTerrainDemo/Core/EnumClass.h"
#include "MCTerrainDemo/Core/ChunkMeshData.h"

class AChunkActor;

constexpr int32 MaxBlockWidth = 16;
constexpr int32 MaxBlockHeight = 96;

constexpr int32 BlockSize = 50;
constexpr int32 BlockSizeHalf = BlockSize / 2;

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
	explicit Chunk(int32 X, int32 Y, const FVector& Position);
	~Chunk()=default;

	// chunk索引
	const FIntPoint ChunkIndex = {0, 0};
private:
	// chunk计算等级
	ECalculateLevel CalculateLevel = ECalculateLevel::Active;
public:
	void SetChunkCalculateLevel(ECalculateLevel Value);
	ECalculateLevel GetChunkCalculateLevel() const;
public:
	// chunk对应的chunkActor
	TWeakObjectPtr<AChunkActor> Mesh;
	// chunk的世界位置
	FVector ChunkWorldPosition;
	// chunk 网格数据
	TMap<EBlockType, FChunkMeshData> Sections;

	TMap<uint64, EBlockType>* GetBlockData();
	EBlockType GetBlock(const FIntVector& Vec);
	EBlockType GetBlock(const int X, const int Y, const int Z);

	FVector GetBlockWorldPosition(const int X, const int Y, const int Z) const;
	FVector GetBlockWorldPosition(uint64 DataIndex) const;

	// 向chunk数据中加入block, XYZ: 对应的数组下标
	void AddBlock2Data(EBlockType BlockType, const int X, const int Y, const int Z);

	
	// chunk地形密度[-1.f, 1.f]
private:
	TMap<uint64, float> Density;

public:
	void SetDensity(const int X, const int Y, const int Z, float Value);
	float GetDensity(const int X, const int Y, const int Z);
	// chunk大陆性
private:
	TMap<uint64, float> Continental;

public:
	void SetContinental(const int X, const int Y, const int Z, float Value);
	float GetContinental(const int X, const int Y);
	float GetContinental(const int X, const int Y, const int Z);
};
