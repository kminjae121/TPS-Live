// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Waepon.generated.h"

UCLASS()
class TPS_API AWaepon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWaepon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	FORCEINLINE int32 GetAmmoMaxCount() { return AmmoMaxCount; }
	FORCEINLINE int32 GetAmmoRemainCount() { return AmomoRemainCount; }
	FORCEINLINE float GetReloadingDelayTime() { return ReloadingDelayTime; }

protected:
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	TObjectPtr<class USkeletalMeshComponent> weaponMesh;

	UPROPERTY(EditAnywhere, Category = Properties)
	int32 AmmoMaxCount = 30;


	UPROPERTY(EditAnywhere, Category = Properties)
	int32 AmomoRemainCount = 30;

	UPROPERTY(EditAnywhere, Category = Properties)
	float ReloadingDelayTime = 3.0f;

};
