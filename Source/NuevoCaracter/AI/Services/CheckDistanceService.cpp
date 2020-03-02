// Fill out your copyright notice in the Description page of Project Settings.


#include "CheckDistanceService.h"
#include "BehaviorTree/BlackboardComponent.h"

void UCheckDistanceService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	
	
	UBlackboardComponent* blackboardComp= OwnerComp.GetBlackboardComponent();

	UObject* targetObject =blackboardComp->GetValueAsObject(bbTarget.SelectedKeyName); //Convertir a Actor porque es un Objeto

	AActor* targetActor = Cast<AActor>(targetObject);

	if (targetActor) {

		FVector controlledPawnLocation = OwnerComp.GetOwner()->GetActorLocation(); //Version GetControllerPawn de los BP
		FVector targetActorLocation = targetActor->GetActorLocation();
		FVector diff = controlledPawnLocation - targetActorLocation;
		float dist = diff.Size();

		if (dist <= minDistance) {

			blackboardComp->SetValueAsBool(bbCheck.SelectedKeyName, true);
		}
		else {
			blackboardComp->SetValueAsBool(bbCheck.SelectedKeyName, false);
		}

	}

}
