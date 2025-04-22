// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BT_Service_DetectTarget.h"
#include "AIController.h"
#include "Engine/OverlapResult.h"
#include "BehaviorTree/BlackboardComponent.h"

UBT_Service_DetectTarget::UBT_Service_DetectTarget()
{
	NodeName = TEXT("Detect");
	Interval = 0.5f;
}

void UBT_Service_DetectTarget::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{	
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();

	if (nullptr == ControllingPawn)
		return;

	UWorld* World = ControllingPawn->GetWorld();

	if (nullptr == World)
		return;

	TArray<FOverlapResult> OverlapResults;

	FCollisionQueryParams CollisionParams;

	CollisionParams.AddIgnoredActor(ControllingPawn);

	FVector Center = ControllingPawn->GetActorLocation();

	bool bResult = World->OverlapMultiByChannel(
	OverlapResults,Center,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel3, FCollisionShape::MakeSphere(DetectRadius),
		CollisionParams);


	if (bResult)
	{
		for (auto const& overlapResult : OverlapResults)
		{
			APawn* TargetPawn = Cast<APawn>(overlapResult.GetActor());
			if (TargetPawn && TargetPawn->GetController()->IsPlayerController())
			{
				OwnerComp.GetBlackboardComponent()->SetValueAsObject(TEXT("TargetActor"),TargetPawn);

				DrawDebugSphere(World, Center, DetectRadius, 16, FColor::Green,
					false, 0.2f);
				return;
			}
		}
	}

	OwnerComp.GetBlackboardComponent()->SetValueAsObject(TEXT("TargetActor"), nullptr);


	DrawDebugSphere(World, Center, DetectRadius, 16, FColor::Red,
		false, 0.2f);
}
