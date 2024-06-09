// Fill out your copyright notice in the Description page of Project Settings.


#include "Class02_SpawnActor.h"
#include "Global.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInstanceConstant.h"
#include "Materials/MaterialInstanceDynamic.h"

// Sets default values
AClass02_SpawnActor::AClass02_SpawnActor()
{
 	// 자료형 템플릿 템플릿 이름
	// 일반적으로 변수명하고 일치해주면 편하다.
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	// 메쉬를 루트로 사용
	RootComponent = Mesh;

	// 메쉬의 레퍼런스 위치를 가져와야 함
	// 메쉬기본자료형/컨텐츠폴더/메쉬폴더/큐브.식별자
	// StaticMesh'/Game/Meshs/M_Cube.M_Cube'

	// 생성자를 도움될 클래스를 모아두는 곳::오브젝트찾아줌
	//<자료형찾기>
	
	//TEXT() 유니코드 방식
	//L 멀티바이트 영문1 한글2 방식이 존재
	//ConstructorHelpers::FObjectFinder<UStaticMesh> mesh(L"StaticMesh'/Game/Meshs/M_Cube.M_Cube'");

	//// 기본으로 메쉬 넣기
	//if (mesh.Succeeded())
	//	Mesh->SetStaticMesh(mesh.Object);

	UStaticMesh* mesh;
	CHelpers::GetAsset<UStaticMesh>(&mesh, "StaticMesh'/Game/Meshs/M_Cube.M_Cube'");
	Mesh->SetStaticMesh(mesh);

}

// Called when the game starts or when spawned
void AClass02_SpawnActor::BeginPlay()
{
	Super::BeginPlay();

	//MaterialInstanceConstant'/Game/Meterial/M_Mesh_Inst.M_Mesh_Inst'
	//c++ 에서는 MaterialInstance가 UMaterialInstanceConstant로 표현
	//동적로딩을 해야되기 때문에 헬퍼클래스 사용불가
	//생성자가 아닌곳에서 동적로딩함수는 StaticLoadObject 사용
	//UObject는 최상위 자료형이므로 사용할 자료형을 캐스팅해서 사용하면된다.

	// 정석
	//UObject* obj = StaticLoadObject(UMaterialInstanceConstant::StaticClass(), NULL, L"MaterialInstanceConstant'/Game/Meterial/M_Mesh_Inst.M_Mesh_Inst'");
	//UMaterialInstanceConstant* material = Cast<UMaterialInstanceConstant>(obj); // 캐스팅 실패하면 NULL 반환

	// 헬퍼클래스로 사용해보기
	UMaterialInstanceConstant* material; // 언리얼에서는 포인터 선언했을때 자동 초기화해준다. NULL
	CHelpers::GetAssetDynamic<UMaterialInstanceConstant>(&material, "MaterialInstanceConstant'/Game/Meterial/M_Mesh_Inst.M_Mesh_Inst'");

	// UMaterialInstanceDynamic::Create를 이용해서 다이나믹 머터리얼을 생성
	// Material 전체는 UMaterialInterface로부터 상속받아 구현되어진다.
	Material = UMaterialInstanceDynamic::Create(material, this);
	Mesh->SetMaterial(0, Material);

	// this는 블루프린트의 self와 같다.
	UKismetSystemLibrary::K2_SetTimer(this, "ChangeColor", 1.0f, true);
}

void AClass02_SpawnActor::ChangeColor()
{
	FLinearColor color;
	
	color.R = UKismetMathLibrary::RandomFloatInRange(0, 1);
	color.G = UKismetMathLibrary::RandomFloatInRange(0, 1);
	color.B = UKismetMathLibrary::RandomFloatInRange(0, 1);
	color.A = 1.0f;

	// 매터리얼 만들때 이름을 Color라고 만든부분 바꾸기
	Material->SetVectorParameterValue("Color", color);
}

