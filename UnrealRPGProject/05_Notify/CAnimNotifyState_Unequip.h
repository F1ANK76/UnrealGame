// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "CAnimNotifyState_Unequip.generated.h"

/**
 * 
 */
UCLASS()
class UNREALRPGPROJECT_API UCAnimNotifyState_Unequip : public UAnimNotifyState
{
	GENERATED_BODY()
public: // 4.25 ���������� public: �Ƚ��ָ� private:

// _Implementation �� �ٿ���� �� �� ����
	FString GetNotifyName_Implementation() const; // ������ �Լ�
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration);
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation);
};
