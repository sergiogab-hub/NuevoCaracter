// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"

// Sets default values
AEnemy::AEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}



void AEnemy::Damage(float amount, FName boneName)
{
	if (damages.Contains(boneName)) { //Corroboro si el enemigo casteo correctamente y si le doy a un hueso xd

		float damagePercentage = damages[boneName];
		float TotalDamage = amount * damagePercentage;

		life -= TotalDamage;

		if (life <= 0) {
			Destroy();
		}

		UE_LOG(LogTemp, Warning, TEXT("Damage Percentage: %f"), damagePercentage); //Imnprimos el porcentaje al daño asociado
		UE_LOG(LogTemp, Warning, TEXT("Total Damage: %f"), TotalDamage);//Imprimimos el Daño directo
	}
}

/*void AEnemy::Heal(float amount)

{
	life = +amount;
	if (life = MaxLife) {
		life = MaxLife;
	}
}
*/
