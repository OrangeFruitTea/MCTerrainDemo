// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

constexpr size_t MaxBlockWidth = 16;
constexpr size_t MaxBlockHeight = 64;

class MCTERRAINDEMO_API Chunk
{
public:
	explicit Chunk(FVector2d ChunkPosition);
	~Chunk();
	// chunk位置
	FVector2d ChunkPosition;
	// chunk地形密度[-1.f, 1.f]
	float BlockDensity[MaxBlockWidth][MaxBlockWidth][MaxBlockHeight];
	void TestGenerateChunk() const;
	void TestCreateBlock(FVector3d Pos);
};
