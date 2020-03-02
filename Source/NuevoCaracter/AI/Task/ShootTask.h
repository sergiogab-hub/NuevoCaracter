// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "ShootTask.generated.h"

/**
 * 
 */
UCLASS()
class NUEVOCARACTER_API UShootTask : public UBTTaskNode
{
	GENERATED_BODY()

public:

   UPROPERTY (EditAnywhere)	TSubclassOf<AActor>bulletBluePrint;


protected:

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

};
