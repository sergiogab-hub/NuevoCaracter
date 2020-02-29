// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "ShootComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class NUEVOCARACTER_API UShootComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	
	UPROPERTY (EditAnywhere) int ammo =100;
	UPROPERTY(EditAnywhere) TSubclassOf<class AActor> bulletBlueprint;
	UPROPERTY(VisibleAnywhere) float basedamage = 100; //Daño que hace mi personaje

	void Shooting(int amount, float shake);
};
