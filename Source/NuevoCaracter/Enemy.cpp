// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "LifeComponent.h"
#include "Engine/TargetPoint.h"

AEnemy::AEnemy()
{
 	
	PrimaryActorTick.bCanEverTick = true;
	life = CreateDefaultSubobject<ULifeComponent>("Life Component"); //Creo el componente de life
}



void AEnemy::Damage(float amount, FName boneName)
{
	life->TakeDamage(amount, boneName);
}

/*AI*/TArray<ATargetPoint*> AEnemy::GetWaypoints()
{

	return waypoints;
}

/*void AEnemy::Heal(float amount)

{
	life = +amount;
	if (life = MaxLife) {
		life = MaxLife;
	}
}
*/
