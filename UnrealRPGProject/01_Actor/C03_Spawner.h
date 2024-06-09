// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C03_Spawner.generated.h"

UCLASS()
class UNREALRPGPROJECT_API AC03_Spawner : public AActor
{
	GENERATED_BODY()

private:
	// TSubClassOf �ش� �ڷ��� ���漱��
	// ���÷���
	// �ڷ����� Ÿ���� ������ �ٷ� �� �ֵ��� ���ִ� ���
	// �������� ��ӹ��� Ŭ������ ����� �� �ְ� ����

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<class AClass02_SpawnActor> SpawnClass[3];

		//UClass* SpawnClass;
		//UClass�� �𸮾� ���Ŭ���� ����

	
public:	
	// Sets default values for this actor's properties
	AC03_Spawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	//���漱��
	class AClass02_SpawnActor* SpawnActors[3];

};
