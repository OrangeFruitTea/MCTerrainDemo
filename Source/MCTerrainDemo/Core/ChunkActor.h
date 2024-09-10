// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MCTerrainDemo/Core/Chunk.h"
#include "GameFramework/Actor.h"
#include "ProceduralMeshComponent.h"
#include "ChunkActor.generated.h"

constexpr int32 BlockSize = 50;

UCLASS()
class MCTERRAINDEMO_API AChunkActor : public AActor
{
	GENERATED_BODY()
private:
	Chunk* ChunkInfo;
public:
	UPROPERTY(EditAnywhere, Category="Setup")
	UProceduralMeshComponent* ProceduralMesh;
	
public:
	AChunkActor();
	AChunkActor(Chunk* ChunkData);

protected:
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
