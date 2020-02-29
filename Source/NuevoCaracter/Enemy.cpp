// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "LifeComponent.h"

// Sets default values
AEnemy::AEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	life = CreateDefaultSubobject<ULifeComponent>("Life Component");
}



void AEnemy::Damage(float amount, FName boneName)
{
	life->TakeDamage(amount, boneName);
}

/*void AEnemy::Heal(float amount)

{
	life = +amount;
	if (life = MaxLife) {
		life = MaxLife;
	}
}
*/
