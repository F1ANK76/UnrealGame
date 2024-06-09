// Fill out your copyright notice in the Description page of Project Settings.


#include "C03_Cube.h"
#include "Global.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AC03_Cube::AC03_Cube()
{
	CHelpers::CreateComponent<UStaticMeshComponent>(this, &Mesh, "Mesh");

	UStaticMesh* mesh;
	CHelpers::GetAsset<UStaticMesh>(&mesh, "StaticMesh'/Game/Meshs/M_Cube.M_Cube'");

	Mesh->SetStaticMesh(mesh);
	Mesh->SetSimulatePhysics(true);
	Mesh->SetCollisionObjectType(ECollisionChannel::ECC_PhysicsBody);
}

// Called when the game starts or when spawned
void AC03_Cube::BeginPlay()
{
	Super::BeginPlay();
	
}

