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
public: // 4.25 버전에서는 public: 안써주면 private:

// _Implementation 을 붙여줘야 쓸 수 있음
	FString GetNotifyName_Implementation() const; // 리턴형 함수
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration);
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation);
};
