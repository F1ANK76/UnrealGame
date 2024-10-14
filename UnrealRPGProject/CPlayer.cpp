// Fill out your copyright notice in the Description page of Project Settings.


#include "CPlayer.h"
#include "Global.h"
#include "CRifle.h"
#include "CAnimInstance.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "Camera/CameraShake.h"
#include "Components/CapsuleComponent.h"
#include "Materials/MaterialInstanceConstant.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "06_Widget/CUserWidget_CrossHair.h"

// Sets default values
ACPlayer::ACPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	/*SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	SpringArm->SetupAttachment(GetCapsuleComponent());

	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(SpringArm);*/

	// 위 코드랑 같음
	CHelpers::CreateComponent<USpringArmComponent>(this, &SpringArm, "SpringArm", GetCapsuleComponent());
	CHelpers::CreateComponent<UCameraComponent>(this, &Camera, "Camera", SpringArm);

	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->MaxWalkSpeed = 400.0f;

	// 메쉬 캐릭터 세팅
	USkeletalMesh* mesh;
	CHelpers::GetAsset<USkeletalMesh>(&mesh, "SkeletalMesh'/Game/Chracter/Mesh/SK_Mannequin.SK_Mannequin'");
	GetMesh()->SetSkeletalMesh(mesh);
	GetMesh()->SetRelativeLocation(FVector(0, 0, -90));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));
	
	// AnimBlueprint'/Game/ABP_Cplayer.ABP_Cplayer_C'
	// 애니메이션
	TSubclassOf<UAnimInstance> animInstance;
	CHelpers::GetClass<UAnimInstance>(&animInstance, "AnimBlueprint'/Game/ABP_Cplayer.ABP_Cplayer_C'");
	GetMesh()->SetAnimInstanceClass(animInstance);


	// 카메라 위치세팅
	SpringArm->SetRelativeLocation(FVector(0, 0, 60));
	SpringArm->TargetArmLength = 200.0f;
	SpringArm->bDoCollisionTest = false;
	SpringArm->bUsePawnControlRotation = true;
	SpringArm->SocketOffset = FVector(0, 60, 0);

	CHelpers::GetClass<UCUserWidget_CrossHair>(&CrossHairClass, "WidgetBlueprint'/Game/Widgets/WB_CrossHair.WB_CrossHair_C'"); // 블루프린트니까 _C 끝에 추가

	// 이미 있는 블루프린트클래스면 가져다 쓰는게 효율적이다.
	CHelpers::GetClass<UCameraShake>(&CameraShakeClass, "Blueprint'/Game/BP_CameraShake.BP_CameraShake_C'");
}

// 탄착부 형성 관련
void ACPlayer::GetLocationAndDirection(FVector& OutStart, FVector& OutEnd, FVector& OutDirection)
{
	OutDirection = Camera->GetForwardVector();

	FTransform transform = Camera->GetComponentToWorld();
	FVector cameraLocation = transform.GetLocation();
	OutStart = cameraLocation + OutDirection;

	// 반동 관련 로직
	FVector conDirection = UKismetMathLibrary::RandomUnitVectorInEllipticalConeInDegrees(OutDirection, 0.2f, 0.3f);
	conDirection *= 3000.0f;

	OutEnd = cameraLocation + conDirection;
}

// Called when the game starts or when spawned
void ACPlayer::BeginPlay()
{
	Super::BeginPlay();
	
	UMaterialInstanceConstant* bodyMaterial;
	CHelpers::GetAssetDynamic<UMaterialInstanceConstant>(&bodyMaterial, "MaterialInstanceConstant'/Game/Meterial/M_UE4Man_Body_Inst.M_UE4Man_Body_Inst'");

	UMaterialInstanceConstant* logoMaterial;
	CHelpers::GetAssetDynamic<UMaterialInstanceConstant>(&logoMaterial, "MaterialInstanceConstant'/Game/Meterial/M_UE4Man_ChestLogo_Inst.M_UE4Man_ChestLogo_Inst'");

	BodyMaterial = UMaterialInstanceDynamic::Create(bodyMaterial, this);
	LogoMaterial = UMaterialInstanceDynamic::Create(logoMaterial, this);

	// 캐릭터 외형 바꾸는 역할
	GetMesh()->SetMaterial(0, BodyMaterial);
	GetMesh()->SetMaterial(1, LogoMaterial);

	CrossHair = CreateWidget<UCUserWidget_CrossHair, APlayerController>(GetController<APlayerController>(), CrossHairClass);
	CrossHair->AddToViewport();
	CrossHair->SetVisibility(ESlateVisibility::Hidden);

	// 총생성
	Rifle = ACRifle::Spawn(GetWorld(), this);
	OnRifle(); // 총기를 잡고 시작
}

// Called every frame
void ACPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//함수 포인터를 사용할때는 함수의 주소로 명시해준다.
	PlayerInputComponent->BindAxis("MoveForward", this, &ACPlayer::OnMoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ACPlayer::OnMoveRight);
	PlayerInputComponent->BindAxis("HorizontalLook", this, &ACPlayer::OnHorizontalLook);
	PlayerInputComponent->BindAxis("VerticalLook", this, &ACPlayer::OnVerticalLook);

	//키액션
	PlayerInputComponent->BindAction("Running", EInputEvent::IE_Pressed, this, &ACPlayer::OnRunning);
	PlayerInputComponent->BindAction("Running", EInputEvent::IE_Released, this, &ACPlayer::OffRunning);

	// Rifle Input
	PlayerInputComponent->BindAction("Rifle", EInputEvent::IE_Pressed, this, &ACPlayer::OnRifle);

	// Aim
	PlayerInputComponent->BindAction("Aim", EInputEvent::IE_Pressed, this, &ACPlayer::OnAim);
	PlayerInputComponent->BindAction("Aim", EInputEvent::IE_Released, this, &ACPlayer::OffAim);

	// Fire
	PlayerInputComponent->BindAction("Fire", EInputEvent::IE_Pressed, this, &ACPlayer::OnFire);
	PlayerInputComponent->BindAction("Fire", EInputEvent::IE_Released, this, &ACPlayer::OffFire);
}

void ACPlayer::OnFocus()
{
	CrossHair->OnFocus();
}

void ACPlayer::OffFocus()
{
	CrossHair->OffFocus();
}

void ACPlayer::PlayCameraShake()
{
	GetController<APlayerController>()->PlayerCameraManager->PlayCameraShake(CameraShakeClass);
}
 
void ACPlayer::OnMoveForward(float Axis)
{
	FRotator rotator = FRotator(0, GetControlRotation().Yaw, 0);
	// 오차를 줄이기 위한 사원수 Quaternion 사용, 짐벌락같은축이 없어지는걸 막거나 회전의 오차를 줄여준다.
	FVector direction = FQuat(rotator).GetForwardVector().GetUnsafeNormal2D();

	AddMovementInput(direction, Axis);
}

void ACPlayer::OnMoveRight(float Axis)
{
	FRotator rotator = FRotator(0, GetControlRotation().Yaw, 0);
	// 오차를 줄이기 위한 사원수 Quaternion 사용, 짐벌락같은축이 없어지는걸 막거나 회전의 오차를 줄여준다.
	FVector direction = FQuat(rotator).GetRightVector().GetUnsafeNormal2D();

	AddMovementInput(direction, Axis);
}

void ACPlayer::OnHorizontalLook(float Axis)
{
	AddControllerYawInput(Axis);
}

void ACPlayer::OnVerticalLook(float Axis)
{
	AddControllerPitchInput(Axis);
}

void ACPlayer::OnRunning()
{
	GetCharacterMovement()->MaxWalkSpeed = 600;
}

void ACPlayer::OffRunning()
{
	GetCharacterMovement()->MaxWalkSpeed = 400;
}

void ACPlayer::OnRifle()
{
	if (Rifle->GetEquipped())
	{
		Rifle->Unequip();
		return;
	}

	Rifle->Equip();
}

void ACPlayer::OnAim()
{
	// 라이플 장착 상태 체크 관련
	CheckFalse(Rifle->GetEquipped());
	CheckTrue(Rifle->GetEquipping());

	bUseControllerRotationYaw = true;
	GetCharacterMovement()->bOrientRotationToMovement = false;

	// 카메라 위치 설정
	SpringArm->TargetArmLength = 100;
	SpringArm->SocketOffset = FVector(0, 30, 10);

	// 화면 확대 느낌
	//Camera->FieldOfView = 40;
	
	// 위 주석 코드와 같은 기능
	OnZoomIn();

	Rifle->Begin_Aiming();
	CrossHair->SetVisibility(ESlateVisibility::Visible);
}

void ACPlayer::OffAim()
{
	CheckFalse(Rifle->GetEquipped());
	CheckTrue(Rifle->GetEquipping());

	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	SpringArm->TargetArmLength = 200;
	SpringArm->SocketOffset = FVector(0, 60, 0);

	// 화면 축소 느낌
	//Camera->FieldOfView = 90;

	// 위 주석 코드와 같은 기능
	OnZoomOut();

	Rifle->End_Aiming();
	CrossHair->SetVisibility(ESlateVisibility::Hidden);
}

void ACPlayer::OnFire()
{
	Rifle->Begin_Fire();
}

void ACPlayer::OffFire()
{
	Rifle->End_Fire();
}

void ACPlayer::ChangeColor(FLinearColor InColor)
{
	BodyMaterial->SetVectorParameterValue("BodyColor", InColor);
	LogoMaterial->SetVectorParameterValue("BodyColor", InColor);
}

