// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySpawner.h"
#include "Engine/World.h"
// Sets default values


// Called when the game starts or when spawned
void AEnemySpawner::BeginPlay()
{
	Super::BeginPlay();

	for (int i = 0; i < Amount; i++) {

		int spawnPointIndex = FMath::RandRange(0, spawnPoints.Num() - 1);   //Cuantos Actores aparece por punto //Aleatorio
	

		AActor* spawnPoint = spawnPoints[spawnPointIndex]; //Guardo en la varible SpawnPoint El actor que le corresponde al indice 

		int blueprintsIndex = FMath::RandRange(0, blueprintsToSpawn.Num() - 1); //Numero aletorio
		TSubclassOf<AActor> blueprintToSpawn = blueprintsToSpawn[blueprintsIndex]; //Guardo ese Numero Aletorio de la esa clase 

		GetWorld()->SpawnActor<AActor>(blueprintToSpawn.Get(), spawnPoint->GetTransform()); //Spameo el actor


	}


	/* int spawnIndex = FMath::RandRange(0, spawnPoints.Num() - 1);   //Creo la Variable para guardar el numero Aleatorio entre 0 el numero de Span (-1 porque es un vector)
	AActor* spawnPoint = spawnPoints[spawnIndex];      //Le digo que para mi Variable SpawnPoint cree un Spawn

	GetWorld()->SpawnActor<AActor>(blueprintToSpawn.Get(), spawnPoint->GetTransform()); */  //Spameo un Actor que determinare en el details de mi clase BlueprintoSpaen , Consigo la trasformada para la localizacion
	
}



