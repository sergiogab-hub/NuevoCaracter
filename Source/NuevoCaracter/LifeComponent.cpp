// Fill out your copyright notice in the Description page of Project Settings.


#include "LifeComponent.h"
#include "GameFramework/Actor.h"

void ULifeComponent::TakeDamage(float amount ,FName boneName)
{
	if (damages.Contains(boneName)) { //Corroboro si el enemigo casteo correctamente y si le doy a un hueso xd

		float damagePercentage = damages[boneName];
		float TotalDamage = amount * damagePercentage;

		life -= TotalDamage;

		if (life <= 0) {
			GetOwner ()->Destroy();
		}

		UE_LOG(LogTemp, Warning, TEXT("Damage Percentage: %f"), damagePercentage); //Imnprimos el porcentaje al daño asociado
		UE_LOG(LogTemp, Warning, TEXT("Total Damage: %f"), TotalDamage);//Imprimimos el Daño directo
	}
}

