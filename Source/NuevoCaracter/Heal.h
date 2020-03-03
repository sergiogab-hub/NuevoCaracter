// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Heal.generated.h"

UCLASS()
class NUEVOCARACTER_API AHeal : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHeal();
	UPROPERTY(EditAnywhere)
		float heal = 30;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION()      //Es necesario llamar a Ufunction para que lo detecte
	void OnOverlap(AActor* me, AActor* other);
};
