// Fill out your copyright notice in the Description page of Project Settings.


#include "Chunk.h"

TMap<uint64, EBlockType>* Chunk::GetBlockData()
{
	return &Blocks;
}

EBlockType Chunk::GetBlock(const int X, const int Y, const int Z)
{
	const uint64 DataIndex = Index(X,Y,Z);
	if (Blocks.Contains(DataIndex))
		return Blocks[DataIndex];
	return Air;
}

void Chunk::AddBlock2Data(EBlockType BlockType, const int X, const int Y, const int Z)
{
	uint64 DataIndex = Index(X,Y,Z);
	Blocks.Emplace(DataIndex, BlockType);
}

FVector Chunk::GetBlockWorldPosition(const int X, const int Y, const int Z) const 
{
	// 计算方块在世界中的位置
	return FVector (
		ChunkIndex.X * BlockSize * 16 + X * BlockSize,
		ChunkIndex.Y * BlockSize * 16 + Y * BlockSize,
		Z * BlockSize
	);
}

FVector Chunk::GetBlockWorldPosition(uint64 DataIndex) const
{
	FIntVector Vec = UnIndex(DataIndex);
	return GetBlockWorldPosition(Vec.X, Vec.Y, Vec.Z);
}

uint64 Chunk::Index(const int32 X, const int32 Y, const int32 Z) const
{
	constexpr int32 Offset = 16384;
	return uint64(X+Offset)<<40|uint64(Y+Offset)<<20|uint64(Z+Offset);
}

uint64 Chunk::Index(const FIntVector& Vec) const
{
	return Index(Vec.X, Vec.Y, Vec.Z);
}

FIntVector Chunk::UnIndex(const uint64 Index) const
{
	constexpr int32 Offset = 16384;
	return FIntVector(
		int32(Index>>40)-Offset,
		int32((Index>>20)&0xFFFFF)-Offset,
		int32(Index&0xFFFFF)-Offset);
}

Chunk::Chunk(int32 X, int32 Y, FVector2d Position)
	: Blocks{},
	ChunkIndex{X, Y},
	BlockDensity{0}
{
	ChunkWorldPosition = Position;
}

Chunk::~Chunk()
{
}

