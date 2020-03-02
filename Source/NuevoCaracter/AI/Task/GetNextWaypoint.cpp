// Fill out your copyright notice in the Description page of Project Settings.


#include "GetNextWaypoint.h"
#include "AIController.h"
#include "AI/Interfaces/PatrolObject.h"
#include "Engine/TargetPoint.h"
#include "BehaviorTree/BlackboardComponent.h"

uint16 UGetNextWaypoint::GetInstanceMemorySize() const
{
	return sizeof(FNextWaypointData);
}

EBTNodeResult::Type UGetNextWaypoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	
	AAIController* aicontroller =Cast<AAIController>(OwnerComp.GetOwner());
    if(!aicontroller)   return EBTNodeResult::Type::Failed;  //Para corroborar
	
	IPatrolObject* patrolObject= Cast <IPatrolObject>(aicontroller->GetPawn());
	if (!patrolObject)   return EBTNodeResult::Type::Failed;  //Para corroborar

	TArray <ATargetPoint*> waypoints = patrolObject->GetWaypoints();
	FNextWaypointData* data = (FNextWaypointData*)NodeMemory;
	data->currentIndex++;

	if (data->currentIndex < 0 || data->currentIndex >= waypoints.Num())
	{
		data->currentIndex = 0;
	}


	
    ATargetPoint* currentWaypoint = waypoints[data->currentIndex];


	UBlackboardComponent* blackboard=OwnerComp.GetBlackboardComponent();
	blackboard->SetValueAsVector(bbTarget.SelectedKeyName, currentWaypoint->GetActorLocation());
	
		
		
		return EBTNodeResult::Type::Succeeded;




}