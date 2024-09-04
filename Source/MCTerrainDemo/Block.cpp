// Fill out your copyright notice in the Description page of Project Settings.


#include "Block.h"

// Sets default values
ABlock::ABlock()
{
	// 禁止每tick调用
	PrimaryActorTick.bCanEverTick = false;
	// 初始化staticMesh组件
	MeshComponent = NewObject<UStaticMeshComponent>(this, TEXT("Block"));
	this->SetRootComponent(MeshComponent);

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


