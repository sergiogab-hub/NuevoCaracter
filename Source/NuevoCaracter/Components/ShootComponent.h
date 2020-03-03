// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "ShootComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FShootHitDelegate, FVector, HitPoint); //Delegado para crear eventos en los BPP


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class NUEVOCARACTER_API UShootComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	
	UPROPERTY (EditAnywhere) int ammo =100;
	UPROPERTY(EditAnywhere) TSubclassOf<class AActor> bulletBlueprint;
	UPROPERTY(VisibleAnywhere) float basedamage = 100; //Daño que hace mi personaje
	UPROPERTY(BlueprintAssignable) FShootHitDelegate onHit;

	void Shooting(int amount, float shake);
	void reloadMo();
};
