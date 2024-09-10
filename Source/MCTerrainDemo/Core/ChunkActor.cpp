// Fill out your copyright notice in the Description page of Project Settings.


#include "ChunkActor.h"

AChunkActor::AChunkActor()
{
	PrimaryActorTick.bCanEverTick = true;

	FString String = "ChunkActor_Test";
	FName Name = FName(String);
	ProceduralMesh = CreateDefaultSubobject<UProceduralMeshComponent>(Name);
	ProceduralMesh->RegisterComponent();
	SetRootComponent(ProceduralMesh);
}

void AChunkActor::InitChunkActor(float X, float Y)
{
	FString String = "ChunkActor_" + FString::FromInt(X) + "_" + FString::FromInt(Y);
	FName Name = FName(String);
	ProceduralMesh = CreateDefaultSubobject<UProceduralMeshComponent>(Name);
	ProceduralMesh->RegisterComponent();
	SetRootComponent(ProceduralMesh);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, String);
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

