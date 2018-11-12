// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BMProjectile.h"
#include "BMCharacter.generated.h"

UCLASS()
class BOSSMODE_API ABMCharacter : public ACharacter
{
	GENERATED_BODY()

	// �� �޽�, �ڽŸ� �� �� ����
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		class USkeletalMeshComponent* FPMesh;

	// �� �޽�, �ڱ⸸ �� �� ����
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		class USkeletalMeshComponent* FPGunMesh;

	// 1��Ī ī�޶�
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* FPCameraComponent;


public:
	// ĳ������ �Ӽ� �⺻ �� ����
	ABMCharacter();

	// �⺻ ȸ�� �ӵ� (deg/sec)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseTurnRate;

	// �⺻ ��/�Ʒ� ���� �ӵ� (deg/sec)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseLookUpRate;

	// ������ ���۵ǰų� �����Ǿ��� �� ȣ��� 
	virtual void BeginPlay() override;

	// APawn �������̽�
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
	// APawn �������̽� ����

	virtual void Tick(float DeltaSeconds) override;

	// ����� �߻�ü Ŭ����
	UPROPERTY(EditDefaultsOnly, Category = Projectile)
		TSubclassOf<ABMProjectile> ProjectileClass;
	// �߻�ü ����
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Projectile)
		class USceneComponent* ProjSpawn;

protected:

	// ���� �� �Ĺ� �̵��� ó��
	void MoveForward(float Val);

	// �¿� ��Ʈ������ �̵� ó��
	void MoveRight(float Val);

	/**
	* input axis ������ ���� ȣ��ȴ�
	* @param Rate ����ȭ�� �ӵ��̸� 1.0�� �ִ� ȸ�� �ӵ��̴�
	*/
	void TurnAtRate(float Rate);

	/**
	* �� �Ʒ��� �־��� �ӵ��� ���� ���� �Է¿��� ȣ���Ѵ�
	* @param Rate ����ȭ�� �ӵ��̸� 1.0�� �ִ� ȸ�� �ӵ��̴�
	*/
	void LookUpAtRate(float Rate);

	/** �߻�ü �߻��ϱ� */
	void OnFire();

	void OnTrack();

protected:
	USceneComponent * TrackingSceneComponent;
};
