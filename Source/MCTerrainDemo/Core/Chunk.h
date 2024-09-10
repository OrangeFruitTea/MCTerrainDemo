// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MCTerrainDemo/Core/ChunkActor.h"

constexpr size_t MaxBlockWidth = 16;
constexpr size_t MaxBlockHeight = 16;

class MCTERRAINDEMO_API Chunk
{
public:
	explicit Chunk(int32 X, int32 Y, FVector2d Position);
	~Chunk();
	// chunk索引
	TPair<int32, int32> Index = {0, 0};
	// chunk位置
	FVector2d ChunkPosition;
	// chunk地形密度[-1.f, 1.f]
	float BlockDensity[MaxBlockWidth][MaxBlockWidth][MaxBlockHeight];
	// chunk Actor
	AChunkActor* ChunkActor;
	
};
