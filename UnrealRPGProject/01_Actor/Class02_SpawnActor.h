// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Class02_SpawnActor.generated.h"

UCLASS()
class UNREALRPGPROJECT_API AClass02_SpawnActor : public AActor
{
	GENERATED_BODY()

protected:
	//ÄÄÆ÷³ÍÆ®
	UPROPERTY(VisibleDefaultsOnly)
		class UStaticMeshComponent* Mesh;

public:	
	// Sets default values for this actor's properties
	AClass02_SpawnActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
private:
	UFUNCTION()
	void ChangeColor();

private:
	class UMaterialInstanceDynamic* Material;


};
