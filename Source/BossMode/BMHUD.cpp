// Fill out your copyright notice in the Description page of Project Settings.

#include "BMHUD.h"

#include "ConstructorHelpers.h"
#include "Engine/Canvas.h"

ABMHUD::ABMHUD()
{
	// ũ�ν���� �ؽ��� ����
	static ConstructorHelpers::FObjectFinder<UTexture2D> CrosshiarTexObj(TEXT("/Game/FirstPerson/Textures/FirstPersonCrosshair"));
	CrosshairTex = CrosshiarTexObj.Object;
}

void ABMHUD::DrawHUD()
{
	Super::DrawHUD();
	// ĵ���� �߾��� ã�´� 
	const FVector2D Center(Canvas->ClipX * 0.5f, Canvas->ClipY * 0.5f);

	// ĵ������ �߾��� �ؽ��� �߽ɰ� ���ĵǵ��� �ؽ��� ũ���� �ݸ�ŭ ������ ����
	const FVector2D CrosshairDrawPosition((Center.X - (CrosshairTex->GetSurfaceWidth() * 0.5)), (Center.Y - (CrosshairTex->GetSurfaceHeight() * 0.5f)));

	// ũ�ν��� �׸���
	FCanvasTileItem TileItem(CrosshairDrawPosition, CrosshairTex->Resource, FLinearColor::White);
	TileItem.BlendMode = SE_BLEND_Translucent;
	Canvas->DrawItem(TileItem);
}