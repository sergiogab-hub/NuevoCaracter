// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"

#include "PatrolObject.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UPatrolObject : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class NUEVOCARACTER_API IPatrolObject
{
	GENERATED_BODY()

		// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	/*AI*/virtual TArray<class ATargetPoint*> GetWaypoints() = 0;


};