// Fill out your copyright notice in the Description page of Project Settings.


#include "C07_SpotLight.h"
#include "Global.h"
#include "C05_MulticastTrigger.h"

#include "Components/TextRenderComponent.h"
#include "Components/SpotLightComponent.h"

// Sets default values
AC07_SpotLight::AC07_SpotLight()
{
	CHelpers::CreateComponent<USceneComponent>(this, &Scene, "Scene");
	CHelpers::CreateComponent<UTextRenderComponent>(this, &Text, "Text", Scene);

	Text->SetRelativeLocation(FVector(0, 0, 100));
	Text->SetRelativeRotation(FRotator(0, 180, 0));
	Text->SetRelativeScale3D(FVector(2));
	Text->TextRenderColor = FColor::Red;
	Text->HorizontalAlignment = EHorizTextAligment::EHTA_Center;
	Text->Text = FText::FromString(GetName());


	for (int32 i = 0; i < 3; i++)
	{
		FString str;
		str.Append("SpotLights_");
		str.Append(FString::FromInt(i + 1));

		CHelpers::CreateComponent<USpotLightComponent>(this, &SpotLights[i], FName(str), Scene);

		SpotLights[i]->SetRelativeLocation(FVector(0, i * 150, 0));
		SpotLights[i]->SetRelativeRotation(FRotator(-90, 0, 0));
		SpotLights[i]->Intensity = 1e+5f;
		SpotLights[i]->OuterConeAngle = 25.0f;
	}
}

// Called when the game starts or when spawned
void AC07_SpotLight::BeginPlay()
{
	Super::BeginPlay();

	TArray<AC05_MulticastTrigger*> triggers;
	CHelpers::FindActors<AC05_MulticastTrigger>(GetWorld(), triggers);

	//// 싱글하고 다르게 AddUFunction
	triggers[0]->OnMultiLightBeginOverlap.AddUFunction(this, "OnLightColor");
}

void AC07_SpotLight::OnLightColor(int32 InIndex, FLinearColor InColor)
{
	for (int32 i = 0; i < 3; i++)
	{
		SpotLights[i]->SetLightColor(FLinearColor(1, 1, 1));
	}

	SpotLights[InIndex]->SetLightColor(InColor);
}

