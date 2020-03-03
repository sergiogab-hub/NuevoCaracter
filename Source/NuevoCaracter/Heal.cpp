// Fill out your copyright notice in the Description page of Project Settings.


#include "Heal.h"
#include "MyCharacter.h"

// Sets default values
AHeal::AHeal()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AHeal::BeginPlay()
{
	Super::BeginPlay();
	OnActorBeginOverlap.AddDynamic(this, &AHeal::OnOverlap);
}

// Called every frame
void AHeal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AHeal::OnOverlap(AActor* me, AActor* other)
{
	AMyCharacter* pb = Cast <AMyCharacter>(other); //LLamo alo jugadorbase con le que se supone debo overlapear si el casteo es verdadero le quito a vida tanto daño
	if (pb != nullptr) {
		pb->lifeOwn+=heal;
	}
	Destroy();
}

