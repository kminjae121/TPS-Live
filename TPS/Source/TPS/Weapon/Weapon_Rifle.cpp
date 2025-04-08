// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/Weapon_Rifle.h"
#include "Charactrer/TPSCharacter.h"
#include "Bullet.h"
#include "GameFramework/Character.h"

AWeapon_Rifle::AWeapon_Rifle()
{
	Bullet = ABullet::StaticClass();
	FireType = EFireType::EF_LineTrace;
}

void AWeapon_Rifle::StartFire(TWeakObjectPtr<class ATPSCharacter> OwnerCharaceter)
{
	Super::StartFire(OwnerCharaceter);

	ATPSCharacter* Character = OwnerCharaceter.Get();

	if (Character)
	{
		switch (FireType)
		{
		case EFireType::EF_LineTrace:
			GetWorld()->GetTimerManager()
				.SetTimer(FireTimerHandle,
					[Character, this]() {FireWithLineTrace(Character);},
					FireInterval,
					true
				);
			break;
		case EFireType::EF_Projectile:
			GetWorld()->GetTimerManager()
				.SetTimer(FireTimerHandle,
					[Character, this]() {FireWithProjectile(Character);},
					FireInterval,
					true
				);
			break;
		default:
			break;
		}
	}
}

void AWeapon_Rifle::StopFire()
{
	Super::StopFire();
	if (FireTimerHandle.IsValid())
	{
		GetWorldTimerManager().ClearTimer(FireTimerHandle);
	}
}

void AWeapon_Rifle::Reloading()
{
	Super::Reloading();
}

void AWeapon_Rifle::FinishReloading()
{
	Super::FinishReloading();
}

void AWeapon_Rifle::FireWithProjectile(TWeakObjectPtr<class ATPSCharacter> OwnerCharacter)
{
	ATPSCharacter* Character = OwnerCharacter.Get();
	if (Character == nullptr)
		return;
	if (AmomoRemainCount <= 0)
	{
		Character->StopAnimMontage(Character->GetCurrentMontage());
		StopFire();
		return;
	}

	FVector Start = weaponMesh->GetSocketLocation("FireSocket");
	FVector End = Start + Character->GetActorForwardVector();
	FVector Direciton = End - Start;

	ABullet* SpawnBullet = GetWorld()->SpawnActor<ABullet>(Bullet);
	if(SpawnBullet)
	{
		SpawnBullet->SetActorLocation(Start);
		SpawnBullet->SetActorRotation(Direciton.Rotation());

		if (Direciton.Normalize())
		{
			SpawnBullet->Fire(Direciton);
		}
		AmomoRemainCount--;
	}
}

void AWeapon_Rifle::FireWithLineTrace(TWeakObjectPtr<class ATPSCharacter> OwnerCharacter)
{
	ATPSCharacter* Character = OwnerCharacter.Get();
	if (Character == nullptr)
		return;
	if (AmomoRemainCount <= 0)
	{
		Character->StopAnimMontage(Character->GetCurrentMontage());
		StopFire();
		return;
	}
	const FVector Start = weaponMesh->GetSocketLocation("FireSocket");
	const FVector End = Start + Character->GetActorForwardVector() * TraceDistance;	

	FHitResult HitResult;

	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(Character);

	bool HitDetected = GetWorld()->LineTraceSingleByChannel(HitResult,
		Start, End, ECollisionChannel::ECC_Visibility, CollisionParams);

	if (HitDetected)
	{
		ACharacter* HitCharacter = Cast<ACharacter>(HitResult.GetActor());

		if(HitCharacter)
		{
			
			GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, TEXT("LineTraceHit"));
		}

		FTransform HitTransform;
		HitTransform.SetLocation(HitResult.ImpactPoint);
		PlayHitEffect(HitTransform);

	}
	AmomoRemainCount--;
#if ENABLE_DRAW_DEBUG
	FColor DrawColor = HitDetected ? FColor::Green : FColor::Red;
	DrawDebugLine(GetWorld(), Start, End, DrawColor, false, 1.0f);
#endif

}
