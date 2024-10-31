// Fill out your copyright notice in the Description page of Project Settings.


#include "ContinentalnessGenerator.h"
#include "MCTerrainDemo/Core/LocationCastLibrary.h"

bool ContinentalnessGenerator::LoadCurve()
{
	ContinentalCurve = LoadObject<UCurveFloat>(nullptr, (TEXT("Engine.CurveFloat'/Game/Core/Curve/Crv_Continental.Crv_Continental'")));
	if (ContinentalCurve != nullptr)
	{
		return true;
	}
	return false;
}

void ContinentalnessGenerator::SetSeed(const int32 Seed)
{
	NoiseLite->SetSeed(Seed);
}

float ContinentalnessGenerator::GetWorldBlockContinental(int WorldX, int WorldY, int WorldZ)
{
	const FVector Input = ULocationCastLibrary::WorldToNoiseParam(WorldX, WorldY, WorldZ);
	return NoiseLite->GetNoise(Input.X, Input.Y, Input.Z);
}

float ContinentalnessGenerator::GetRelativeBlockContinental(const Chunk& Chunk, int X, int Y, int Z)
{
	return NoiseLite->GetNoise(X+Chunk.ChunkWorldPosition.X, Y+Chunk.ChunkWorldPosition.Y, double(Z));
}

void ContinentalnessGenerator::GenerateContinental(const Chunk& Chunk)
{
	if (LoadCurve())
	{
		for (int x = 0; x < MaxBlockWidth; x++)
		for (int y = 0; y < MaxBlockWidth; y++)
		for (int z = 0; z < MaxBlockHeight; z++)
		{
			// Chunk.SetContinental(x,y,z,GetRelativeBlockContinental(Chunk,x,y,z));
			uint64 DataIndex = IndexTool::Index(x,y,z);
			ContinentalMap.Emplace(DataIndex, GetRelativeBlockContinental(Chunk,x,y,z));
			// GEngine->AddOnScreenDebugMessage(-1, 115.f, FColor::Green, FString::Printf(TEXT("Continental: (%f)"), Continental));
		}
	}
}

float ContinentalnessGenerator::GetContinentalByIndex(int X, int Y, int Z)
{
	const uint64 DataIndex = IndexTool::Index(X,Y,Z);
	if (ContinentalMap.Contains(DataIndex))
	{
		return ContinentalMap[DataIndex];
	}
	return -1;
}

void ContinentalnessGenerator::ClearMap()
{
	ContinentalMap.Empty();
}

float ContinentalnessGenerator::GetCrvValue(float Key)
{
	if (LoadCurve())
	{
		return ContinentalCurve->GetFloatValue(Key);
	}
	return -1;
}
