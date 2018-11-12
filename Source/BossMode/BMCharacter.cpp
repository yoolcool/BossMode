// Fill out your copyright notice in the Description page of Project Settings.

#include "BMCharacter.h"

#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
ABMCharacter::ABMCharacter()
{
	// �� ĳ���Ͱ� Tick()�� �� �����Ӹ��� �θ����� �Ѵ�. �ʿ���ٸ� ���� ����� ���� �� ���� �ִ�.
	PrimaryActorTick.bCanEverTick = true;

	// �ݸ��� ĸ�� ũ�� ����
	GetCapsuleComponent()->InitCapsuleSize(42.0f, 96.0f);

	// ĳ���� ȸ�� �ӵ� ����
	BaseTurnRate = 45.0f;
	BaseLookUpRate = 45.0f;

	// CameraComponent ���� 
	FPCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	//FPCameraComponent->AttachParent = GetCapsuleComponent();
	FPCameraComponent->SetupAttachment(GetCapsuleComponent());

	// ī�޶� ��ġ ����
	FPCameraComponent->RelativeLocation = FVector(0, 0, 64.f);
	FPCameraComponent->bUsePawnControlRotation = true;

	// �����ϴ� �������� �� �� �ִ� �޽� ����
	FPMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));

	FPMesh->SetOnlyOwnerSee(true);
	//FPMesh->AttachParent = FPCameraComponent;
	FPMesh->AttachTo(FPCameraComponent);
	FPMesh->bCastDynamicShadow = false;
	FPMesh->CastShadow = false;
	
	FPGunMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FP_Gun"));
	FPGunMesh->SetOnlyOwnerSee(true);// �������� �÷��̾ �޽ø� �� ���̴�
	FPGunMesh->bCastDynamicShadow = false;
	FPGunMesh->CastShadow = false;
	FPGunMesh->AttachTo(FPMesh, TEXT("GripPoint"), EAttachLocation::SnapToTargetIncludingScale, true);

	ProjSpawn = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileSpawn"));
	ProjSpawn->AttachTo(FPGunMesh);
}

// Called when the game starts or when spawned
void ABMCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABMCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABMCharacter::SetupPlayerInputComponent(UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

	check(InputComponent);
	InputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	InputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	InputComponent->BindAxis("MoveForward", this, &ABMCharacter::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &ABMCharacter::MoveRight);

	InputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	InputComponent->BindAxis("TurnRate", this, &ABMCharacter::TurnAtRate);
	InputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	InputComponent->BindAxis("LookUpRate", this, &ABMCharacter::LookUpAtRate);
	
	InputComponent->BindAction("Fire", IE_Pressed, this, &ABMCharacter::OnFire);

	InputComponent->BindAction("Track", IE_Pressed, this, &ABMCharacter::OnTrack);
} // <-- SetupPlayerInputComponent() �ݱ�

void ABMCharacter::MoveForward(float Val)
{
	if (Val != 0.0f) {
		// �ش� ��ġ�� �̵� �߰�
		AddMovementInput(GetActorForwardVector(), Val);
	}
}

void ABMCharacter::MoveRight(float Val)
{
	if (Val != 0.0f)
	{
		// �ش� ��ġ�� �̵� �߰�
		AddMovementInput(GetActorRightVector(), Val);
	}
}

void ABMCharacter::TurnAtRate(float Rate)
{
	// �ӵ� �������� �� �������� ��Ÿ�� ����Ѵ�.
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void ABMCharacter::LookUpAtRate(float Rate)
{
	// �ӵ� �������� �� �������� ��Ÿ�� ����Ѵ�.
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void ABMCharacter::OnFire()
{
	// �߻�ü �߻� �õ�
	if (ProjectileClass != nullptr)
	{
		if (GetWorld() != nullptr)
		{
			ABMProjectile* ThisProjectile = GetWorld()->SpawnActor<ABMProjectile>(ProjectileClass, ProjSpawn->GetComponentLocation(), GetControlRotation());
			ThisProjectile->GetProjectileMovement()->HomingTargetComponent = TrackingSceneComponent;
		}
	}
}

void ABMCharacter::OnTrack()
{
	FVector MousePos;
	FVector MouseDir;
	FHitResult Hit;
	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(ECC_GameTraceChannel2);
	APlayerController* playerController = Cast<APlayerController>(GetController());
	
	if (GEngine->GameViewport != nullptr && playerController != nullptr)
	{
		FVector2D ScreenPos = GEngine->GameViewport->Viewport->GetSizeXY();
		playerController->DeprojectScreenPositionToWorld(ScreenPos.X / 2.0f, ScreenPos.Y / 2.0f, MousePos, MouseDir);
		MouseDir *= 100000.0f;

		GetWorld()->LineTraceSingleByObjectType(Hit, MousePos, MouseDir, ObjectQueryParams);

		if (Hit.bBlockingHit)
		{
			UE_LOG(LogTemp, Warning, TEXT("TRACE HIT WITH %s"), *(Hit.GetActor()->GetName()));
			TrackingSceneComponent = Cast<USceneComponent>(Hit.GetActor()->GetComponentByClass(USceneComponent::StaticClass()));
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("No Trace"));
			TrackingSceneComponent = nullptr;
		}
	}// <--If(GEngine->GameViewport != nullptr...) �ݱ�
}// <--OnTrack() �ݱ�