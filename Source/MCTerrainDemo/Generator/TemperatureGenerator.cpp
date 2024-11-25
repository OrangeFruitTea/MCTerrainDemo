// Fill out your copyright notice in the Description page of Project Settings.


#include "TemperatureGenerator.h"

#include "MCTerrainDemo/Core/LocationCastLibrary.h"

void TemperatureGenerator::SetSeed(const int32 Seed)
{
	NoiseLite->SetSeed(Seed);
}

float TemperatureGenerator::GetWorldBlockTemperature(int WorldX, int WorldY, int WorldZ)
{
	const FVector Input = ULocationCastLibrary::WorldToNoiseParam(WorldX, WorldY, WorldZ);
	return NoiseLite->GetNoise(Input.X, Input.Y, Input.Z);
}

float TemperatureGenerator::GetWorldBlockTemperature(FIntVector WorldLocation)
{
	return GetWorldBlockTemperature(WorldLocation.X, WorldLocation.Y, WorldLocation.Z);
}

float TemperatureGenerator::GetRelativeBlockTemperature(const Chunk& Chunk, int X, int Y, int Z)
{
	return NoiseLite->GetNoise(X+Chunk.ChunkWorldPosition.X, Y+Chunk.ChunkWorldPosition.Y, double(Z));
}

void TemperatureGenerator::GenerateTemperature(const Chunk& Chunk)
{
	for (int x = 0; x < MaxBlockWidth; x++)
	for (int y = 0; y < MaxBlockWidth; y++)
	for (int z = 0; z < MaxBlockHeight; z++)
	{
		uint64 DataIndex = IndexTool::Index(x,y,z);
		TemperatureMap.Emplace(DataIndex, GetRelativeBlockTemperature(Chunk,x,y,z));
	}
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Green, FString::Printf(TEXT("Temperature Generated.")));
}

float TemperatureGenerator::GetTemperatureByIndex(int X, int Y, int Z)
{
	const uint64 DataIndex = IndexTool::Index(X,Y,Z);
	if (TemperatureMap.Contains(DataIndex))
	{
		return TemperatureMap[DataIndex];
	}
	return 1;
}

void TemperatureGenerator::ClearMap()
{
	TemperatureMap.Empty();
}
