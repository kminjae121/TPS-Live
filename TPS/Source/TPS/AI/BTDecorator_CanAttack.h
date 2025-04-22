

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTDecorator_CanAttack.generated.h"

/**
 * 
 */
UCLASS()
class TPS_API UBTDecorator_CanAttack : public UBTDecorator
{
	GENERATED_BODY()

public:
	UBTDecorator_CanAttack();
protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent&
		OwnerCompo, uint8* NodeMemory) const override;
public:
	UPROPERTY(EditAnywhere)
	float AttackRange = 15.0f;
};
