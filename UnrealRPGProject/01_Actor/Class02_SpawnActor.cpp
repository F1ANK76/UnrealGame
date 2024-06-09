// Fill out your copyright notice in the Description page of Project Settings.


#include "Class02_SpawnActor.h"
#include "Global.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInstanceConstant.h"
#include "Materials/MaterialInstanceDynamic.h"

// Sets default values
AClass02_SpawnActor::AClass02_SpawnActor()
{
 	// �ڷ��� ���ø� ���ø� �̸�
	// �Ϲ������� �������ϰ� ��ġ���ָ� ���ϴ�.
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	// �޽��� ��Ʈ�� ���
	RootComponent = Mesh;

	// �޽��� ���۷��� ��ġ�� �����;� ��
	// �޽��⺻�ڷ���/����������/�޽�����/ť��.�ĺ���
	// StaticMesh'/Game/Meshs/M_Cube.M_Cube'

	// �����ڸ� ����� Ŭ������ ��Ƶδ� ��::������Ʈã����
	//<�ڷ���ã��>
	
	//TEXT() �����ڵ� ���
	//L ��Ƽ����Ʈ ����1 �ѱ�2 ����� ����
	//ConstructorHelpers::FObjectFinder<UStaticMesh> mesh(L"StaticMesh'/Game/Meshs/M_Cube.M_Cube'");

	//// �⺻���� �޽� �ֱ�
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
	//c++ ������ MaterialInstance�� UMaterialInstanceConstant�� ǥ��
	//�����ε��� �ؾߵǱ� ������ ����Ŭ���� ���Ұ�
	//�����ڰ� �ƴѰ����� �����ε��Լ��� StaticLoadObject ���
	//UObject�� �ֻ��� �ڷ����̹Ƿ� ����� �ڷ����� ĳ�����ؼ� ����ϸ�ȴ�.

	// ����
	//UObject* obj = StaticLoadObject(UMaterialInstanceConstant::StaticClass(), NULL, L"MaterialInstanceConstant'/Game/Meterial/M_Mesh_Inst.M_Mesh_Inst'");
	//UMaterialInstanceConstant* material = Cast<UMaterialInstanceConstant>(obj); // ĳ���� �����ϸ� NULL ��ȯ

	// ����Ŭ������ ����غ���
	UMaterialInstanceConstant* material; // �𸮾󿡼��� ������ ���������� �ڵ� �ʱ�ȭ���ش�. NULL
	CHelpers::GetAssetDynamic<UMaterialInstanceConstant>(&material, "MaterialInstanceConstant'/Game/Meterial/M_Mesh_Inst.M_Mesh_Inst'");

	// UMaterialInstanceDynamic::Create�� �̿��ؼ� ���̳��� ���͸����� ����
	// Material ��ü�� UMaterialInterface�κ��� ��ӹ޾� �����Ǿ�����.
	Material = UMaterialInstanceDynamic::Create(material, this);
	Mesh->SetMaterial(0, Material);

	// this�� �������Ʈ�� self�� ����.
	UKismetSystemLibrary::K2_SetTimer(this, "ChangeColor", 1.0f, true);
}

void AClass02_SpawnActor::ChangeColor()
{
	FLinearColor color;
	
	color.R = UKismetMathLibrary::RandomFloatInRange(0, 1);
	color.G = UKismetMathLibrary::RandomFloatInRange(0, 1);
	color.B = UKismetMathLibrary::RandomFloatInRange(0, 1);
	color.A = 1.0f;

	// ���͸��� ���鶧 �̸��� Color��� ����κ� �ٲٱ�
	Material->SetVectorParameterValue("Color", color);
}

