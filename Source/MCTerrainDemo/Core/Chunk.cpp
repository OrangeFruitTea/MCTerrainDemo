// Fill out your copyright notice in the Description page of Project Settings.


#include "Chunk.h"


Chunk::Chunk(int32 X, int32 Y, FVector2d Position)
	: Index{X, Y},
	BlockDensity{0}
{
	ChunkPosition = Position;
	// ChunkActor = nullptr;
}

Chunk::~Chunk()
{
}

