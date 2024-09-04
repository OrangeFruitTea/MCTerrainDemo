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
