// Fill out your copyright notice in the Description page of Project Settings.

#include "BMProjectile.h"

#include "BMBossCharacter.h"

#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GameFramework/DamageType.h"

// Sets default values
ABMProjectile::ABMProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// ��ü�� ������ �浹 ǥ������ ����Ѵ�
	ProjCollision = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));

	ProjCollision->InitSphereRadius(10.0f);
	ProjCollision->BodyInstance.SetCollisionProfileName("BlockAll");
	ProjCollision->OnComponentHit.AddDynamic(this, &ABMProjectile::OnHit);

	OnDestroyed.AddDynamic(this, &ABMProjectile::OnDestoyedProjectile);

	ProjCollision->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	ProjCollision->CanCharacterStepUpOn = ECB_No;
	RootComponent = ProjCollision;

	ProjMesh = CreateDefaultSubobject <UStaticMeshComponent>(TEXT("MeshComp"));

	ProjMesh->AttachTo(ProjCollision);
	ProjMesh->SetCollisionProfileName(TEXT("NoCollision"));

	ProjParticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleComp"));

	ProjParticle->bAutoActivate = false;
	ProjParticle->AttachTo(ProjCollision);

	// �߻�ü�� �̵��� �����ϱ� ���� ProjectileMovementComponent ���
	ProjMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjMovement->UpdatedComponent = ProjCollision;
	ProjMovement->InitialSpeed = 3000.f;
	ProjMovement->MaxSpeed = 3000.f;
	ProjMovement->bRotationFollowsVelocity = true;

	ProjMovement->bIsHomingProjectile = true;
	ProjMovement->HomingAccelerationMagnitude = 10000.0f;

	// �⺻������ 3�� �ڿ� �״´�
	InitialLifeSpan = 3.0f;
}

// Called when the game starts or when spawned
void ABMProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABMProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABMProjectile::OnHit(class UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor->GetClass()->IsChildOf(ABMBossCharacter::StaticClass()))
	{
		FDamageEvent DamageEvent(UDamageType::StaticClass());
		OtherActor->TakeDamage(10.0f, DamageEvent, GetWorld()->GetFirstPlayerController(), this);
	}

	if (!OtherActor->GetClass()->IsChildOf(this->StaticClass()))
	{
		ProjCollision->SetCollisionProfileName(TEXT("NoCollision"));
		ProjCollision->bGenerateOverlapEvents = false;
		ProjMesh->SetVisibility(false);

		ProjParticle->Activate();
		ProjParticle->DetachFromParent(true);
	}
}

void ABMProjectile::OnDestoyedProjectile(AActor* DestroyingActor)
{

}