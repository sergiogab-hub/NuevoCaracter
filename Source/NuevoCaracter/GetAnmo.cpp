// Fill out your copyright notice in the Description page of Project Settings.


#include "GetAnmo.h"
#include "MyCharacter.h"

// Sets default values
AGetAnmo::AGetAnmo()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGetAnmo::BeginPlay()
{
	Super::BeginPlay();
	OnActorBeginOverlap.AddDynamic(this, &AGetAnmo::OnOverlap);

	
}

// Called every frame
void AGetAnmo::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGetAnmo::OnOverlap(AActor* me, AActor* other)
{
	AMyCharacter* pb = Cast <AMyCharacter>(other); //LLamo alo jugadorbase con le que se supone debo overlapear si el casteo es verdadero le quito a vida tanto daño
	if (pb != nullptr) {
		
	}
	Destroy();
}

