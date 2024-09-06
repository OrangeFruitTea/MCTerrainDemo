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
	SetActorScale3D(FVector(0.1f, 0.1f, 0.1f));
	MeshComponent->SetRelativeScale3D(FVector(0.2f,0.2f,0.2f));
}

// Called when the game starts or when spawned
void ABlock::BeginPlay()
{
	Super::BeginPlay();
	FVector Scale = GetActorScale3D();
	DrawDebugString(GetWorld(), GetActorScale3D(), FString::Printf(TEXT("Scale: %f, %f, %f"), Scale.X, Scale.Y, Scale.Z), nullptr, FColor::Red, 10.f);
}

void ABlock::UpdateVisibility()
{
	FVector3d Location = GetActorLocation();
}


