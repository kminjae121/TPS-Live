// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Waepon.h"
#include "Weapon_Rifle.generated.h"

/**
 * 
 */
UCLASS()
class TPS_API AWeapon_Rifle : public AWaepon
{
	GENERATED_BODY()
public:
	AWeapon_Rifle();

public :
	virtual void StartFire(TWeakObjectPtr<class ATPSCharacter> OwnerCharaceter) override;
	virtual void StopFire() override;
	virtual void Reloading() override;
	virtual void FinishReloading() override;
	void FireWithProjectile(TWeakObjectPtr<class ATPSCharacter> OwnerCharacter);
	void FireWithLineTrace(TWeakObjectPtr<class ATPSCharacter> OwnerCharacter);

private:
	UPROPERTY(EditAnywhere, Category = Bullet)
	TSubclassOf<class ABullet> Bullet;
	FTimerHandle FireTimerHandle;
	
};
