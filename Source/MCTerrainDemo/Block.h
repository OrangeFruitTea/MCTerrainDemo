// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Block.generated.h"

UCLASS()
class MCTERRAINDEMO_API ABlock : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABlock();

protected:
	UPROPERTY(EditAnywhere, Category="Setup")
	UStaticMeshComponent* MeshComponent;
	// UPROPERTY(EditAnywhere, Category="Setup")
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

};
