// Fill out your copyright notice in the Description page of Project Settings.


#include "Charactrer/TPSCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "InputMappingContext.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

// Sets default values
ATPSCharacter::ATPSCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> FindMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/_Art/MilitaryCharDark/MW_Style2_Female.MW_Style2_Female'"));


	if (FindMesh.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(FindMesh.Object);
	}

	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -88.0f), FRotator(0.0f, -90.0f, 0.0f));

	springArm = CreateDefaultSubobject < USpringArmComponent>(TEXT("SpringArm"));
	springArm->SetupAttachment(RootComponent);
	springArm->TargetArmLength = 400.0f;
	springArm->SetRelativeLocation(FVector(0.0f, 70.0f, 90.0f));

	camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	camera->SetupAttachment(springArm);
#pragma region InputSystems
	static ConstructorHelpers::FObjectFinder<UInputMappingContext> 
		IMCDefaultRef(TEXT("/Script/EnhancedInput.InputMappingContext'/Game/Input/Actions/IMAC_Default.IMAC_Default'"));
	if (IMCDefaultRef.Succeeded())
	{
		IMCDefault = IMCDefaultRef.Object;
	}
#pragma endregion

	static ConstructorHelpers::FObjectFinder<UInputAction> JumpActionRef
	(TEXT("/Script/EnhancedInput.InputAction'/Game/Input/Actions/IA_Jump.IA_Jump'"));

	if (JumpActionRef.Succeeded())
	{
		JumpAction = JumpActionRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> MoveActionRef
	(TEXT("/Script/EnhancedInput.InputAction'/Game/Input/Actions/IA_Move.IA_Move'"));

	if (MoveActionRef.Succeeded())
	{
		MoveAction = MoveActionRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> TurnActionRef
	(TEXT("/Script/EnhancedInput.InputAction'/Game/Input/Actions/IA_Turn.IA_Turn'"));

	if (TurnActionRef.Succeeded())
	{
		TurnAction = TurnActionRef.Object;
	}

}

// Called when the game starts or when spawned
void ATPSCharacter::BeginPlay()
{
	Super::BeginPlay();
	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	if (PlayerController)
	{
		auto* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>
			(PlayerController->GetLocalPlayer());
		if (Subsystem)
		{
			Subsystem->AddMappingContext(IMCDefault, 0);
		}
	}
	
}

// Called every frame
void ATPSCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATPSCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	auto* EnhancedInputCompoenet = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);

	if (EnhancedInputCompoenet)
	{
		EnhancedInputCompoenet->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputCompoenet->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
		EnhancedInputCompoenet->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ATPSCharacter::Input_Move);
		EnhancedInputCompoenet->BindAction(TurnAction, ETriggerEvent::Triggered, this, &ATPSCharacter::Input_Turn);

	}
}

void ATPSCharacter::Input_Move(const FInputActionValue& InputValue)
{
	FVector2D MovementVector = InputValue.Get<FVector2D>();

	const FRotator Rotation = GetControlRotation();

	const FRotator YawRotation(0.0f, Rotation.Yaw, 0.0f);

	const FVector ForwardVector = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	
	AddMovementInput(ForwardVector, MovementVector.X);
	AddMovementInput(RightDirection, MovementVector.Y);
}

void ATPSCharacter::Input_Turn(const FInputActionValue& InputValue)
{
	float XValue = InputValue.Get<float>();
	AddControllerYawInput(XValue);
}

