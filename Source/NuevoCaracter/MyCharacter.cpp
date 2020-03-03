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
#include "Damageable.h"
#include "Healeable.h"
#include "LifeComponent.h"
#include "Components/ShootComponent.h"
#include "GetAnmo.h"
#include "Potenciador.h"



// Sets default values
AMyCharacter::AMyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Crear  Componentes por el lado de codigo


	life = CreateDefaultSubobject<ULifeComponent>("Life Component");

	cam = CreateDefaultSubobject<UCameraComponent>("Cam"); //	Crear Componentes desde el lado de C++
	cam->bUsePawnControlRotation = true;
	cam->SetupAttachment(GetRootComponent());



	shoot = CreateDefaultSubobject<UShootComponent>("Shoot Component");
	shoot->SetupAttachment(cam);

	arms = CreateDefaultSubobject<USkeletalMeshComponent>("Arms");
	arms->SetupAttachment(cam);



	weapon = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	weapon->SetupAttachment(arms, "GripPoint");     // De una vez le dije que quiero que se quede atachado a la Mano
	
	

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
	OnStarJump();
}

void AMyCharacter::StopJump()
{
	StopJumping();
}




void AMyCharacter::StartShoot()
{
	GetWorld()->GetTimerManager().SetTimer(shootTimerHandle, this, &AMyCharacter::ShootTimer, 0.1, true);
	OnStartShoot();
}

void AMyCharacter::StopShoot()
{
	GetWorldTimerManager().ClearTimer(shootTimerHandle);
	OnEndShoot();
}

void AMyCharacter::ShootTimer()
{
	shoot->Shooting(1, 0);

	nuevaammo = shoot->ammo;
	if (nuevaammo >= 1) {
		shoot->ammo--;
	}
	else {
		shoot->ammo = 0;
	}
	nuevaammo = shoot->ammo;
}



	void AMyCharacter::StartShoot2()
	{
		if (potenciador != false) {
			GetWorld()->GetTimerManager().SetTimer(shootTimerHandle2, this, &AMyCharacter::ShootTimer2, 0.1, true);
		}
	}

	void AMyCharacter::StopShoot2()
	{
		GetWorldTimerManager().ClearTimer(shootTimerHandle2);
	}

	void AMyCharacter::ShootTimer2()
	{
		shoot->Shooting(6, 1200);

		nuevaammo = shoot->ammo;
	

		
		if (shoot->ammo >= 6)
		{
			shoot->ammo -= 6;

		}
		else {
			shoot->ammo =0;
		}

		nuevaammo = shoot->ammo;
		UE_LOG(LogTemp, Warning, TEXT("nuevaammo: %f"), nuevaammo);
		UE_LOG(LogTemp, Warning, TEXT("ammo: %f"), shoot->ammo);
		
	}

void AMyCharacter::reload()
	{


	}






/*void AMyCharacter::shoot(int amount, float shake)
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
			cam->GetComponentLocation() + cam->GetForwardVector() * 10000 + shakevector,
			ECC_GameTraceChannel3);

		// float numero = hits.Num();
		//  UE_LOG(LogTemp, Warning, TEXT("Numero de hits: %f"), numero ); //Debug

		DrawDebugLine(
			GetWorld(),
			cam->GetComponentLocation(),
			cam->GetComponentLocation() + cam->GetForwardVector() * 10000 + shakevector,
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
					IDamageable* damageable = Cast<IDamageable>(hitInfo.GetActor()); //Casteo al Actor para poder restarle Daño
					if (damageable) {

						damageable->Damage(currentdamage, hitInfo.BoneName);// Envio los parametros ala funcion de Enemy

						UE_LOG(LogTemp, Warning, TEXT("Bone Name: %s"), *hitInfo.BoneName.ToString()); //Imprimo el nombre del hueso , hago la conversacion de a STRING , utilizar puntero *

					}


					/*if (enemy && damages.Contains(hitInfo.BoneName)) { //Corroboro si el enemigo casteo correctamente y si le doy a un hueso xd

						float damagePercentage = damages[hitInfo.BoneName];
						float TotalDamage = currentdamage * damagePercentage;

						enemy->life -= TotalDamage;

						UE_LOG(LogTemp, Warning, TEXT("Damage Percentage: %f"), damagePercentage); //Imnprimos el porcentaje al daño asociado
						UE_LOG(LogTemp, Warning, TEXT("Total Damage: %f"), TotalDamage);//Imprimimos el Daño directo
					} 
					//Logica en Enemy

				}
			}
		}
	}
}
*/

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (lifeOwn <= 0) {

		shoot->ammo = 0;
		lifeOwn = 0;
	}

	if (lifeOwn >= 100) {
		lifeOwn = 100;
	}


	
}
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
	OnActorBeginOverlap.AddDynamic(this, &AMyCharacter::OnOverlap);
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

 void AMyCharacter::OnOverlap(AActor* me, AActor* other)
{
	 AGetAnmo* pb = Cast <AGetAnmo>(other); //LLamo alo jugadorbase con le que se supone debo overlapear si el casteo es verdadero le quito a vida tanto daño
	 if (pb != nullptr) {
		 
		
		 if (shoot->ammo >= 70)
		 {
			 shoot->ammo = 100;

		 }
		 else {
			 shoot->ammo += 30;
		 }

		
		 nuevaammo = shoot->ammo;
		// pb->Destroy();
		 UE_LOG(LogTemp, Warning, TEXT("Overlapeo: %f"), nuevaammo);
	 }
	 
	 APotenciador* pp = Cast <APotenciador>(other);

	 if (pp != nullptr){

		 potenciador = true;

		 pp->Destroy();
	 }
}

