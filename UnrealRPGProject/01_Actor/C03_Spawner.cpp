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
	
	// 언리얼에서는 int32 사용하게된다.
	// int 4바이트 4*8 = 32
	// 언리얼은 pc용 게임으로만 제작되는것이 아니기 때문에 멀티 플랫폼을 지원하기에 자료형 크기를 변환할 수 있게 사용 플랫폼마다 int 크기가 다를 수 있다.

	for (int32 i = 0; i < 3; i++)
	{
		FTransform transform;
		FVector location = GetActorLocation();
		transform.SetLocation(FVector(location.X + i * 400, location.Y, location.Z));
		SpawnActors[i] = GetWorld()->SpawnActor<AClass02_SpawnActor>(SpawnClass[i], transform);
	}
}

