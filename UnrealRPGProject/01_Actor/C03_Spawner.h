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
	// TSubClassOf 해당 자료형 전방선언
	// 리플렉션
	// 자료형의 타입을 변수로 다룰 수 있도록 해주는 기능
	// 스폰액터 상속받은 클래스만 사용할 수 있게 제한

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<class AClass02_SpawnActor> SpawnClass[3];

		//UClass* SpawnClass;
		//UClass는 언리얼 모든클래스 가능

	
public:	
	// Sets default values for this actor's properties
	AC03_Spawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	//전방선언
	class AClass02_SpawnActor* SpawnActors[3];

};
