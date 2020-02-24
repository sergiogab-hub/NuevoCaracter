// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Paredsita.generated.h"

UCLASS()
class NUEVOCARACTER_API AParedsita : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AParedsita();

	UPROPERTY(EditAnywhere) float damageAabsorver;
};
