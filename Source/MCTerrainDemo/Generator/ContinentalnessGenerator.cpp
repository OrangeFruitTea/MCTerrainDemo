// Fill out your copyright notice in the Description page of Project Settings.


#include "ContinentalnessGenerator.h"

bool ContinentalnessGenerator::LoadCurve()
{
	ContinentalCurve = LoadObject<UCurveFloat>(nullptr, (TEXT("Engine.CurveFloat'/Game/Core/Curve/Crv_Continental.Crv_Continental'")));
	if (ContinentalCurve != nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Load Continental Curve Success")));
		return true;
	}
	return false;
}

void ContinentalnessGenerator::GenerateContinental(Chunk& Chunk)
{
	if (LoadCurve())
	{
		for (int x = 0; x < MaxBlockWidth; x++)
		for (int y = 0; y < MaxBlockWidth; y++)
		for (int z = 0; z < MaxBlockHeight; z++)
		{
			const float Continental = NoiseLite->GetNoise(x+Chunk.ChunkWorldPosition.X, y+Chunk.ChunkWorldPosition.Y, double(z));
			Chunk.SetContinental(x,y,z,Continental);
			// GEngine->AddOnScreenDebugMessage(-1, 115.f, FColor::Green, FString::Printf(TEXT("Continental: (%f)"), Continental));
		}
	}
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Load Continental Curve Failed")));
}

float ContinentalnessGenerator::GetCrvValue(float Key)
{
	if (LoadCurve())
	{
		return ContinentalCurve->GetFloatValue(Key);
	}
	GEngine->AddOnScreenDebugMessage(-1, 115.f, FColor::Red, FString::Printf(TEXT("Load Continental Curve Failed")));
	return -1;
}
