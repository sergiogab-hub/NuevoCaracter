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
	GetWorldTimerManager().SetTimer(shootTimer, this, &AMyCharacter::ShootTimer, 0.1 , true);

	/*FHitResult hitInfo; //Variable especial Creada para guardar los datos del TraceByChanel

	bool hasHit =GetWorld()->LineTraceSingleByChannel(hitInfo,  // Variable especial , inicio del rayo , final , y nombre del DefaultEngine.ini
									   cam->GetComponentLocation()+ cam->GetForwardVector() * 100,
									   cam->GetComponentLocation()+ cam->GetForwardVector()*1000, ECC_GameTraceChannel3);
	DrawDebugLine(
		GetWorld(),
		cam->GetComponentLocation(),
		cam->GetComponentLocation() + cam->GetForwardVector() * 1000, FColor::Red ,false,3);

	if (hasHit && hitInfo.GetActor()) // Corrobora si choco y sobre todo si choco contra un actor
	{
		 hitInfo.GetActor()->Destroy();
	}
	*/



}

void AMyCharacter::StopShoot()
{
	GetWorldTimerManager().ClearTimer(shootTimer);
}

void AMyCharacter::ShootTimer()

{
	
	FHitResult hitInfo; //Variable especial Creada para guardar los datos del TraceByChanel

	bool hasHit = GetWorld()->LineTraceSingleByChannel(hitInfo,  // Variable especial , inicio del rayo , final , y nombre del DefaultEngine.ini
		cam->GetComponentLocation() + cam->GetForwardVector() * 100,
		cam->GetComponentLocation() + cam->GetForwardVector() * 1000, ECC_GameTraceChannel3);

	DrawDebugLine(
		GetWorld(),
		cam->GetComponentLocation(),
		cam->GetComponentLocation() + cam->GetForwardVector() * 1000, FColor::Red, false, 3);

	if (hitInfo.bBlockingHit) // Corrobora si choco 
	{
		DrawDebugBox(GetWorld(), hitInfo.ImpactPoint, FVector(5, 5, 5), FColor::Blue, false, 2);
	     

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

}

