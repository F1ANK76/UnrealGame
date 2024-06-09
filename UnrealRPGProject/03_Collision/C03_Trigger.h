// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C03_Trigger.generated.h"

// ��������Ʈ : �̱� ��������Ʈ, ��Ƽĳ��Ʈ
// �̱� ��������Ʈ : �ϳ��� �Լ��� �ϳ��� ��������Ʈ
// ��Ƽĳ��Ʈ : �ϳ��� ��������Ʈ�� ������ �Լ��� ����

// ��������Ʈ ��ũ��
DECLARE_DELEGATE(FBoxLightBeginOverlap); // void _(void)
DECLARE_DELEGATE(FBoxLightEndOverlap);
DECLARE_DELEGATE_RetVal_OneParam(FString, FBoxLightRandomBeginOverlap, FLinearColor);

UCLASS()
class UNREALRPGPROJECT_API AC03_Trigger : public AActor
{
	GENERATED_BODY()
private:
	UPROPERTY(VisibleDefaultsOnly)
		class USceneComponent* Scene;
	UPROPERTY(VisibleDefaultsOnly)
		class UBoxComponent* Box;
	UPROPERTY(VisibleDefaultsOnly)
		class UTextRenderComponent* Text;
	UPROPERTY(VisibleDefaultsOnly)
		class UPointLightComponent* PointLight;

public:	
	// Sets default values for this actor's properties
	AC03_Trigger();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UFUNCTION()
		void ActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor);
	UFUNCTION()
		void ActorEndOverlap(AActor* OverlappedActor, AActor* OtherActor);

public:
	// �̸��� ���� �ƹ��ų� �������
	// ���ҷ��� F -> On���� �ٲ��ش�.
	FBoxLightBeginOverlap OnBoxLightBeginOverlap;
	FBoxLightEndOverlap OnBoxLightEndOverlap;
	FBoxLightRandomBeginOverlap OnBoxLightRandomBeginOverlap;
};