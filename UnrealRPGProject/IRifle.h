// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IRifle.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UIRifle : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class UNREALRPGPROJECT_API IIRifle
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual class ACRifle* GetRifle() = 0;
	virtual void GetLocationAndDirection(FVector& OutStart, FVector& OutEnd, FVector& OutDirection) = 0;
	virtual void OnFocus() = 0;
	virtual void OffFocus() = 0;

};
