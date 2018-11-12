// Fill out your copyright notice in the Description page of Project Settings.

#include "BossModeGameMode.h"

#include "BMHUD.h"

#include "ConstructorHelpers.h"

ABossModeGameMode::ABossModeGameMode() : Super()
{
	// �������Ʈ ĳ���͸� �⺻ �� �÷����� �����ϱ�
	static ConstructorHelpers::FClassFinder<APawn>PlayerPawnClassFinder(TEXT("/Game/Blueprint/FPCharacter"));

	DefaultPawnClass = PlayerPawnClassFinder.Class;
	HUDClass = ABMHUD::StaticClass();
}


