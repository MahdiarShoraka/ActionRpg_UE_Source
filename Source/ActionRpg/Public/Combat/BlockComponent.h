// Mahdiar Shoraka All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BlockComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_OneParam(
	FOnBlockSignature,
	UBlockComponent,
	OnBlockDelegate,
	float, Cost);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ACTIONRPG_API UBlockComponent : public UActorComponent
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere)
	float StaminaCost = 10.f;
	
	UPROPERTY(EditAnywhere)
	UAnimMontage* BlockAnimMontage;

public:	
	UBlockComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	bool Check(AActor* Opponent);
	
	UPROPERTY(BlueprintAssignable)
	FOnBlockSignature OnBlockDelegate;
};
