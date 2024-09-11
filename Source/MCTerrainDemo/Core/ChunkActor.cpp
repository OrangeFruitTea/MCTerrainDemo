// Fill out your copyright notice in the Description page of Project Settings.


#include "ChunkActor.h"

AChunkActor::AChunkActor()
{
	PrimaryActorTick.bCanEverTick = true;

	FString String = "ChunkActor_Test";
	FName Name = FName(String);
	ProceduralMesh = CreateDefaultSubobject<UProceduralMeshComponent>(Name);
	ProceduralMesh->RegisterComponent();
}

void AChunkActor::InitChunkActor(float X, float Y)
{
	const FString NewString = "ChunkActor_" + FString::FromInt(X) + "_" + FString::FromInt(Y);
	const TCHAR* NewName = *NewString;
	ProceduralMesh->Rename(NewName);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, NewString);
}

// Called when the game starts or when spawned
void AChunkActor::BeginPlay()
{
	Super::BeginPlay();
	SetRootComponent(ProceduralMesh);
	
}

// Called every frame
void AChunkActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

