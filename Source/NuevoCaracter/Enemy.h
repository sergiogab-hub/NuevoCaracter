// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Damageable.h"


#include "Enemy.generated.h"

UCLASS()
class NUEVOCARACTER_API AEnemy : public ACharacter , public IDamageable 

{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemy();

	UPROPERTY(EditAnywhere) float lifesita=100;
	UPROPERTY(EditAnywhere) float MaxLife = 100;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite) class ULifeComponent* life;
	
	void Damage(float amount, FName boneName) override;
	//void Heal(float amount) override;
};
