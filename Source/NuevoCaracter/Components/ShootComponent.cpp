// Fill out your copyright notice in the Description page of Project Settings.


#include "ShootComponent.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "Paredsita.h"
#include "Damageable.h"



// Called every frame



void UShootComponent::Shooting(int amount, float shake)
{
	if (ammo > 0) {
	
	for (int i = 0; i < amount; i++) {

		// FHitResult hitInfo; //Variable especial Creada para guardar los datos del TraceByChanel

		TArray <FHitResult> hits;//Arreglo para guardar los hits del trace
		float currentdamage = basedamage;

		FVector shakevector;                                  //	Dispersion de la balas con el rango que le mando del Shootimer2
		shakevector.X = FMath::RandRange(-shake, shake);
		shakevector.Y = FMath::RandRange(-shake, shake);
		shakevector.Z = FMath::RandRange(-shake, shake);


		GetWorld()->LineTraceMultiByChannel(hits,  // Variable especial , inicio del rayo , final , y nombre del DefaultEngine.ini
			GetComponentLocation() + GetForwardVector() * 100,
			GetComponentLocation() + GetForwardVector() * 10000 + shakevector,
			ECC_GameTraceChannel3);

		// float numero = hits.Num();
		//  UE_LOG(LogTemp, Warning, TEXT("Numero de hits: %f"), numero ); //Debug

		DrawDebugLine(
			GetWorld(),
		  GetComponentLocation(),
		    GetComponentLocation() + GetForwardVector() * 10000 + shakevector,
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
					} */
					//Logica en Enemy

				}
			}
			}
		}
	}
}
