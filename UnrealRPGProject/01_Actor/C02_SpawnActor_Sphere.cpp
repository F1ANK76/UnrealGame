// Fill out your copyright notice in the Description page of Project Settings.


#include "C02_SpawnActor_Sphere.h"
#include "Global.h"

AC02_SpawnActor_Sphere::AC02_SpawnActor_Sphere()
{
	UStaticMesh* mesh;
	CHelpers::GetAsset<UStaticMesh>(&mesh, "StaticMesh'/Game/Meshs/M_Sphere.M_Sphere'");
	Mesh->SetStaticMesh(mesh);
}
