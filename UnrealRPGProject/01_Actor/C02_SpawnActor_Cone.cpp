// Fill out your copyright notice in the Description page of Project Settings.


#include "C02_SpawnActor_Cone.h"
#include "Global.h"

AC02_SpawnActor_Cone::AC02_SpawnActor_Cone() 
{
	UStaticMesh* mesh;
	CHelpers::GetAsset<UStaticMesh>(&mesh, "StaticMesh'/Game/Meshs/M_Cone.M_Cone'");
	Mesh->SetStaticMesh(mesh);
}
