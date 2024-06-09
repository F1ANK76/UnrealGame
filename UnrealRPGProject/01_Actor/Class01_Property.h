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
	// ��簪�� ��� ����
	UPROPERTY(EditAnywhere)
		int A = 10;
	// ��ġ�� �ֵ鸸 ��� ����
	UPROPERTY(EditInstanceOnly)
		int B = 20;
	// �⺻���� ������ �� ����
	UPROPERTY(EditDefaultsOnly)
		int C = 30;

protected:
	// ������ �Ұ����ѵ� �� Ȯ���ϰ� ������
	// �������Ʈ���� ���� ����
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
