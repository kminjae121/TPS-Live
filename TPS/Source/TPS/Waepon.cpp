// Fill out your copyright notice in the Description page of Project Settings.


#include "Waepon.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"

// Sets default values
AWaepon::AWaepon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	weaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));

	SetRootComponent(weaponMesh);

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> WeaponMeshRef(TEXT
	("/Script/Engine.SkeletalMesh'/Game/_Art/FPS_Weapon_Bundle/Weapons/Meshes/AR4/SK_AR4.SK_AR4'"));
	if (WeaponMeshRef.Succeeded())
	{
		weaponMesh->SetSkeletalMesh(WeaponMeshRef.Object);
	}

	static ConstructorHelpers::FObjectFinder<UParticleSystem> HitEffectRef(
		TEXT("/Script/Engine.ParticleSystem'/Game/_Art/Effect/Particles/P_HitEffect.P_HitEffect'"));

	if (HitEffectRef.Succeeded())
	{
		HitEffect = HitEffectRef.Object;
	}

}

// Called when the game starts or when spawned
void AWaepon::BeginPlay()
{
	Super::BeginPlay();

	AmomoRemainCount = AmmoMaxCount;
	
}

// Called every frame
void AWaepon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWaepon::StartFire(TWeakObjectPtr<class ATPSCharacter> OwnerCharaceter)
{
	
}

void AWaepon::StopFire()
{
}

void AWaepon::Reloading()
{
	StopFire();
}

void AWaepon::FinishReloading()
{
	
	AmomoRemainCount = AmmoMaxCount;
}

void AWaepon::PlayHitEffect(FTransform HitTransform)
{
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitEffect, HitTransform);
}

