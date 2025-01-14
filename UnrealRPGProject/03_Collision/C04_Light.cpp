// Fill out your copyright notice in the Description page of Project Settings.


#include "C04_Light.h"
#include "Global.h"
#include "C03_Trigger.h"
#include "Components/TextRenderComponent.h"
#include "Components/PointLightComponent.h"


// Sets default values
AC04_Light::AC04_Light()
{
	CHelpers::CreateComponent<USceneComponent>(this, &Scene, "Scene");
	CHelpers::CreateComponent<UTextRenderComponent>(this, &Text, "Text", Scene);
	CHelpers::CreateComponent<UPointLightComponent>(this, &Light, "Light", Scene);
	CHelpers::CreateComponent<UPointLightComponent>(this, &Light2, "Light2", Scene);


	Text->SetRelativeLocation(FVector(0, 0, 100));
	Text->SetRelativeRotation(FRotator(0, 180, 0));
	Text->SetRelativeScale3D(FVector(2));
	Text->TextRenderColor = FColor::Red;
	Text->HorizontalAlignment = EHorizTextAligment::EHTA_Center;
	Text->Text = FText::FromString(GetName());

	// 언리얼에서는 10^4 = 10000
	// 1e-6f = 10^-6 = 0.000001

	Light->Intensity = 1e+4f;
	Light->AttenuationRadius = 200;
	Light->LightColor = FColor(255, 128, 50);

	Light2->SetRelativeLocation(FVector(0, 200, 0));
	Light2->Intensity = 1e+4f;
	Light2->AttenuationRadius = 200;
	Light2->LightColor = FColor(255, 128, 50);
}

// Called when the game starts or when spawned
void AC04_Light::BeginPlay()
{
	Super::BeginPlay();

	Light->SetVisibility(false);
	Light2->SetVisibility(false);

	// TArray: 가변형 배열
	// C++ STL의 Vector와 유사함
	TArray<AActor*> actors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AC03_Trigger::StaticClass(), actors); // 포인터를 얻어옴
	CheckFalse(actors.Num() > 0);

	AC03_Trigger* trigger = Cast<AC03_Trigger>(actors[0]);
	trigger->OnBoxLightBeginOverlap.BindUFunction(this, "OnLight");
	trigger->OnBoxLightEndOverlap.BindUFunction(this, "OffLight");

	trigger->OnBoxLightRandomBeginOverlap.BindUFunction(this, "OnRandomLight");
}

void AC04_Light::OnLight()
{
	Light->SetVisibility(true);
}

void AC04_Light::OffLight()
{
	Light->SetVisibility(false);
	Light2->SetVisibility(false);
}

FString AC04_Light::OnRandomLight(FLinearColor InColor)
{
	Light2->SetVisibility(true);
	Light2->SetLightColor(InColor);
	return InColor.ToString();
}


