// Fill out your copyright notice in the Description page of Project Settings.


#include "ShootTask.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"


EBTNodeResult::Type UShootTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	GetWorld()->SpawnActor<AActor>(bulletBluePrint.Get() , OwnerComp.GetOwner()->GetActorLocation(), OwnerComp.GetOwner()->GetActorRotation());

	return EBTNodeResult::Type::Succeeded;

}