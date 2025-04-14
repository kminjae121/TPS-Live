// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/TPSEnemyAnimInstance.h"

#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Enemy/TPSEnemy.h"

UTPSEnemyAnimInstance::UTPSEnemyAnimInstance()
{
	static ConstructorHelpers::FObjectFinder<UAnimMontage> HitMontageRef
	(TEXT("/Script/Engine.AnimMontage'/Game/Animation/Am_EnemyHit.Am_EnemyHit'"));

	if (HitMontageRef.Succeeded())
	{
		HitMontage = HitMontageRef.Object;
	}
}

void UTPSEnemyAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	Character = Cast<ATPSEnemy>(TryGetPawnOwner());

	if (Character)
	{
		MovementComponent = Character->GetCharacterMovement();
	}
}

void UTPSEnemyAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (Character == nullptr)

		if (MovementComponent == nullptr)
			return;

	Velocity = MovementComponent->Velocity;

	bShouldMove = (Velocity.Size2D() > 3.0f && MovementComponent->GetCurrentAcceleration()
		!= FVector::ZeroVector);

}

void UTPSEnemyAnimInstance::PlayHitMontage()
{
	int32 RandomIndex = FMath::RandRange(1, 2);
	FString SelctionName = FString::Printf(TEXT("Hit%d"), RandomIndex);

	Montage_Play(HitMontage);
	Montage_JumpToSection(*SelctionName);
}

void UTPSEnemyAnimInstance::PlayDeadMontage()
{
	FString SectionName = TEXT("Dead");
	Montage_Play(HitMontage);
	Montage_JumpToSection(*SectionName);
}
