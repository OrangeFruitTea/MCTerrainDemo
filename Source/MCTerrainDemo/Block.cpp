// Fill out your copyright notice in the Description page of Project Settings.


#include "Block.h"

// Sets default values
ABlock::ABlock()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void ABlock::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABlock::UpdateVisibility()
{
	FVector3d Location = GetActorLocation();
}


