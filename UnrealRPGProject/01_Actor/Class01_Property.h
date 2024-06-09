// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Class01_Property.generated.h"

UCLASS()
class UNREALRPGPROJECT_API AClass01_Property : public AActor
{
	GENERATED_BODY()

private:
	// 모든값을 사용 가능
	UPROPERTY(EditAnywhere)
		int A = 10;
	// 배치된 애들만 사용 가능
	UPROPERTY(EditInstanceOnly)
		int B = 20;
	// 기본값만 설정할 수 있음
	UPROPERTY(EditDefaultsOnly)
		int C = 30;

protected:
	// 수정은 불가능한데 값 확인하고 싶을때
	// 블루프린트에서 접근 가능
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
		int Test = 50;




public:	
	// Sets default values for this actor's properties
	AClass01_Property();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	


};
