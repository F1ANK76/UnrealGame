// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C01_ActorBeginOverlap.generated.h"

UCLASS()
class UNREALRPGPROJECT_API AC01_ActorBeginOverlap : public AActor
{
	GENERATED_BODY()
private:
	UPROPERTY(VisibleDefaultsOnly)
		class USceneComponent* Scene;
	UPROPERTY(VisibleDefaultsOnly)
		class UBoxComponent* Box;
	UPROPERTY(VisibleDefaultsOnly)
		class UTextRenderComponent* Text;


public:	
	// Sets default values for this actor's properties
	AC01_ActorBeginOverlap();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	// 에디터랑 블루프린트랑 통신
	UFUNCTION()
	void ActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor);
	UFUNCTION()
	void ActorEndOverlap(AActor* OverlappedActor, AActor* OtherActor);
};
