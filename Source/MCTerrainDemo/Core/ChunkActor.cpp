// Fill out your copyright notice in the Description page of Project Settings.


#include "ChunkActor.h"

AChunkActor::AChunkActor()
{
	PrimaryActorTick.bCanEverTick = true;

	ChunkInfo = nullptr;
	FString String = "ChunkActor_Test";
	ProceduralMesh = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("MeshComponent"));
	ProceduralMesh->RegisterComponent();
	SetRootComponent(ProceduralMesh);
}

// Sets default values
AChunkActor::AChunkActor(Chunk* ChunkData)
{
	PrimaryActorTick.bCanEverTick = true;

	ChunkInfo = ChunkData;
	FString String = "ChunkActor_" + FString::FromInt(ChunkInfo->ChunkPosition.X) + "_" + FString::FromInt(ChunkInfo->ChunkPosition.Y);
	ProceduralMesh = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("MeshComponent"));
	ProceduralMesh->RegisterComponent();
	SetRootComponent(ProceduralMesh);
}

// Called when the game starts or when spawned
void AChunkActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AChunkActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

