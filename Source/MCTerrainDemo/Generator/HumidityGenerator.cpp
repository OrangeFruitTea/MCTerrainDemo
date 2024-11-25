// Fill out your copyright notice in the Description page of Project Settings.


#include "HumidityGenerator.h"
#include "MCTerrainDemo/Core/LocationCastLibrary.h"

void HumidityGenerator::SetSeed(const int32 Seed)
{
	NoiseLite->SetSeed(Seed);
}

float HumidityGenerator::GetWorldBlockHumidity(int WorldX, int WorldY, int WorldZ)
{
	const FVector Input = ULocationCastLibrary::WorldToNoiseParam(WorldX, WorldY, WorldZ);
	return NoiseLite->GetNoise(Input.X, Input.Y, Input.Z);
}

float HumidityGenerator::GetWorldBlockHumidity(FIntVector WorldLocation)
{
	return GetWorldBlockHumidity(WorldLocation.X, WorldLocation.Y, WorldLocation.Z);
}

float HumidityGenerator::GetRelativeBlockHumidity(const Chunk& Chunk, int X, int Y, int Z)
{
	return NoiseLite->GetNoise(X+Chunk.ChunkWorldPosition.X, Y+Chunk.ChunkWorldPosition.Y, double(Z));
}

void HumidityGenerator::GenerateHumidity(const Chunk& Chunk)
{
	for (int x = 0; x < MaxBlockWidth; x++)
	for (int y = 0; y < MaxBlockWidth; y++)
	for (int z = 0; z < MaxBlockHeight; z++)
	{
		uint64 DataIndex = IndexTool::Index(x,y,z);
		HumidityMap.Emplace(DataIndex, GetRelativeBlockHumidity(Chunk,x,y,z));
	}
}

float HumidityGenerator::GetHumidityByIndex(int X, int Y, int Z)
{
	const uint64 DataIndex = IndexTool::Index(X,Y,Z);
	if (HumidityMap.Contains(DataIndex))
	{
		return HumidityMap[DataIndex];
	}
	return 1;
}

void HumidityGenerator::ClearMap()
{
	HumidityMap.Empty();
}
