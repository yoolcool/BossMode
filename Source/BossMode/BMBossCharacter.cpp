// Fill out your copyright notice in the Description page of Project Settings.

#include "BMBossCharacter.h"

#include "GameFramework/PawnMovementComponent.h"

// �⺻ �� ����
ABMBossCharacter::ABMBossCharacter()
{
	// �� ĳ���Ͱ� Tick()�� �� �����Ӹ��� �θ����� �Ѵ�. �ʿ���ٸ� ���� ����� ���� �� ���� �ִ�.
	PrimaryActorTick.bCanEverTick = true;

	Health = 100.0f;

	GetMovementComponent()->NavAgentProps.AgentHeight = 320.0f;
	GetMovementComponent()->NavAgentProps.AgentRadius = 160.0f;
}

float ABMBossCharacter::TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
	Health -= Damage;
	return Damage;
}

const float ABMBossCharacter::GetHealth()
{
	return Health;
}