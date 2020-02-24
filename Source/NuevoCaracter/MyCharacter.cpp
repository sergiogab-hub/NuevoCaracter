// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/InputComponent.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "TimerManager.h"
#include "Engine/EngineTypes.h"
#include "UObject/NameTypes.h"
#include "Enemy.h"
#include "Paredsita.h"


// Sets default values
AMyCharacter::AMyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Crear  Componentes por el lado de codigo

	cam = CreateDefaultSubobject<UCameraComponent>("Cam"); //	Crear Componentes desde el lado de C++
	cam->bUsePawnControlRotation = true;
	cam->SetupAttachment(GetRootComponent());

	arms = CreateDefaultSubobject<USkeletalMeshComponent>("Arms");
	arms->SetupAttachment(cam);

	weapon = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	weapon->SetupAttachment(arms, "GripPoint");                      // D euna vez le dije que quiero que se quede atachado a la Mano



}





void AMyCharacter::MoveForward(float dato)
{
	AddMovementInput(GetActorForwardVector(), dato);

}

void AMyCharacter::MoveSides(float dato)
{
	AddMovementInput(GetActorRightVector(), dato);
}

void AMyCharacter::LookUp(float dato)
{


	AddControllerPitchInput((dato*-1) * rotationspeed * GetWorld()->GetDeltaSeconds()); //AddControllerPitchInput Aplica una Rotacion Vertical
}

void AMyCharacter::TurnSides(float dato)
{
	AddControllerYawInput(dato * rotationspeed * GetWorld()->GetDeltaSeconds()); //AddoControllerYawInput Aplica una Rotacion Horizontal
}

void AMyCharacter::StarJump()
{
	Jump();
}

void AMyCharacter::StopJump()
{
	StopJumping();
}

void AMyCharacter::StartShoot()
{
	GetWorld()->GetTimerManager().SetTimer(shootTimerHandle, this, &AMyCharacter::ShootTimer, 0.1, true);

}

void AMyCharacter::StopShoot()
{
	GetWorldTimerManager().ClearTimer(shootTimerHandle);
}

void AMyCharacter::ShootTimer()
{
    shoot(1, 0);
	
}



void AMyCharacter::StartShoot2()
{
	GetWorld()->GetTimerManager().SetTimer(shootTimerHandle2, this, &AMyCharacter::ShootTimer2, 0.1, true);

}

void AMyCharacter::StopShoot2()
{
	GetWorldTimerManager().ClearTimer(shootTimerHandle2);
}

void AMyCharacter::ShootTimer2()
{
	shoot(6, 500);

}






void AMyCharacter::shoot(int amount, float shake)
{
	for (int i = 0; i < amount; i++) {

		// FHitResult hitInfo; //Variable especial Creada para guardar los datos del TraceByChanel

		TArray <FHitResult> hits;//Arreglo para guardar los hits del trace
        float currentdamage = basedamage;

		FVector shakevector;                                  //	Dispersion de la balas con el rango que le mando del Shootimer2
		shakevector.X = FMath::RandRange(-shake, shake);    
		shakevector.Y = FMath::RandRange(-shake, shake);
		shakevector.Z = FMath::RandRange(-shake, shake);


		GetWorld()->LineTraceMultiByChannel(hits,  // Variable especial , inicio del rayo , final , y nombre del DefaultEngine.ini
			cam->GetComponentLocation() + cam->GetForwardVector() * 100,
			cam->GetComponentLocation() + cam->GetForwardVector() * 10000+shakevector,
			ECC_GameTraceChannel3);

		// float numero = hits.Num();
		//  UE_LOG(LogTemp, Warning, TEXT("Numero de hits: %f"), numero ); //Debug

		DrawDebugLine(
			GetWorld(),
			cam->GetComponentLocation(),
			cam->GetComponentLocation() + cam->GetForwardVector() * 10000 +shakevector,
			FColor::Red,
			false,
			3);

		for (int i = 0; i < hits.Num(); i++) {


			FHitResult hitInfo = hits[i];

			// if (hitInfo.bBlockingHit) // Corrobora si el trace bloqueo



			DrawDebugBox(GetWorld(), hitInfo.ImpactPoint, FVector(5, 5, 5), FColor::Blue, false, 2); //Dibuja un cuadrado done choco de la dimensiones Fvector , no se olvide de sacar cuando overlapea

			if (hitInfo.GetActor()) //Corrobora si choco contra un actor 
			{
				AParedsita* pared = Cast<AParedsita>(hitInfo.GetActor());

				if (pared)
				{
					currentdamage -= pared->damageAabsorver;
					// UE_LOG(LogTemp, Warning, TEXT("Cogio la  pared ")); //Debug
				}
				else {
					// UE_LOG(LogTemp, Warning, TEXT("NO Cogio una puta mierda"));  //Debug
					AEnemy* enemy = Cast<AEnemy>(hitInfo.GetActor()); //Casteo al Actor para poder restarle Daño

					UE_LOG(LogTemp, Warning, TEXT("Bone Name: %s"), *hitInfo.BoneName.ToString());  //Imprimo el nombre del hueso , hago la conversacion de a STRING , utilizar puntero *

					if (enemy && damages.Contains(hitInfo.BoneName)) { //Corroboro si el enemigo casteo correctamente y si le doy a un hueso xd

						float damagePercentage = damages[hitInfo.BoneName];
						float TotalDamage = currentdamage * damagePercentage;

						enemy->life -= TotalDamage;

						UE_LOG(LogTemp, Warning, TEXT("Damage Percentage: %f"), damagePercentage); //Imnprimos el porcentaje al daño asociado
						UE_LOG(LogTemp, Warning, TEXT("Total Damage: %f"), TotalDamage);//Imprimimos el Daño directo
					}
				}
			}
		}
	}
}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	PlayerInputComponent->BindAxis("MoveForward", this, &AMyCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveSides", this, &AMyCharacter::MoveSides);
	PlayerInputComponent->BindAxis("LookUp", this, &AMyCharacter::LookUp);
	PlayerInputComponent->BindAxis("TurnSides", this, &AMyCharacter::TurnSides);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AMyCharacter::StarJump);
	PlayerInputComponent->BindAction("Jump", EInputEvent::IE_Released, this, &AMyCharacter::StopJump);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AMyCharacter::StartShoot);
	PlayerInputComponent->BindAction("Fire", IE_Released, this, &AMyCharacter::StopShoot);
	PlayerInputComponent->BindAction("Fire2", IE_Pressed, this, &AMyCharacter::StartShoot2);
	PlayerInputComponent->BindAction("Fire2", IE_Released, this, &AMyCharacter::StopShoot2);


}

