// Fill out your copyright notice in the Description page of Project Settings.


#include "Chunk.h"
#include "MCTerrainDemo/Block.h"


Chunk::Chunk(FVector2d Position)
	:BlockDensity{0}
{
	ChunkPosition = Position;
}

Chunk::~Chunk()
{
}

void Chunk::TestGenerateChunk() const
{
	for (int i = 0; i < MaxBlockWidth; i++)
	for(int j = 0; j < MaxBlockWidth; j++)
	for (int k = 0; k < MaxBlockHeight; k++)
	{
		if (BlockDensity[i][j][k] > 0.f)
		{
			// 生成方块
		}		
	}
}