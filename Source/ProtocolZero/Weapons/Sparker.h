// (C) Naibell

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponBase.h"
#include "../Interfaces/Interactable.h"
#include "../MainCharacter/MainCharacter.h"
#include "Sparker.generated.h"

UCLASS()
class PROTOCOLZERO_API ASparker : public AWeaponBase, public IInteractable
{
	GENERATED_BODY()
	
public:	
	ASparker();

protected:
	virtual void BeginPlay() override;
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	FString ThingDescription = TEXT("ПТ-3 Искровик");
public:	
	virtual void Tick(float DeltaTime) override;

protected:
	void Equip() override;
	void Fire() override;
	virtual void Interact_Implementation(const AActor* initiator) override;
	virtual FString GetThingDescription_Implementation() override;
public:
	void StartFire() override;
	void EndFire() override;
	void Reload() override;
private:
	AMainCharacter* player;
	void CastTrace();
};
