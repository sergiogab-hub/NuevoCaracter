// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "GetNextWaypoint.generated.h"


struct FNextWaypointData
{
	int currentIndex = -1;
};


UCLASS()
class NUEVOCARACTER_API UGetNextWaypoint : public UBTTaskNode
{
	GENERATED_BODY()


public:

	UPROPERTY(EditAnywhere) FBlackboardKeySelector bbTarget;

	uint16 GetInstanceMemorySize() const override; // Cuanta memoria necesita nuestro nodo


protected:

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
};
