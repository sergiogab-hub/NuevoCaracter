// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemySpawner.generated.h"

UCLASS()
class NUEVOCARACTER_API AEnemySpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	UPROPERTY(EditAnywhere)
		int Amount;  //Numero de Actores que voy a Spawmear

	UPROPERTY(EditAnywhere)
		TArray <AActor*> spawnPoints;  //Variable tipo Arreglo que contiene los actores que van a spamear otros actores

	UPROPERTY(EditAnywhere)
		TArray<TSubclassOf<AActor>> blueprintsToSpawn; //Arreglo de Clases 
       // TSubclassOf<AActor> blueprintsToSpawn; //Variable que dice que vamos a spamear actores



protected:

	virtual void BeginPlay() override;



};
