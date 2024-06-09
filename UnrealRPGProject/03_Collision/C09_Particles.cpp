// Fill out your copyright notice in the Description page of Project Settings.


#include "C09_Particles.h"
#include "Global.h"
#include "C08_EventTrigger.h"
#include "Components/TextRenderComponent.h"
#include "Particles/ParticleSystem.h"

// Sets default values
AC09_Particles::AC09_Particles()
{
	CHelpers::CreateComponent<USceneComponent>(this, &Scene, "Scene");
	CHelpers::CreateComponent<UTextRenderComponent>(this, &Text, "Text", Scene);

	Text->SetRelativeLocation(FVector(0, 0, 100));
	Text->SetRelativeRotation(FRotator(0, 180, 0));
	Text->SetRelativeScale3D(FVector(2));
	Text->TextRenderColor = FColor::Red;
	Text->HorizontalAlignment = EHorizTextAligment::EHTA_Center;
	Text->Text = FText::FromString(GetName());

	CHelpers::GetAsset<UParticleSystem>(&Particles[0], "ParticleSystem'/Game/InfinityBladeEffects/Effects/FX_Ambient/Fire/P_Fire_largeArea_Trans_mobile.P_Fire_largeArea_Trans_mobile'");
	CHelpers::GetAsset<UParticleSystem>(&Particles[1], "ParticleSystem'/Game/InfinityBladeEffects/Effects/FX_Ambient/Fire/P_Fire_TrapBossEnd_mobile.P_Fire_TrapBossEnd_mobile'");
	CHelpers::GetAsset<UParticleSystem>(&Particles[2], "ParticleSystem'/Game/InfinityBladeEffects/Effects/FX_Ambient/Fire/P_Fire_wallTorch_Trans_mobile.P_Fire_wallTorch_Trans_mobile'");
}

// Called when the game starts or when spawned
void AC09_Particles::BeginPlay()
{
	Super::BeginPlay();
	
	TArray<AC08_EventTrigger*> triggers;
	CHelpers::FindActors<AC08_EventTrigger>(GetWorld(), triggers);

	//// 싱글하고 다르게 AddUFunction
	triggers[0]->OnEventTrigger.AddUFunction(this, "PlayParticle");
}

void AC09_Particles::PlayParticle(int32 InIndex)
{
	FTransform transform;
	transform.SetLocation(GetActorLocation());

	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Particles[InIndex], transform);
}
