// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyCharacter.generated.h"

UCLASS()
class NUEVOCARACTER_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	
	AMyCharacter();

	FTimerHandle shootTimerHandle; 
	FTimerHandle shootTimerHandle2;//Timer para el disparo

	UPROPERTY(EditAnywhere) float rotationspeed = 45; //Velocidad con la que rota la camara
	UPROPERTY(VisibleAnywhere) class UCameraComponent* cam;
	UPROPERTY(VisibleAnywhere) class USkeletalMeshComponent* arms;
	UPROPERTY(VisibleAnywhere) class USkeletalMeshComponent* weapon;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite) class ULifeComponent* life;
	UPROPERTY(VisibleAnywhere) class UShootComponent* shoot;
	
	// UPROPERTY(VisibleAnywhere) float healamount = 10; //Heal que hace mi personaje
    UPROPERTY(EditAnywhere) float shake; //Dispersion del disparo
	UPROPERTY(EditAnywhere) float amout; // cantidad de disparos

	UPROPERTY(EditAnywhere) float shake2 = 0;//Dispersion del disparo
	UPROPERTY(EditAnywhere) float amout2 = 0; // cantidad de disparos

	UPROPERTY(BlueprintReadWrite) float lifeOwn=100;
	bool potenciador = false;
	float  nuevaammo;

private:

	void MoveForward(float dato);
	void MoveSides(float dato);
	void LookUp(float dato);
	void TurnSides(float dato);
	void StarJump();
	void StopJump();

	void StartShoot();
	void StopShoot();
	void ShootTimer();

	void StartShoot2();
	void StopShoot2();
	void ShootTimer2();

	void reload();


	//void shoot(int amount , float shake);
protected:
	
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/*Partycle System*/ UFUNCTION(BlueprintImplementableEvent)void OnStartShoot();
	/*Partycle System*/ UFUNCTION(BlueprintImplementableEvent)void OnEndShoot();
	/*Partycle System*/ UFUNCTION(BlueprintImplementableEvent)void OnStarJump();

	 /*Conseguir Municion*/UFUNCTION() 
		 void OnOverlap(AActor* me, AActor* other);



};
