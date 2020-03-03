// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Damageable.h"
#include "AI/Interfaces/PatrolObject.h"
#include "Enemy.generated.h"

UCLASS()
class NUEVOCARACTER_API AEnemy : public ACharacter , public IDamageable , public IPatrolObject

{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemy();


	UPROPERTY(BlueprintReadWrite) float lifeTotal=100;


	UPROPERTY(VisibleAnywhere, BlueprintReadWrite) class ULifeComponent* life;
	/*AI*/UPROPERTY(EditAnywhere) TArray<class ATargetPoint*> waypoints; 
	
	void Damage(float amount, FName boneName) override;

	/*AI*/TArray <class ATargetPoint*> GetWaypoints() override; // Defino mi propio funcion heredada de PátrolObjest
	//void Heal(float amount) override;

	virtual void Tick(float DeltaTime) override;
};
