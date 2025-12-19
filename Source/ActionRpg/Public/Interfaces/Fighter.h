// Mahdiar Shoraka All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Characters/EStat.h"
#include "UObject/Interface.h"
#include "Fighter.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UFighter : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class ACTIONRPG_API IFighter
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual float GetDamage() { return 0.0f; }
	
	virtual void Attack() {}
	
	virtual float GetAnimDuration() {return 0.0f;}
	
	virtual float GetMeleeRange() { return 0.0f; }
	
	virtual bool CanTakeDamage(AActor* Opponent) { return true; }
};
