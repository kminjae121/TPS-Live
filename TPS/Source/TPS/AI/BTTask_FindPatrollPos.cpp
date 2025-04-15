// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask_FindPatrollPos.h"
#include "AIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_FindPatrollPos::UBTTask_FindPatrollPos()
{
}

EBTNodeResult::Type UBTTask_FindPatrollPos::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (Super::ExecuteTask(OwnerComp, NodeMemory) == EBTNodeResult::Failed)
		return EBTNodeResult::Failed;

	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();

	if (nullptr == ControllingPawn)
		return EBTNodeResult::Failed;

	UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetNavigationSystem
	(ControllingPawn->GetWorld());

	FVector Origin = OwnerComp.GetBlackboardComponent()->GetValueAsVector
	(TEXT("HomePos"));

	FNavLocation NextPatrollPos;

	if (NavSystem->GetRandomPointInNavigableRadius(Origin, PatrolPos, NextPatrollPos))
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(TEXT("PatrolPos"), NextPatrollPos.Location);
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}


