// Fill out your copyright notice in the Description page of Project Settings.


#include "Block.h"

// Sets default values
ABlock::ABlock()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	MeshComponent->SetupAttachment(GetRootComponent());

	const FString StaticMeshPath = TEXT("/Game/Models/Block.Block");
	UStaticMesh* LoadedStaticMesh = LoadObject<UStaticMesh>(nullptr, *StaticMeshPath);
	if (LoadedStaticMesh)
	{
		MeshComponent->SetStaticMesh(LoadedStaticMesh);
	}
	MeshComponent->SetRelativeScale3D(FVector(0.5f,0.5f,0.5f));
}

// Called when the game starts or when spawned
void ABlock::BeginPlay()
{
	Super::BeginPlay();
}



