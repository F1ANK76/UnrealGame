// Fill out your copyright notice in the Description page of Project Settings.


#include "C01_Log.h"
#include "Global.h"

// Sets default values
AC01_Log::AC01_Log()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AC01_Log::BeginPlay()
{
	Super::BeginPlay();

	CLog::Print(10);
	CLog::Print(20, 1);
	// ���� ���̵�� 30�� ������ ��������.
	CLog::Print(30, 2, 20.0f);
	CLog::Print(40, 2, 20.0f);

	CLog::Print("Unreal Gameplay");
	CLog::Print(GetActorLocation());
	CLog::Print(GetActorRotation());

	CLog::Log(10);
	CLog::Log(PI);
	CLog::Log("Unreal Log Gameplay !!!");
	CLog::Log(GetActorLocation());
	CLog::Log(GetActorRotation());


	CLog::Log(this);
	// �������Ҷ� �ش� ��ũ�ΰ� �ҼӵǾ��ִ� ������ ��Ÿ����
	PrintLine();
}

// Called every frame
void AC01_Log::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Time += DeltaTime;
	CLog::Print(Time, 3);
}

