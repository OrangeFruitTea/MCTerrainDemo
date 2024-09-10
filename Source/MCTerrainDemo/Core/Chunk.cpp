// Fill out your copyright notice in the Description page of Project Settings.


#include "Chunk.h"


Chunk::Chunk(int32 X, int32 Y, FVector2d Position)
	:BlockDensity{0},
	Index{X, Y}
{
	ChunkPosition = Position;
	ChunkActor = nullptr;
}

Chunk::~Chunk()
{
}

