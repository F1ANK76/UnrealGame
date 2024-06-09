// Fill out your copyright notice in the Description page of Project Settings.


#include "C03_Spawner.h"
#include "Global.h"
#include "Class02_SpawnActor.h"

// Sets default values
AC03_Spawner::AC03_Spawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AC03_Spawner::BeginPlay()
{
	Super::BeginPlay();
	
	// �𸮾󿡼��� int32 ����ϰԵȴ�.
	// int 4����Ʈ 4*8 = 32
	// �𸮾��� pc�� �������θ� ���۵Ǵ°��� �ƴϱ� ������ ��Ƽ �÷����� �����ϱ⿡ �ڷ��� ũ�⸦ ��ȯ�� �� �ְ� ��� �÷������� int ũ�Ⱑ �ٸ� �� �ִ�.

	for (int32 i = 0; i < 3; i++)
	{
		FTransform transform;
		FVector location = GetActorLocation();
		transform.SetLocation(FVector(location.X + i * 400, location.Y, location.Z));
		SpawnActors[i] = GetWorld()->SpawnActor<AClass02_SpawnActor>(SpawnClass[i], transform);
	}
}

