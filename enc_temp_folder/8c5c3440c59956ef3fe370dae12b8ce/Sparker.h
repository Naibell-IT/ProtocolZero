// (C) Naibell

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponBase.h"
#include "../Interfaces/Interactable.h"
#include "Sparker.generated.h"

UCLASS()
class PROTOCOLZERO_API ASparker : public AWeaponBase, public IInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASparker();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	FString ThingDescription = TEXT("ПТ-3 Искровик");
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	void Equip() override;

	void StartFire() override;

	void EndFire() override;

	void Fire() override;

	void Reload() override;

	virtual void Interact_Implementation(const AActor* initiator) override;
	virtual FString GetThingDescription_Implementation() override;
};
