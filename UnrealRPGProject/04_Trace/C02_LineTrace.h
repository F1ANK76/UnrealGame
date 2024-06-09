// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C02_LineTrace.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FTraceResult, class AActor*, InActor, FLinearColor, InColor);
UCLASS()
class UNREALRPGPROJECT_API AC02_LineTrace : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleDefaultsOnly)
		class USceneComponent* Scene;

	UPROPERTY(VisibleDefaultsOnly)
		class UTextRenderComponent* Text;
	
public:	
	// Sets default values for this actor's properties
	AC02_LineTrace();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	TArray<class AC01_Cylinder*> Cylinders;
private:
	UFUNCTION()
	void StartJump(class AActor* InActor, FLinearColor InColor);
protected:
	UFUNCTION(BlueprintCallable)
	void RestoreColor(class ACPlayer* InPlayer);
public:
	UPROPERTY(BlueprintAssignable)
	FTraceResult OnTraceResult;
};
