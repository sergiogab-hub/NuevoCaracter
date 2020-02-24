// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Pared1.generated.h"

UCLASS()
class NUEVOCARACTER_API APared1 : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APared1();
	
	 UPROPERTY(EditAnywhere) float damageAabsorver;
	


};
