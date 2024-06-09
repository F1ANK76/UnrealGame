#pragma once
#include "CoreMinimal.h"
#include "UObject/ConstructorHelpers.h"

//�𸮾� ���ӽ����̽�
//��� ������Ʈ�� �Ҽӵ� �ҽ����� ����

class UNREALRPGPROJECT_API CHelpers
{
public:
	template<typename T> // �ڷ��� �̸��� �ٲ���
	static void GetAsset(T** OutObject, FString InPath)
	{
		ConstructorHelpers::FObjectFinder<T> asset(*InPath);
		// ������ ������ �����߿� ������ üũ
		// �����ͻ󿡼� ���
		// ���� ���� �Ҷ��� ������������
		verifyf(asset.Succeeded(), L"asset.Succeeded()");

		*OutObject = asset.Object;
	}

	template<typename T> // �ڷ��� �̸��� �ٲ���
	static void GetAssetDynamic(T** OutObject, FString InPath)
	{
		T* obj = Cast<T>(StaticLoadObject(T::StaticClass(), NULL, *InPath));
		// ������ ������ �����߿� ������ üũ
		// �����ͻ󿡼� ���
		// ���� ���� �Ҷ��� ������������
		//verifyf(obj.Succeeded(), L"obj.Succeeded()");

		// !! -> �𸮾󿡼��� obj != NULL ���� ǥ��
		verifyf(!!obj, L"!!obj");

		*OutObject = obj;
	}

	// CGameMode.cpp ���� ���
	template<typename T> // �⺻������ TSub Ŭ������ �������̴�.
	static void GetClass(TSubclassOf<T>* OutClass, FString InPath)
	{
		ConstructorHelpers::FClassFinder<T> asset(*InPath);
		verifyf(asset.Succeeded(), L"asset.Succeeded()");

		*OutClass = asset.Class;
	}

	template<typename T>
	static void CreateComponent(AActor* InActor, T** InComponent, FName InName, USceneComponent* InParent = NULL)
	{
		*InComponent = InActor->CreateDefaultSubobject<T>(InName);

		if (!!InParent)
		{
			(*InComponent)->SetupAttachment(InParent);

			return;
		}

		InActor->SetRootComponent((*InComponent));
	}

	template<typename T>
	static void CreateActorComponent(AActor* InActor, T** InComponent, FName InName)
	{
		*InComponent = InActor->CreateDefaultSubobject<T>(InName);


	}

	template<typename T>
	static void FindActors(class UWorld* InWorld, TArray<T*>& OutActors)
	{
		TArray<AActor*> actors;
		UGameplayStatics::GetAllActorsOfClass(InWorld, T::StaticClass(), actors);

		for (AActor* actor : actors)
		{
			OutActors.Add(Cast<T>(actor));
		}
	}
};
